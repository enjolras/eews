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

/*! \class languageObject */

#ifndef LANGUAGEOBJECT_H
#define LANGUAGEOBJECT_H

#include <QObject>

class languageObject : public QObject {

	Q_OBJECT

public:
	languageObject(QObject *parent=0) ;
	void setUniqId(QString tmpUniqId) ;
	void setName(QString tmpName) ;
	void setDescription(QString tmpDescription) ;
	void setVersion(QString tmpVersion) ;
	void setCompile(QString tmpCompile) ;
	void setLink(QString tmpLink) ;
	void setRun(QString tmpRun) ;
	void setSrcExt(QString tmpSrcExt) ;
	void setObjExt(QString tmpObjExt) ;
	void setExeExt(QString tmpExeExt) ;
	void setMemOffset(int tmpMemOffset) ;
	void setCalCode(QString tmpCalCode) ;
	void setEnabled(bool tmpEnabled) ;
	QString getUniqId() ;
	QString getName() ;
	QString getDescription() ;
	QString getVersion() ;
	QString getCompile() ;
	QString getLink() ;
	QString getRun() ;
	QString getSrcExt() ;
	QString getObjExt() ;
	QString getExeExt() ;
	int getMemOffset() ;
	QString getCalCode() ;
	bool getEnabled() ;

private:
	QString fieldUniqId ;
	QString fieldName ;
	QString fieldDescription ;
	QString fieldVersion ;
	QString fieldCompile ;
	QString fieldLink ;
	QString fieldRun ;
	QString fieldSrcExt ;
	QString fieldObjExt ;
	QString fieldExeExt ;
	int fieldMemOffset ;
	QString fieldCalCode ;
	bool fieldEnabled ;

} ;

#endif // LANGUAGEOBJECT_H
