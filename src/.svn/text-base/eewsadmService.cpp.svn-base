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

#include "eewsadmService.h"

// Void implementation of the SOAP methods, to be reimplemented later in an object that inherits both gSoap and QObject

int eewsadmService::version(struct ns2__versionResponse &response) { return SOAP_OK ; }

int eewsadmService::getPluginList(struct ns2__getPluginListResponse &pluginList) { return SOAP_OK ; }

int eewsadmService::getServerConf(std::string fieldName, std::string &fieldContent) { return SOAP_OK ; }

int eewsadmService::setServerConf(std::string fieldName, std::string fieldContent, struct ns2__setServerConfResponse &_param_8) { return SOAP_OK ; }

int eewsadmService::startPlugin(std::string uniqid, int &status) { return SOAP_OK ; }

int eewsadmService::stopPlugin(std::string uniqid, int &status) { return SOAP_OK ; }

int eewsadmService::setPluginAutoload(std::string uniqid, int autoload, int &status) { return SOAP_OK ; }

int eewsadmService::getPluginFieldList(std::string uniqid, struct ns2__getPluginFieldListResponse &pluginFieldListResponse) { return SOAP_OK ; }

int eewsadmService::getPluginFieldValue(std::string uniqid, std::string field, std::string &value) { return SOAP_OK ; }

int eewsadmService::setPluginFieldValue(std::string uniqid, std::string field, std::string value, int &status) { return SOAP_OK ; }

int eewsadmService::getPluginData(std::string uniqid, ns2__getPluginDataResponse &response) { return SOAP_OK ; }

int eewsadmService::getLanguageList(struct ns2__getLanguageListResponse &response) { return SOAP_OK ; }

int eewsadmService::addLanguage(ns2__LanguageData *languageData, int &status) { return SOAP_OK ; }

int eewsadmService::getQueue(std::string queue, struct ns2__getQueueResponse &response) { return SOAP_OK ; }

int eewsadmService::removeLanguage(std::string id, int &status) { return SOAP_OK ; }

int eewsadmService::calibrateLanguage(std::string id, int &status) { return SOAP_OK ; }
