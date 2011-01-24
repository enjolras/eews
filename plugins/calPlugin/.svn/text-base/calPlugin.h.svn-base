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

#ifndef CALPLUGIN_H
#define CALPLUGIN_H

#include <QObject>
#include <pluginInterface.h>
#include <QList>
#include "eewsProcess.h"

class calPlugin : public QObject, public pluginInterface {

	Q_OBJECT
	Q_INTERFACES(pluginInterface)

public:
	calPlugin() ;
	QString* getDesc() ;
	QString* getUniqId() ;
	int getVersion() ;
	bool startPlugin() ;
	bool stopPlugin() ;
	bool getStatus() ;
	bool reloadConfig() ;
	QList< QStringList* >* getFieldList() ;
	bool wantsLO() ;
	bool isPublic() ;

	void process(loObject *lo,QString workdir,QString ticket,QString command) ;

private:
	QString* desc ;
	QString* uniqId ;
	int version ;
	bool status ;
	QList< QStringList* >* fieldList ;

private slots:
	void afterRun(int exitCode, QProcess::ExitStatus exitStatus, eewsProcess* process) ;

signals:
	void ticketResult(QString ticket,verdictObject *verdict) ;

} ;

#endif // CALPLUGIN_H
