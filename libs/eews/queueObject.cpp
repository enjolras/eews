/***************************************************************************
 *   Copyright (C) 2008 by Miguel Revilla   *
 *   yo@miguelrevilla.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <QSqlQuery>
#include <QVariant>
#include <QDateTime>
#include <QTimer>
#include <QDir>
#include "queueObject.h"
#include "eewsServer.h"
#include "verdictObject.h"
#include "pluginInterface.h"

queueObject::queueObject(QObject *parent) : QObject(parent) {

	QTimer *timer = new QTimer(this) ;
	timer->setInterval(1000) ;
	connect(timer,SIGNAL(timeout()),this,SLOT(calculatePriority())) ;
	timer->start() ;

}

void queueObject::setSlots(int tmpSlots) {
	activeSlots = tmpSlots ;
}

int queueObject::getSlots() {
	return activeSlots ;
}

void queueObject::setTable(QString table) {

	sqlTable = table ;
}

void queueObject::addSubmission(QString ticket) {

	QDateTime now = QDateTime::currentDateTime();

	QSqlQuery query ;
	query.prepare("INSERT INTO " + sqlTable + " (ticket,timestamp,priority) "
			"VALUES (:ticket,:timestamp,:priority)") ;
	query.bindValue(":ticket",ticket) ;
	query.bindValue(":timestamp",now.toTime_t()) ;
	query.bindValue(":priority",0) ;
	query.exec() ;

	QSqlQuery queryStatus ;
	queryStatus.prepare("UPDATE submissions SET status = :status WHERE ticket = :ticket") ;
	queryStatus.bindValue(":status",getIdleStatus()) ;
	queryStatus.bindValue(":ticket",ticket) ;
	queryStatus.exec() ;

}

void queueObject::calculatePriority() {

	QSqlQuery query ;
	query.prepare("SELECT a.ticket AS ticket,a.priority AS priority,b.status AS status,b.plugin as plugin,b.lo as lo FROM "+sqlTable+" AS a JOIN submissions AS b ON a.ticket = b.ticket WHERE b.status = :status ORDER BY priority DESC") ;
	query.bindValue(":status",getIdleStatus()) ;
	query.exec() ;

	while(query.next()) {

		pluginInterface *tmpRealPlugin = qobject_cast<pluginInterface *>(PLUGINS->getPluginByUniqId(query.value(3).toString())) ;

		bool readyToProcess = FALSE;
		bool waitingForLO = FALSE;

		if(tmpRealPlugin->wantsLO() == FALSE) {
			readyToProcess=TRUE ;
		} else {
			QSqlQuery querylo ;
			querylo.prepare("SELECT status FROM locache WHERE url = :url") ;
			querylo.bindValue(":url",query.value(4).toString()) ;
			querylo.exec() ;

			if(!querylo.next()) {
				waitingForLO = TRUE ;
			} else {
				switch(querylo.value(0).toInt()) {
				case -1:
					{
					setStatus(query.value(0).toString(),SubmissionStatus::LONotAvailable) ;
					verdictObject *verdict = new verdictObject() ;
					verdict->setVerdict(SubmissionVerdict::SubmissionError) ;
					setVerdict(query.value(0).toString(),verdict) ;
					QSqlQuery query_delete ;
					query_delete.prepare("DELETE FROM "+sqlTable+" WHERE ticket = :ticket") ;
					query_delete.bindValue(":ticket",query.value(0).toString()) ;
					query_delete.exec() ;
					break ;
					}
				case 0:
					readyToProcess=TRUE ;
					break ;
				default:
					waitingForLO = TRUE ;
					break ;
				}
			}

			if(waitingForLO == TRUE) {
				setStatus(query.value(0).toString(),SubmissionStatus::WaitingForLO) ;
			}
		}

		if((usedSlots() < activeSlots) && readyToProcess == TRUE) {
			setStatus(query.value(0).toString(),getProcessingStatus()) ;
			proccessSubmission(query.value(0).toString()) ;
		}
	}
}

int queueObject::usedSlots() {

	QSqlQuery query("SELECT count(*) FROM submissions WHERE status > "+QString::number(getIdleStatus())+" AND status < "+QString::number(getTopStatus())) ;
	query.next() ;
	return query.value(0).toInt() ;

}

void queueObject::setStatus(QString ticket, int status) {

	QSqlQuery query("UPDATE submissions SET status = " + QString::number(status) + " WHERE ticket = '" + ticket + "'") ;

}

void queueObject::setVerdict(QString ticket,verdictObject *verdict) {

	setStatus(ticket,SubmissionStatus::Finished) ;

	QSqlQuery query_submission ;

	query_submission.prepare("UPDATE submissions SET verdict = :verdict, stderr = :stderr, result = :result, timeusage = :timeusage, memusage = :memusage WHERE ticket = :ticket") ;
	query_submission.bindValue(":verdict",verdict->getVerdict()) ;
	query_submission.bindValue(":stderr",verdict->getStdErr()) ;
	query_submission.bindValue(":result",verdict->getResult()) ;
	query_submission.bindValue(":ticket",ticket) ;
	query_submission.bindValue(":timeusage",verdict->getTimeUsage()) ;
	query_submission.bindValue(":memusage",verdict->getMemUsage()) ;

	query_submission.exec() ;

	verdict->deleteLater() ;

	QDir workDir(SETTINGS->value("General/WorkDir").toString() + "/" + ticket) ;
	foreach(QFileInfo tmpFileInfo,workDir.entryInfoList()) {
		QFile tmpFile(tmpFileInfo.absoluteFilePath()) ;
		tmpFile.remove() ;
	}
	workDir.rmdir(workDir.absolutePath()) ;

}
