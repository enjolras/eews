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

#include <QObject>
#include <QSqlQuery>
#include "pluginInterface.h"
#include "judgeQueue.h"
#include "languageObject.h"
#include "verdictObject.h"
#include "eewsServer.h"

judgeQueue::judgeQueue(QObject *parent) : queueObject(parent) {

	activeSlots = SETTINGS->value("General/JQSlots").toInt() ;

	foreach(QObject *tmpObject,*PLUGINS->getPlugins()) {
		connect(tmpObject,SIGNAL(ticketResult(QString,verdictObject*)),this,SLOT(setVerdict(QString,verdictObject*))) ;
		connect(tmpObject,SIGNAL(ticketResult(QString,verdictObject*)),this,SLOT(deleteFromQueue(QString,verdictObject*))) ;
	}

}

void judgeQueue::proccessSubmission(QString ticket) {

	QSqlQuery query("SELECT plugin,lo,language FROM submissions WHERE ticket='" + ticket + "'" ) ;
	query.next() ;

	languageObject *lang = qobject_cast<languageObject *>(LANGUAGES->getLanguageByUniqId(query.value(2).toString())) ;
	QString command = lang->getRun() ;
	command.replace("$source","code." + lang->getExeExt()) ;

	QObject *tmpObject = PLUGINS->getPluginByUniqId(query.value(0).toString()) ;

	pluginInterface *tmpPlugin = qobject_cast<pluginInterface *>(tmpObject) ;

	setStatus(ticket,SubmissionStatus::JudgeRunning) ;

	tmpPlugin->process(	(tmpPlugin->wantsLO() ? LOCACHE->getLO(query.value(1).toString()) : NULL),
				SETTINGS->value("General/WorkDir").toString(),
				ticket,
				command) ;

}

void judgeQueue::deleteFromQueue(QString ticket, verdictObject *verdict) {

	QSqlQuery query ;
	query.prepare("DELETE FROM "+sqlTable+" WHERE ticket = :ticket") ;
	query.bindValue(":ticket",ticket) ;
	query.exec() ;

}

int judgeQueue::getIdleStatus() { return SubmissionStatus::JudgeIdle ; }
int judgeQueue::getProcessingStatus() { return SubmissionStatus::JudgeProcessing ; }
int judgeQueue::getTopStatus() { return SubmissionStatus::JudgeTop ; }
