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
#include <QString>
#include <QDir>
#include <QPluginLoader>
#include <QList>
#include "pluginInterface.h"
#include "pluginContainer.h"
#include "eewsServer.h"

pluginContainer::pluginContainer(QString pluginDir) : pluginPath(pluginDir) {

	plugins = new QList<QObject*> ;
	reloadPlugins() ;

}

QList<QObject*>* pluginContainer::getPlugins() {

	return plugins ;

}

void pluginContainer::reloadPlugins(QString pluginDir) {

	pluginPath = pluginDir ;
	reloadPlugins() ;

}

void pluginContainer::reloadPlugins() {

	plugins->clear() ;
	QDir dir(pluginPath) ;
	QStringList files = dir.entryList(QDir::Files) ;
	foreach(QString fileName,files) {
		QPluginLoader loader(dir.absoluteFilePath(fileName)) ;
		tmpPlugin = loader.instance() ;
		if(tmpPlugin) {
			plugins->append(tmpPlugin) ;
			pluginInterface *tmpRealPlugin = qobject_cast<pluginInterface *>(tmpPlugin) ;
			if(SETTINGS->value(*tmpRealPlugin->getUniqId()+QString("/Autoload")).toInt() == 1) {
				tmpRealPlugin->startPlugin() ;
			}
		}
	}

}

QObject* pluginContainer::getPluginByUniqId(QString uniqId) {

	foreach(QObject *tmpObject,*plugins) {
		pluginInterface *tmpPlugin = qobject_cast<pluginInterface *>(tmpObject) ;
		if(tmpPlugin->getUniqId() == uniqId) return tmpObject ;
	}

	return NULL ;

}
