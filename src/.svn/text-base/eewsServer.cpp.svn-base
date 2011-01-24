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

#include <QtSql>
#include "databaseGod.h"
#include "compileQueue.h"
#include "settingsGod.h"
#include "eewsServer.h"
#include "eews.nsmap"
#include "soapServices.h"

eewsServer::eewsServer(int argc, char **argv) : QtService<QCoreApplication>(argc, argv, "EEWS Server") {


}

void eewsServer::start() {

	settings = new QSettings(QSettings::SystemScope,"eews","eews") ;

	settingsGod *stGod = new settingsGod() ;

	if(settings->value("General/DBDriver").toString() == QString("sqlite")) {
		QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE") ;
		database.setDatabaseName(settings->value("General/DBName").toString()) ;
	}

	QSqlDatabase database = QSqlDatabase::database() ;
	if(!database.open()) {
		LOG(database.lastError().text().toAscii()) ;
		exit(1) ;
	}

	LOG("Base de datos iniciada") ;

	locache = new loCache(	settings->value("General/loCacheSize").toInt(),
				settings->value("General/loCacheExp").toInt(),
				settings->value("General/loCacheDir").toString() ) ;
	pluginsCont = new pluginContainer(settings->value("General/PluginDir").toString()) ;
	languages = new languageContainer() ;

	QSqlQuery query ;

	query.exec("SELECT value FROM dbparams WHERE field='dbversion'") ;

	if(!query.next()) {

		LOG("Creating database tables") ;

		databaseGod dbGod ;
		dbGod.createTables() ;
	}

	query.clear() ;

	soapServices *services = new soapServices() ;

}

void eewsServer::pause() {

}

void eewsServer::stop() {

}

void eewsServer::resume() {

}
