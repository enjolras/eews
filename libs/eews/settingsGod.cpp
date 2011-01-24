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

#include <QStringList>
#include "settingsGod.h"
#include "eewsServer.h"

settingsGod::settingsGod() {

	QStringList fieldNames ;
	fieldNames	<< "General/SvcPort"
			<< "General/AdmPort"
			<< "General/AdminEmail"
			<< "General/Owner"
			<< "General/DBDriver"
			<< "General/DBHost"
			<< "General/DBPort"
			<< "General/DBName"
			<< "General/DBPrefix"
			<< "General/DBUsername"
			<< "General/DBPassword"
			<< "General/loCacheSize"
			<< "General/loCacheExp"
			<< "General/loCacheDir"
			<< "General/WorkDir"
			<< "General/CQSlots"
			<< "General/JQSlots"
			<< "General/PluginDir" ;

	QStringList fieldValues	;
	fieldValues	<< "8080"			// General/SvcPort
			<< "8090"			// General/AdmPort
			<< "some@email.here"		// General/AdminEmail
			<< "Owner Name"			// General/Owner
			<< "sqlite"			// General/DBDriver
			<< "localhost"			// General/DBHost
			<< "3306"			// General/DBPort
			<< "/var/edujudge/eews.sql"	// General/DBName
			<< "eews_"			// General/DBPrefix
			<< "username"			// General/DBUsername
			<< "password"			// General/DBPassword
			<< "512"			// General/loCacheSize
			<< "86400"			// General/loCacheExp
			<< "/var/edujudge/cache"	// General/loCacheDir
			<< "/var/edujudge/tmp"		// General/WorkDir
			<< "5"				// General/CQSlots
			<< "5"				// General/JQSlots
			<< "/usr/share/eews/plugins" ;	// General/PluginDir


	for(int i=0;i<fieldNames.size();i++) {
		if(SETTINGS->value(fieldNames.at(i),-1).toInt() == -1) {
			SETTINGS->setValue(fieldNames.at(i),fieldValues.at(i)) ;
			LOG(QString("Setting '" + fieldNames.at(i) + "' to its default value of '" + fieldValues.at(i) + "'").toAscii()) ;
		}
	}

	this->deleteLater() ;

}
