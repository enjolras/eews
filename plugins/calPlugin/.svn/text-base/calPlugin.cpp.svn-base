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

#include <QtPlugin>
#include <QString>
#include "calPlugin.h"
#include "verdictObject.h"
#include "enums.h"

calPlugin::calPlugin() {

	desc = new QString("Plugin for memory calibration") ;
	uniqId = new QString("CAL") ;
	version = 1 ;
	status = TRUE ;

	fieldList = new QList< QStringList* > ;


}

QString* calPlugin::getDesc() {

	return desc ;

}

QString* calPlugin::getUniqId() {

	return uniqId ;

}

int calPlugin::getVersion() {

	return version ;

}

bool calPlugin::startPlugin() {

	status = TRUE ;
	return TRUE ;

}

bool calPlugin::stopPlugin() {

	status = FALSE ;
	return TRUE ;

}

bool calPlugin::getStatus() {

	return status ;

}

bool calPlugin::reloadConfig() {

	return TRUE ;

}

QList< QStringList* >* calPlugin::getFieldList() {

	return fieldList ;

}

void calPlugin::process(loObject *lo,QString workdir,QString ticket,QString command) {

	eewsProcess *tmpProcess = new eewsProcess() ;

	tmpProcess->setTicket(ticket) ;

	connect(tmpProcess,SIGNAL(finished(int,QProcess::ExitStatus,eewsProcess*)),this,SLOT(afterRun(int,QProcess::ExitStatus,eewsProcess*))) ;

	tmpProcess->setWorkingDirectory(workdir + "/" + ticket) ;
	tmpProcess->setTimeLimit(15000) ;
	tmpProcess->start(command,eewsProcess::Sandboxed) ;

}

void calPlugin::afterRun(int exitCode, QProcess::ExitStatus exitStatus, eewsProcess* process) {

	process->disconnect(SIGNAL(finished(int,QProcess::ExitStatus,eewsProcess*))) ;

	verdictObject *verdict = new verdictObject() ;

	verdict->setTestCases(0) ;
	verdict->setSolvedTestCases(0) ;
	verdict->setTimeUsage(process->timeUsage()) ;
	verdict->setMemUsage(process->memUsage()) ;

	verdict->setVerdict(SubmissionVerdict::Accepted) ;
	verdict->setResult(100) ;
	verdict->setSolvedTestCases(1) ;

	process->deleteLater() ;

	emit(ticketResult(process->ticket(),verdict)) ;

}

bool calPlugin::wantsLO() {
	return FALSE ;
}

bool calPlugin::isPublic() {
	return FALSE ;
}

Q_EXPORT_PLUGIN2(calPlugin,calPlugin)
