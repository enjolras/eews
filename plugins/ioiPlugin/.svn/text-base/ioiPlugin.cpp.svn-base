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
#include "ioiPlugin.h"
#include "verdictObject.h"
#include "enums.h"

ioiPlugin::ioiPlugin() {

	desc = new QString("IOI Style Judging Engine") ;
	uniqId = new QString("IOI") ;
	version = 1 ;
	status = FALSE ;

	fieldList = new QList< QStringList* > ;


}

QString* ioiPlugin::getDesc() {

	return desc ;

}

QString* ioiPlugin::getUniqId() {

	return uniqId ;

}

int ioiPlugin::getVersion() {

	return version ;

}

bool ioiPlugin::startPlugin() {

	status = TRUE ;
	return TRUE ;

}

bool ioiPlugin::stopPlugin() {

	status = FALSE ;
	return TRUE ;

}

bool ioiPlugin::getStatus() {

	return status ;

}

bool ioiPlugin::reloadConfig() {

	return TRUE ;

}

QList< QStringList* >* ioiPlugin::getFieldList() {

	return fieldList ;

}

void ioiPlugin::process(loObject *lo,QString workdir,QString ticket,QString command) {

	if(lo->countCases("IOI") == 0) {
		verdictObject *verdict = new verdictObject() ;
		verdict->setVerdict(SubmissionVerdict::SubmissionError) ;
		emit(ticketResult(ticket,verdict)) ;
		return ;
	}

	eewsProcess *tmpProcess = new eewsProcess() ;

	tmpProcess->setLo(lo) ;
	tmpProcess->setTicket(ticket) ;
	tmpProcess->solvedCases = 0 ;
	tmpProcess->processedCases = 0 ;
	tmpProcess->totalCases = lo->countCases("IOI") ;

	connect(tmpProcess,SIGNAL(finished(int,QProcess::ExitStatus,eewsProcess*)),this,SLOT(afterRun(int,QProcess::ExitStatus,eewsProcess*))) ;

	tmpProcess->setWorkingDirectory(workdir + "/" + ticket) ;
 	tmpProcess->setStdIn(lo->getInputTest("IOI",tmpProcess->processedCases)) ;
	tmpProcess->setTimeLimit(10000) ;
	tmpProcess->command = command ;
	tmpProcess->start(command,eewsProcess::Sandboxed) ;

}

void ioiPlugin::afterRun(int exitCode, QProcess::ExitStatus exitStatus, eewsProcess* process) {

	int tmpTimeUsed = 10000 ;
	int tmpMemUsed = 512 * 1024 ;

	QString tmpOutput(process->getStdOut()) ;
	QString tmpTestcase(process->lo()->getOutputTest("IOI",process->processedCases)) ;

	if(!QString::compare(tmpOutput,tmpTestcase)) {
		process->solvedCases++ ;
	}

	process->processedCases++ ;

	if(process->processedCases < process->totalCases) {
		process->setStdIn(process->lo()->getInputTest("IOI",process->processedCases)) ;
		process->start(process->command,eewsProcess::Sandboxed) ;
	} else {
		process->disconnect(SIGNAL(finished(int,QProcess::ExitStatus,eewsProcess*))) ;

		verdictObject *verdict = new verdictObject() ;

		verdict->setTestCases(process->totalCases) ;
		verdict->setSolvedTestCases(process->solvedCases) ;
		verdict->setTimeUsage(0) ;
		verdict->setMemUsage(0) ;

		if(process->totalCases == process->solvedCases) {
			verdict->setVerdict(SubmissionVerdict::Accepted) ;
		}
		else {
			verdict->setVerdict(SubmissionVerdict::WrongAnswer) ;
		}

		verdict->setResult(process->solvedCases * 100 / process->totalCases) ;

		process->deleteLater() ;

		emit(ticketResult(process->ticket(),verdict)) ;
	}
}

bool ioiPlugin::wantsLO() {
	return TRUE ;
}

bool ioiPlugin::isPublic() {
	return TRUE ;
}

Q_EXPORT_PLUGIN2(ioiPlugin,ioiPlugin)
