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

#include <QString>
#include <QList>
#include <QtSql>
#include <QDateTime>
#include <QxtHash>
#include "eewsServer.h"
#include "pluginInterface.h"
#include "eewsObject.h"
#include "compileQueue.h"
#include "judgeQueue.h"
#include "qtservice.h"
#include "languageObject.h"
#include "verdictObject.h"

eewsObject::eewsObject() {

	/* Instantiate a compile queue */
	compileQueue *cQueue = new compileQueue(this) ;
	cQueue->setTable(QString("compilequeue")) ;

	/* Instantiate a judge queue */
	judgeQueue *jQueue = new judgeQueue(this) ;
	jQueue->setTable(QString("judgequeue")) ;

	connect(cQueue,SIGNAL(finishedSubmission(QString)),jQueue,SLOT(addSubmission(QString))) ;
	connect(LOCACHE,SIGNAL(submissionReady(QString)),cQueue,SLOT(addSubmission(QString))) ;

	if(PLUGINS->getPluginByUniqId("CAL") != NULL) {
		connect(PLUGINS->getPluginByUniqId("CAL"), SIGNAL(ticketResult(QString,verdictObject*)), this, SLOT(getCalibrationData(QString,verdictObject*))) ;
	}

}

// Reimplementation of the run method for QThreads
void eewsObject::run() {

	// The sockets
	int m, s ;

	// GSoap socket binding
	m = this->bind(NULL,SETTINGS->value("General/SvcPort").toInt(),100) ;

	// Check if the socket is correctly open
	if(m<0) {
		// Print the error message if the socket failed
		SOAP_ENV__Fault *tmpFault = this->fault ;
		QString tmpStr = QString("SOAP could not bind. Error was: %1").arg(tmpFault->faultstring) ;
		LOG(tmpStr.toAscii()) ;
	}
	else {  // The socket is correctly opened, so start the main loop to accept connections

		LOG(QString("Connection succesful. Socket: %1").arg(m)) ;

		for(int i=1;;i++) {
			// Wait for an incoming connection
			s = this->accept() ;
			if(s<0) {  // Check for errors
				SOAP_ENV__Fault *tmpFault = this->fault ;
				QString tmpStr = QString("Could not accept connection. Error was: %1").
					arg(tmpFault->faultstring) ;
				LOG(tmpStr.toAscii()) ;
				break ;
			}
			// Connection opened, get the peer IP and print it
			QString tmpStr = QString("Connection accepted from %1.%2.%3.%4").
				arg((this->ip>>24)&0xFF).
				arg((this->ip>>16)&0xFF).
				arg((this->ip>>8)&0xFF).
				arg(this->ip&0xFF) ;
			LOG(tmpStr.toAscii()) ;
			// Serve the SOAP request
			if(this->serve()!=SOAP_OK) {  // Check if the request is valid
				SOAP_ENV__Fault *tmpFault = this->fault ;
				QString tmpStr = QString("Could not proccess request. Error was: %1").
					arg(tmpFault->faultstring) ;
				LOG(tmpStr.toAscii()) ;
			}
			// Print to the logs that everything is OK
			LOG("Request served.") ;
		}
	}
}

// Response for the "getCapabilities" SOAP request
int eewsObject::getCapabilities(struct ns1__getCapabilitiesResponse &response) {

	languageL *tmpLanguages = new languageL ;
	ns1__languageInfo **tmpLanguageInfoArray = new ns1__languageInfo* [0] ;

	pluginL *tmpPlugins = new pluginL ;
	ns1__pluginInfo **tmpPluginInfoArray = new ns1__pluginInfo* [0] ;

	QSqlQuery query("SELECT uniqid,name,version,description FROM languages") ;
	
	int ct=0 ;

	while(query.next()) {
		ns1__languageInfo *tmpLanguageInfo = new ns1__languageInfo ;

		tmpLanguageInfo->uniqid = query.value(0).toString().toStdString() ;
		tmpLanguageInfo->name = query.value(1).toString().toStdString() ;
		tmpLanguageInfo->version = query.value(2).toString().toStdString() ;
		tmpLanguageInfo->description = query.value(3).toString().toStdString() ;

		ns1__languageInfo **vtmpLanguageInfoArray = tmpLanguageInfoArray ;
		tmpLanguageInfoArray = new ns1__languageInfo* [ct+1] ;
		memcpy(tmpLanguageInfoArray,vtmpLanguageInfoArray,sizeof(ns1__languageInfo*[ct])) ;
		delete [] vtmpLanguageInfoArray ;

		tmpLanguageInfoArray[ct++] = tmpLanguageInfo ;
	}

	tmpLanguages->__ptr = tmpLanguageInfoArray ;
	tmpLanguages->__size = ct ;

	response.languages = tmpLanguages ;

	ct=0 ;
	foreach(QObject *tmpObject,*PLUGINS->getPlugins()) {
		pluginInterface *tmpPlugin = qobject_cast<pluginInterface *>(tmpObject) ;

		if(tmpPlugin->isPublic()) {

			ns1__pluginInfo *tmpPluginInfo = new ns1__pluginInfo ;

			tmpPluginInfo->uniqid   = tmpPlugin->getUniqId()->toStdString() ;
			tmpPluginInfo->desc     = tmpPlugin->getDesc()->toStdString() ;
			tmpPluginInfo->version  = tmpPlugin->getVersion() ;
			tmpPluginInfo->status   = (int)tmpPlugin->getStatus() ;

			ns1__pluginInfo **vtmpPluginInfoArray = tmpPluginInfoArray ;
			tmpPluginInfoArray = new ns1__pluginInfo* [ct+1] ;
			memcpy(tmpPluginInfoArray,vtmpPluginInfoArray,sizeof(ns1__pluginInfo*[ct])) ;
			delete [] vtmpPluginInfoArray ;

			tmpPluginInfoArray[ct++] = tmpPluginInfo ;
		}
	}


	tmpPlugins->__ptr = tmpPluginInfoArray ;
	tmpPlugins->__size = ct ;

	response.plugins = tmpPlugins ;

	response.protocol = 1 ;
	response.version = 1 ;
	response.versionString = QString("Evaluation Engine Web Services v0.7").toStdString() ;
	response.adminEmail = QString(SETTINGS->value("General/AdminEmail").toString()).toStdString();
	response.owner = QString(SETTINGS->value("General/Owner").toString()).toStdString();

	return SOAP_OK;

}

int eewsObject::submitCode(ns1__submissionData *data, std::string &ticket) {

	QDateTime now = QDateTime::currentDateTime();
	srand(now.toTime_t()+QString::fromStdString(data->code).size()) ;

	QxtHash numberHash(QxtHash::Md5,QString::number(rand()).toAscii()) ;
	QxtHash codeHash(QxtHash::Md5,QString::fromStdString(data->code).toAscii()) ;
	QxtHash ticketHash(QxtHash::Md5) ;
	ticketHash.append(numberHash.hash()) ;
	ticketHash.append(codeHash.hash()) ;

	QString ticketId(ticketHash.hash().toHex()) ;

	QSqlQuery query ;
	query.prepare("INSERT INTO submissions (ticket,language,plugin,code,lo,priority,status) VALUES (:ticket, :language, :plugin, :code, :lo, :priority, :status)") ;
	query.bindValue(":ticket",ticketId) ;
	query.bindValue(":language",QString::fromStdString(data->language)) ;
	query.bindValue(":plugin",QString::fromStdString(data->plugin)) ;
	query.bindValue(":code",QString::fromStdString(data->code)) ;
	query.bindValue(":lo",QString::fromStdString(data->lo)) ;
	query.bindValue(":priority",data->priority) ;
	query.bindValue(":status",SubmissionStatus::CompileIdle) ;

	query.exec() ;

	ticket = ticketId.toStdString() ;

	LOCACHE->prepareLO(ticketId) ;

	return SOAP_OK ;
}

int eewsObject::getTicketResult(std::string ticket, struct ns1__getTicketResultResponse &response) {

	QSqlQuery query("SELECT verdict,result,stderr,timeusage,memusage,status,statusstr,resultstr FROM submissions WHERE ticket = '"
		+ QString::fromStdString(ticket) + "'") ;

	if(!query.next()) {
		return SOAP_ERR ;
	}

	ns1__ticketResult *result = new ns1__ticketResult ;

	result->verdict = query.value(0).toInt() ;
	result->result = query.value(1).toInt() ;
	result->stderr = query.value(2).toString().toStdString() ;
	result->timeusage = query.value(3).toInt() ;
	result->memusage = query.value(4).toInt() ;
	result->queuepos = 0 ;
	result->status = query.value(5).toInt() ;
	result->statusstr = query.value(6).toString().toStdString() ;
	result->resultstr = query.value(7).toString().toStdString() ;

	response.ticketResult = result ;

	if(query.value(5).toInt() == SubmissionStatus::Finished) {
		QSqlQuery queryDelete("DELETE FROM submissions WHERE ticket = '" + QString::fromStdString(ticket) + "'") ;
	}

	return SOAP_OK ;
}

int eewsObject::getTicketDump(struct ns1__getTicketDumpResponse &response) {
	return SOAP_OK ;
}

void eewsObject::calibrateLanguage(QString argLang) {

	ns1__submissionData *tmpSubmission = new ns1__submissionData ;
	QObject *tmpObject = LANGUAGES->getLanguageByUniqId(argLang) ;
	languageObject *tmpLanguage = qobject_cast<languageObject *>(tmpObject) ;

	tmpSubmission->language = tmpLanguage->getUniqId().toStdString() ;
	tmpSubmission->plugin = QString("CAL").toStdString() ;
	tmpSubmission->priority = 0 ;
	tmpSubmission->code = tmpLanguage->getCalCode().toStdString() ;
	tmpSubmission->lo = QString("DUMMY").toStdString() ;

	std::string ticket ;

	submitCode(tmpSubmission,ticket) ;

}

void eewsObject::getCalibrationData(QString ticket, verdictObject *verdict) {

	QSqlQuery query ;
	query.prepare("SELECT memusage,language FROM submissions WHERE ticket = :ticket") ;
	query.bindValue(":ticket",ticket) ;
	query.exec() ;

	query.next() ;

	int memoffset = query.value(0).toInt() ;
	QString language = query.value(1).toString() ;

	query.prepare("UPDATE languages SET memoffset = :memoffset WHERE uniqid = :lang") ;
	query.bindValue(":memoffset",memoffset) ;
	query.bindValue(":lang",language) ;
	query.exec() ;

	query.prepare("DELETE FROM submissions WHERE ticket = :ticket") ;
	query.bindValue(":ticket",ticket) ;
	query.exec() ;

}
