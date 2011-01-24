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

/*! \class pluginInterface */

#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include "loObject.h"

class verdictObject ;
class QString ;
class QStringList ;

class pluginInterface {

public:
	virtual ~pluginInterface() {}

	virtual QString* getDesc() = 0;
	virtual QString* getUniqId() = 0;
	virtual int getVersion() = 0;
	virtual bool startPlugin() = 0;
	virtual bool stopPlugin() = 0;
	virtual bool getStatus() = 0;
	virtual bool reloadConfig() = 0;
	virtual QList< QStringList* >* getFieldList() = 0;
	virtual bool wantsLO() = 0 ;
	virtual bool isPublic() = 0 ;

	virtual void process(loObject *lo,QString workdir,QString ticket,QString command) = 0;

signals:
	virtual void ticketResult(QString ticket,verdictObject *verdict) = 0;

} ;

Q_DECLARE_INTERFACE(pluginInterface,"eu.edujudge.eews.pluginInterface/1.0") ;

#endif // PLUGININTERFACE_H

