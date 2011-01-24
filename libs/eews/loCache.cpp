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

#include <QHttp>
#include <QUrl>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QtSql>
#include <QDateTime>
#include <QxtHash>
#include "loCache.h"
#include "loObject.h"
#include "enums.h"
#include "eewsServer.h"
#include "pluginInterface.h"

loCache::loCache(int loCacheSize, int loCacheExp, QString loCacheDir) : cacheSize(loCacheSize), cacheExp(loCacheExp), cacheDir(loCacheDir) {

	downloadFiles = new QList<fileRef>() ;

}

loObject* loCache::getLO(QString url) {

	QUrl httpUrl(url) ;
	QxtHash urlHash(QxtHash::Md5,httpUrl.toString().toAscii()) ;
	QString fileName(urlHash.hash().toHex()) ;

	QFile file(cacheDir + "/" + fileName) ;

	loObject *tmpLO = new loObject() ;
	if(tmpLO->setFile(file.fileName())) return tmpLO ;

	return NULL ;

}

void loCache::prepareLO(QString ticket) {

	cleanUp() ;

	QSqlQuery query_ticket ;
	query_ticket.prepare("SELECT lo FROM submissions WHERE ticket = :ticket") ;
	query_ticket.bindValue(":ticket",ticket) ;
	query_ticket.exec() ;
	query_ticket.next() ;

	if(query_ticket.value(0).toString() == QString("DUMMY")) {
		emit submissionReady(ticket) ;
		return ;
	}

	QUrl httpUrl(query_ticket.value(0).toString()) ;
	QxtHash urlHash(QxtHash::Md5,httpUrl.toString().toAscii()) ;
	QString fileName(urlHash.hash().toHex()) ;

	QSqlQuery query ;
	query.prepare("SELECT * FROM locache WHERE url = :url") ;
	query.bindValue(":url",query_ticket.value(0).toString()) ;
	query.exec() ;

	if(!query.next()) {

		QDateTime dateTime(QDateTime::currentDateTime()) ;

		query.prepare("INSERT INTO locache (url,filename,expiration,status) VALUES (:url,:filename,:expiration,:status)") ;
		query.bindValue(":url",query_ticket.value(0).toString()) ;
		query.bindValue(":filename",fileName) ;
		query.bindValue(":expiration",QString::number(dateTime.toTime_t() + cacheExp)) ;
		query.bindValue(":status",1000) ;
		query.exec() ;

		tmpFile = new QFile(cacheDir + "/" + fileName) ;
		tmpFile->open(QIODevice::WriteOnly) ;

		fileRef tmpFileref ;
		tmpFileref.file = tmpFile ;
		tmpFileref.ticket = ticket ;

		http = new QHttp() ;

		connect(http,SIGNAL(requestFinished(int,bool)),this,SLOT(closeFile(int,bool))) ;

		http->setHost(httpUrl.host(),httpUrl.port()) ;

		int tmpId = http->get(httpUrl.path(),tmpFile) ;

		tmpFileref.transId = tmpId ;
		downloadFiles->append(tmpFileref) ;

		query.prepare("UPDATE locache SET status = :status WHERE url = :url") ;
		query.bindValue(":status",tmpId) ;
		query.bindValue(":url",query_ticket.value(0).toString()) ;
		query.exec() ;

		while(1) {
			qApp->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents,500);
			QSqlQuery tmpQuery ;
			tmpQuery.prepare("SELECT * FROM locache WHERE status = :status") ;
			tmpQuery.bindValue(":status",tmpId) ;
			tmpQuery.exec() ;
			if(!tmpQuery.next()) break ;
		}
		qApp->processEvents(QEventLoop::WaitForMoreEvents | QEventLoop::ExcludeUserInputEvents,500);
	} else {
		emit submissionReady(ticket) ;
	}
}

void loCache::refreshLO(QString url) {

	QSqlQuery query ;

	query.prepare("UPDATE locache SET expiration = 0 WHERE url = :url") ;
	query.bindValue(":url",url) ;

	query.exec() ;

	cleanUp() ;

}

void loCache::refreshAll() {

	QSqlQuery query("UPDATE locache SET expiration = 0") ;

	cleanUp() ;

}

void loCache::cleanUp() {

	QSqlQuery query ;
	QDateTime dateTime(QDateTime::currentDateTime()) ;

	query.prepare("SELECT url,filename,expiration FROM locache WHERE expiration < :timenow") ;
	query.bindValue(":timenow",QString::number(dateTime.toTime_t())) ;

	query.exec() ;

	while(query.next()) {

		QSqlQuery tmp_query ;

		tmp_query.prepare("DELETE FROM locache WHERE url = :url") ;
		tmp_query.bindValue(":url",query.value(0).toString()) ;

		tmp_query.exec() ;

		QFile tmp_file(cacheDir + "/" + query.value(1).toString()) ;
		tmp_file.remove() ;

	}

}

void loCache::closeFile(int id,bool error) {

	for(int i=0;i<downloadFiles->size();i++) {
		if(downloadFiles->value(i).transId == id) {
			downloadFiles->value(i).file->close() ;
			downloadFiles->value(i).file->deleteLater() ;
			if(error) {
				QSqlQuery query("UPDATE locache SET status = -1 WHERE status = "+ QString::number(id)) ;
			} else {
				QSqlQuery query("UPDATE locache SET status = 0 WHERE status = " + QString::number(id)) ;
			}
			delete http ;
			emit submissionReady(downloadFiles->value(i).ticket) ;
			downloadFiles->removeAt(i) ;
			return ;
		}
	}
}
