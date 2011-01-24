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
#include <QStringList>
#include <QDir>
#include <QList>
#include <QtSql>
#include "pluginInterface.h"
#include "eewsadmObject.h"
#include "eewsServer.h"
#include "eewsProcess.h"
#include "languageObject.h"

// Constructor
eewsadmObject::eewsadmObject()  {

}

void eewsadmObject::run() {

	// The sockets
	int m, s ;

	// GSoap socket binding
	m = this->bind(NULL,SETTINGS->value("General/AdmPort").toInt(),100) ;

	// Check if the socket is correctly open
	if(m<0) {
		// Print the error message if the socket failed
		struct SOAP_ENV__Fault *tmpFault = this->fault ;
		QString tmpStr = QString("SOAP could not bind. Error was: %1").arg(tmpFault->faultstring) ;
		LOG(tmpStr.toAscii()) ;
	}
	else {  // The socket is correctly opened, so start the main loop to accept connections and inform the log
		QString tmpStr = QString("Connection succesful. Socket: %1").arg(m) ;
		LOG(tmpStr.toAscii()) ;

		// Endless loop with a counter
		for(int i=1;;i++) {

			// Wait for an incoming connection
			s = this->accept() ;
			if(s<0) {  // Check for errors and inform the log
				struct SOAP_ENV__Fault *tmpFault = this->fault ;
				QString tmpStr = QString("Could not accept connection. Error was: %1").
					arg(tmpFault->faultstring) ;
				LOG(tmpStr.toAscii()) ;
				break ;
			}

			// Connection opened, get the peer IP and inform the log
			QString tmpStr = QString("Connection accepted from %1.%2.%3.%4").
				arg((this->ip>>24)&0xFF).
				arg((this->ip>>16)&0xFF).
				arg((this->ip>>8)&0xFF).
				arg(this->ip&0xFF) ;
			LOG(tmpStr.toAscii()) ;

			// Serve the SOAP request
			if(this->serve()!=SOAP_OK) {  // Check if the request is valid
				struct SOAP_ENV__Fault *tmpFault = this->fault ;
				QString tmpStr = QString("Could not proccess request. Error was: %1").
					arg(tmpFault->faultstring) ;
				LOG(tmpStr.toAscii()) ;
			}

			// Print to the logs that everything is OK
			LOG("Request served.") ;
		}
	}
	// If the loop ends, suicide the object
	this->deleteLater() ;
	return ;
}

// Response for the "version" SOAP request
int eewsadmObject::version(struct ns2__versionResponse &response) {

	// Protocol version is always 1 for now
	response.id = 1 ;

	// Free text version string to make it more verbose and nicer
	response.desc = QString("EEWSADM v0.5<br/><a href=\"www.edujudge.eu\">www.edujudge.eu</a>").toStdString() ;

	// Return that the request went right
	return SOAP_OK ;

}


// Response for the getPluginFieldList SOAP request
int eewsadmObject::getPluginFieldList(std::string uniqid, struct ns2__getPluginFieldListResponse &pluginFieldListResponse) {

	// Load the required plugin from the container
	QObject *tmpObject = PLUGINS->getPluginByUniqId(QString::fromStdString(uniqid)) ;

	// Cast the retrieved object to make it look like a plugin
	pluginInterface* tmpPlugin = qobject_cast<pluginInterface *>(tmpObject) ;

	// Instantiate a PluginFieldList object to store the data
	PluginFieldList *tmpPluginFieldList = new PluginFieldList ;

	// Instantiate the response structure as an array of pointers
	ns2__PluginField **tmpPluginFieldArray = new ns2__PluginField* [0] ;

	// Prepare a counter
	int ct=0 ;

	// FOREACH loop that will iterate to every plugin field available
	foreach(QStringList* fieldSpec,*tmpPlugin->getFieldList()) {

		// Instantiate a ns2__PluginField object
		ns2__PluginField *tmpPluginField = new ns2__PluginField ;

		// Load the field data as provided by the plugin
		tmpPluginField->fieldname	= fieldSpec->at(0).toStdString() ;
		tmpPluginField->fieldtype	= fieldSpec->at(1).toStdString() ;
		tmpPluginField->fielddefault	= fieldSpec->at(2).toStdString() ;
		tmpPluginField->fieldmin	= fieldSpec->at(3).toInt() ;
		tmpPluginField->fieldmax	= fieldSpec->at(4).toInt() ;

		// Rename the previously created ns2__PluginField pointer array
		ns2__PluginField **vtmpPluginFieldArray = tmpPluginFieldArray ;

		// Instantiate a new ns2__PluginField pointer array with one more element
		tmpPluginFieldArray = new ns2__PluginField* [ct+1] ;

		// Copy the old data to the new instance
		memcpy(tmpPluginFieldArray,vtmpPluginFieldArray,sizeof(ns2__PluginField*[ct])) ;

		// Delete the old data
		delete [] vtmpPluginFieldArray ;

		// Add the new field information to the array and increase the counter
		tmpPluginFieldArray[ct++] = tmpPluginField ;
	}

	// Provide the needed information to the response structure
	// The pointer of the plugin field information array
	tmpPluginFieldList->__ptr = tmpPluginFieldArray ;
	// And the count of the number of elements
	tmpPluginFieldList->__size = ct ;

	// Finally add all the previous stuff to the response structure
	pluginFieldListResponse.pluginFieldList = tmpPluginFieldList ;

	// Return that everything was fine
	return SOAP_OK ;
}

// Response for the getPluingList SOAP request
int eewsadmObject::getPluginList(struct ns2__getPluginListResponse &pluginList) {

	// Instantiate a new PluginList object
	PluginList *tmpPluginList = new PluginList ;

	// Instantiate a new ns2__PluginData array of pointers
	ns2__PluginData **tmpPluginDataArray = new ns2__PluginData* [0] ;

	// Create a counter
	int ct=0 ;

	// Start a FOREACH loop to go through all the available plugins
	foreach(QObject *tmpObject,*PLUGINS->getPlugins()) {

		// Cast the pluginObject to its correct interface
		pluginInterface *tmpPlugin = qobject_cast<pluginInterface *>(tmpObject) ;

		// Create a new ns2__PluginData object
		ns2__PluginData *tmpPluginData = new ns2__PluginData ;

		// Load the information as provided by the plugin
		tmpPluginData->uniqid   = tmpPlugin->getUniqId()->toStdString() ;
		tmpPluginData->desc     = tmpPlugin->getDesc()->toStdString() ;
		tmpPluginData->version  = tmpPlugin->getVersion() ;
		tmpPluginData->status   = (int)tmpPlugin->getStatus() ;
		tmpPluginData->autoload = SETTINGS->value(*tmpPlugin->getUniqId() + QString("/Autoload")).toInt() ;

		// Rename the tmpPluginDataArray array
		ns2__PluginData **vtmpPluginDataArray = tmpPluginDataArray ;

		// Create a new ns2__PluginData array of pointers with one more member
		tmpPluginDataArray = new ns2__PluginData* [ct+1] ;

		// Copy the previous data to the new array
		memcpy(tmpPluginDataArray,vtmpPluginDataArray,sizeof(ns2__PluginData*[ct])) ;

		// Delete the temporary array
		delete [] vtmpPluginDataArray ;

		// Add the new plugin data to the end of the array and increase the counter
		tmpPluginDataArray[ct++] = tmpPluginData ;
	}

	// Finish completing the response structure data
	// Pointer to the plugin data
	tmpPluginList->__ptr = tmpPluginDataArray ;
	// Elements counter
	tmpPluginList->__size = ct ;

	// Asign all the stuff to the response structure
	pluginList.pluginList = tmpPluginList ;

	// Say that everything was right
	return SOAP_OK ;

}

// getServerConf SOAP request handler
int eewsadmObject::getServerConf(std::string fieldName, std::string &fieldContent) {

	fieldContent = QString(SETTINGS->value("General/" + QString::fromStdString(fieldName)).toString()).toStdString() ;

	// Say that everything was right
	return SOAP_OK ;
}

int eewsadmObject::setServerConf(std::string fieldName, std::string fieldContent, struct ns2__setServerConfResponse &_param_8) {

	SETTINGS->setValue("General/" + QString::fromStdString(fieldName),QString::fromStdString(fieldContent)) ;

	_param_8.configStatus = 0 ;
	_param_8.errorMessage = QString("All OK").toStdString() ;

	return SOAP_OK ;
}

int eewsadmObject::startPlugin(std::string uniqid, int &status) {
	QObject *tmpObject = PLUGINS->getPluginByUniqId(QString::fromStdString(uniqid)) ;
	pluginInterface* tmpPlugin = qobject_cast<pluginInterface *>(tmpObject) ;
	tmpPlugin->startPlugin() ;
	status = TRUE ;
	return SOAP_OK ;
}

int eewsadmObject::stopPlugin(std::string uniqid, int &status) {
	QObject *tmpObject = PLUGINS->getPluginByUniqId(QString::fromStdString(uniqid)) ;
	pluginInterface* tmpPlugin = qobject_cast<pluginInterface *>(tmpObject) ;
	tmpPlugin->stopPlugin() ;
	status = TRUE ;
	return SOAP_OK ;
}

int eewsadmObject::setPluginAutoload(std::string uniqid, int autoload, int &status) {
	SETTINGS->setValue(QString::fromStdString(uniqid) + QString("/Autoload"),autoload) ;
	status = TRUE ;
	return SOAP_OK ;
}

int eewsadmObject::getPluginFieldValue(std::string uniqid, std::string field, std::string &value) {

	QObject *tmpObject = PLUGINS->getPluginByUniqId(QString::fromStdString(uniqid)) ;
	pluginInterface* tmpPlugin = qobject_cast<pluginInterface *>(tmpObject) ;

	QString tmpFieldDefault ;

	foreach(QStringList* fieldSpec,*tmpPlugin->getFieldList()) {
		if(fieldSpec->at(0).toStdString() == field) {
			tmpFieldDefault = fieldSpec->at(2) ;
		}
	}

	value = QString(SETTINGS->value(*tmpPlugin->getUniqId() + QString("/") + QString::fromStdString(field),tmpFieldDefault).toString()).toStdString() ;

	return SOAP_OK ;
}

int eewsadmObject::setPluginFieldValue(std::string uniqid, std::string field, std::string value, int &status) {
	SETTINGS->setValue(QString::fromStdString(uniqid)+"/"+QString::fromStdString(field),QString::fromStdString(value)) ;
	status = TRUE ;
	return SOAP_OK ;
}

int eewsadmObject::getPluginData(std::string uniqid, ns2__getPluginDataResponse &response) {

	QObject *tmpObject = PLUGINS->getPluginByUniqId(QString::fromStdString(uniqid)) ;
	pluginInterface* tmpPlugin = qobject_cast<pluginInterface *>(tmpObject) ;

	ns2__PluginData *tmpPluginData = new ns2__PluginData ;

	tmpPluginData->uniqid   = tmpPlugin->getUniqId()->toStdString() ;
	tmpPluginData->desc     = tmpPlugin->getDesc()->toStdString() ;
	tmpPluginData->version  = tmpPlugin->getVersion() ;
	tmpPluginData->status   = (int)tmpPlugin->getStatus() ;
	tmpPluginData->autoload = SETTINGS->value(*tmpPlugin->getUniqId() + QString("/Autoload")).toInt() ;

	response.pluginData = tmpPluginData ;

	return SOAP_OK ;

}

int eewsadmObject::getLanguageList(struct ns2__getLanguageListResponse &response) {

	LanguageList *tmpLanguageList = new LanguageList ;
	ns2__LanguageData **tmpLanguageDataArray = new ns2__LanguageData* [0] ;

	QSqlQuery query("SELECT uniqid,name,version,description,compile,link,run,srcext,objext,exeext,memoffset,calcode FROM languages ORDER BY uniqid") ;
	
	int ct=0 ;

	while(query.next()) {
		ns2__LanguageData *tmpLanguageData = new ns2__LanguageData ;

		tmpLanguageData->uniqid = query.value(0).toString().toStdString() ;
		tmpLanguageData->name = query.value(1).toString().toStdString() ;
		tmpLanguageData->version = query.value(2).toString().toStdString() ;
		tmpLanguageData->description = query.value(3).toString().toStdString() ;
		tmpLanguageData->compile = query.value(4).toString().toStdString() ;
		tmpLanguageData->link = query.value(5).toString().toStdString() ;
		tmpLanguageData->run = query.value(6).toString().toStdString() ;
		tmpLanguageData->srcext = query.value(7).toString().toStdString() ;
		tmpLanguageData->objext = query.value(8).toString().toStdString() ;
		tmpLanguageData->exeext = query.value(9).toString().toStdString() ;
		tmpLanguageData->memoffset = query.value(10).toInt() ;
		tmpLanguageData->calcode = query.value(11).toString().toStdString() ;

		ns2__LanguageData **vtmpLanguageDataArray = tmpLanguageDataArray ;
		tmpLanguageDataArray = new ns2__LanguageData* [ct+1] ;
		memcpy(tmpLanguageDataArray,vtmpLanguageDataArray,sizeof(ns2__LanguageData*[ct])) ;
		delete [] vtmpLanguageDataArray ;

		tmpLanguageDataArray[ct++] = tmpLanguageData ;
	}

	tmpLanguageList->__ptr = tmpLanguageDataArray ;
	tmpLanguageList->__size = ct ;

	response.languageList = tmpLanguageList ;

	return SOAP_OK ;
}

int eewsadmObject::addLanguage(ns2__LanguageData *languageData, int &status) {

	QSqlQuery query ;

	query.prepare("INSERT INTO languages (uniqid,name,description,version,compile,link,run,srcext,objext,exeext,calcode) "
		"VALUES (:uniqid, :name, :description, :version, :compile, :link, :run, :srcext, :objext, :exeext, :calcode)") ;
	query.bindValue(":uniqid",QString::fromStdString(languageData->uniqid)) ;
	query.bindValue(":name",QString::fromStdString(languageData->name)) ;
	query.bindValue(":description",QString::fromStdString(languageData->description)) ;
	query.bindValue(":version",QString::fromStdString(languageData->version)) ;
	query.bindValue(":compile",QString::fromStdString(languageData->compile)) ;
	query.bindValue(":link",QString::fromStdString(languageData->link)) ;
	query.bindValue(":run",QString::fromStdString(languageData->run)) ;
	query.bindValue(":srcext",QString::fromStdString(languageData->srcext)) ;
	query.bindValue(":objext",QString::fromStdString(languageData->objext)) ;
	query.bindValue(":exeext",QString::fromStdString(languageData->exeext)) ;
	query.bindValue(":calcode",QString::fromStdString(languageData->calcode)) ;

	query.exec() ;

	emit startLanguageCalibration(QString::fromStdString(languageData->uniqid)) ;

	return SOAP_OK ;
}

int eewsadmObject::getQueue(std::string queue, struct ns2__getQueueResponse &response) {

	QueueList *tmpQueueList = new QueueList ;
	ns2__QueueItem **tmpQueueDataArray = new ns2__QueueItem* [0] ;

	QSqlQuery query ;

	int ct=0 ;

	query.exec("SELECT ticket,priority,timestamp FROM " + QString::fromStdString(queue) + "queue") ;

	while(query.next()) {
		ns2__QueueItem *tmpQueueData = new ns2__QueueItem ;

		tmpQueueData->ticket = query.value(0).toString().toStdString() ;
		tmpQueueData->priority = query.value(1).toInt() ;
		tmpQueueData->timestamp = query.value(2).toInt() ;

		QSqlQuery queryb("SELECT plugin,language FROM submissions WHERE ticket = '"
			+ query.value(0).toString() + "'") ;

		queryb.next() ;
		tmpQueueData->plugin = queryb.value(0).toString().toStdString() ;
		tmpQueueData->language = queryb.value(1).toString().toStdString() ;

		ns2__QueueItem **vtmpQueueDataArray = tmpQueueDataArray ;
		tmpQueueDataArray = new ns2__QueueItem* [ct+1] ;
		memcpy(tmpQueueDataArray,vtmpQueueDataArray,sizeof(ns2__QueueItem*[ct])) ;
		delete [] vtmpQueueDataArray ;

		tmpQueueDataArray[ct++] = tmpQueueData ;
	}

	tmpQueueList->__ptr = tmpQueueDataArray ;
	tmpQueueList->__size = ct ;

	response.queueList = tmpQueueList ;

	return SOAP_OK ;

}

int eewsadmObject::removeLanguage(std::string id, int &status) {

	QSqlQuery query(QString("DELETE FROM languages WHERE uniqid LIKE '%1'").arg(QString::fromStdString(id))) ;

	return SOAP_OK ;

}

int eewsadmObject::calibrateLanguage(std::string id, int &status) {

	emit startLanguageCalibration(QString::fromStdString(id)) ;

	status=1 ;
	return SOAP_OK ;

}
