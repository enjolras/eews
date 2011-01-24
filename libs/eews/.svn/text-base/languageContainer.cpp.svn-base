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
#include <QStringList>
#include "eewsServer.h"
#include "languageContainer.h"
#include "languageObject.h"

languageContainer::languageContainer(QObject *parent) : QObject(parent) {

	languages = new QList<QObject*> ;

	reloadLanguages() ;

}

void languageContainer::reloadLanguages() {

	languages->clear() ;

	QSqlQuery query("SELECT uniqid,name,version,description,compile,link,run,srcext,objext,exeext,memoffset,calcode,enabled FROM languages") ;

	while(query.next()) {
		languageObject *tmpLanguageObject = new languageObject() ;

		tmpLanguageObject->setUniqId(query.value(0).toString()) ;
		tmpLanguageObject->setName(query.value(1).toString()) ;
		tmpLanguageObject->setVersion(query.value(2).toString()) ;
		tmpLanguageObject->setDescription(query.value(3).toString()) ;
		tmpLanguageObject->setCompile(query.value(4).toString()) ;
		tmpLanguageObject->setLink(query.value(5).toString()) ;
		tmpLanguageObject->setRun(query.value(6).toString()) ;
		tmpLanguageObject->setSrcExt(query.value(7).toString()) ;
		tmpLanguageObject->setObjExt(query.value(8).toString()) ;
		tmpLanguageObject->setExeExt(query.value(9).toString()) ;
		tmpLanguageObject->setMemOffset(query.value(10).toInt()) ;
		tmpLanguageObject->setCalCode(query.value(11).toString()) ;
		tmpLanguageObject->setEnabled(query.value(12).toBool()) ;

		languages->append(tmpLanguageObject) ;

	}

}

QObject* languageContainer::getLanguageByUniqId(QString uniqId) {

	foreach(QObject *tmpObject,*languages) {
		languageObject *tmpLanguage = qobject_cast<languageObject *>(tmpObject) ;
		if(tmpLanguage->getUniqId() == uniqId) return tmpObject ;
	}

	return NULL ;

}

QStringList languageContainer::getLanguageUniqIds() {

	QStringList languageUniqIds ;

	foreach(QObject *tmpObject,*languages) {
		languageObject *tmpLanguage = qobject_cast<languageObject *>(tmpObject) ;
		languageUniqIds.append(tmpLanguage->getUniqId()) ;
	}

	return languageUniqIds ;

}
