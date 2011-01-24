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

/*! \class eewsadmObject
    \brief This class handles the eewsadm SOAP webservice for managing the EEWS */

#ifndef EEWSADMOBJECT_H
#define EEWSADMOBJECT_H

#include <QThread>
#include <QList>
#include "eewsadmService.h"
#include <QString>

class QObject ;
class languageObject ;

class eewsadmObject : public QThread, public eewsadmService {

	Q_OBJECT

public:
	//! The class constructor
	/*!	\param settingsPointer Pointer to the global QSettings object
		\param pluginPointer Pointer to the global pluginContainer object */
	eewsadmObject() ;
	//! Reimplementation of the run() method to comply with QThread inheritance
	void run() ;

private:
	//! Answers the version SOAP request
	/*!	\return SOAP_OK if the command was succesful
		\param response Pointer to the ns2__versionResponse structure were we have to load the query results */
	int version(struct ns2__versionResponse &response) ;

	//! Answers the getPluginList SOAP request
	/*!	\return SOAP_OK if the command was succesful
		\param pluginList Pointer to the ns2__getPluginListResponse structure were we have to load the query results */
	int getPluginList(struct ns2__getPluginListResponse &pluginList) ;

	int getServerConf(std::string fieldName, std::string &fieldContent) ;

	int setServerConf(std::string fieldName, std::string fieldContent, struct ns2__setServerConfResponse &_param_8) ;

	int startPlugin(std::string uniqid, int &status);
	int stopPlugin(std::string uniqid, int &status);
	int setPluginAutoload(std::string uniqid, int autoload, int &status);
	int getPluginFieldList(std::string uniqid, struct ns2__getPluginFieldListResponse &pluginFieldListResponse);
	int getPluginFieldValue(std::string uniqid, std::string field, std::string &value);
	int setPluginFieldValue(std::string uniqid, std::string field, std::string value, int &status);
	int getPluginData(std::string uniqid, ns2__getPluginDataResponse &response);
	int getLanguageList(struct ns2__getLanguageListResponse &response) ;
	int addLanguage(ns2__LanguageData *languageData, int &status) ;
	int getQueue(std::string queue, struct ns2__getQueueResponse &response) ;
	int removeLanguage(std::string id, int &status) ;
	int calibrateLanguage(std::string id, int &status) ;

signals:
	void startLanguageCalibration(QString language) ;

} ;

#endif // EEWSADMOBJECT_H
