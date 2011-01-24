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
#include "icpcPlugin.h"
#include "verdictObject.h"
#include "enums.h"

icpcPlugin::icpcPlugin() {

	desc = new QString("ICPC Style Judging Engine") ;
	uniqId = new QString("ICPC") ;
	version = 1 ;
	status = FALSE ;

	fieldList = new QList< QStringList* > ;


}

QString* icpcPlugin::getDesc() {

	return desc ;

}

QString* icpcPlugin::getUniqId() {

	return uniqId ;

}

int icpcPlugin::getVersion() {

	return version ;

}

bool icpcPlugin::startPlugin() {

	status = TRUE ;
	return TRUE ;

}

bool icpcPlugin::stopPlugin() {

	status = FALSE ;
	return TRUE ;

}

bool icpcPlugin::getStatus() {

	return status ;

}

bool icpcPlugin::reloadConfig() {

	return TRUE ;

}

QList< QStringList* >* icpcPlugin::getFieldList() {

	return fieldList ;

}

void icpcPlugin::process(loObject *lo,QString workdir,QString ticket,QString command) {

	if(lo->countCases("ICPC") == 0) {
		verdictObject *verdict = new verdictObject() ;
		verdict->setVerdict(SubmissionVerdict::SubmissionError) ;
		emit(ticketResult(ticket,verdict)) ;
		return ;
	}

	eewsProcess *tmpProcess = new eewsProcess() ;

	tmpProcess->setLo(lo) ;
	tmpProcess->setTicket(ticket) ;

	connect(tmpProcess,SIGNAL(finished(int,QProcess::ExitStatus,eewsProcess*)),this,SLOT(afterRun(int,QProcess::ExitStatus,eewsProcess*))) ;

	tmpProcess->setWorkingDirectory(workdir + "/" + ticket) ;
 	tmpProcess->setStdIn(lo->getInputTest("ICPC",0)) ;
	tmpProcess->setTimeLimit(10000) ;
	tmpProcess->start(command,eewsProcess::Sandboxed) ;

}

void icpcPlugin::afterRun(int exitCode, QProcess::ExitStatus exitStatus, eewsProcess* process) {

	int tmpTimeUsed = 10000 ;
	int tmpMemUsed = 512 * 1024 ;

	process->disconnect(SIGNAL(finished(int,QProcess::ExitStatus,eewsProcess*))) ;

	QString tmpOutput(process->getStdOut()) ;
	QString tmpTestcase(process->lo()->getOutputTest("ICPC",0)) ;

	verdictObject *verdict = new verdictObject() ;

	verdict->setTestCases(0) ;
	verdict->setSolvedTestCases(0) ;
	verdict->setTimeUsage((process->timeUsage() < tmpTimeUsed ? process->timeUsage() : tmpTimeUsed)) ;
	verdict->setMemUsage((process->memUsage() < tmpMemUsed ? process->memUsage() : tmpMemUsed)) ;

	if(process->timeUsage() > tmpTimeUsed) {
		verdict->setVerdict(SubmissionVerdict::TimeLimit) ;
		verdict->setResult(0) ;
	} else if(process->memUsage() > tmpMemUsed ) {
		verdict->setVerdict(SubmissionVerdict::MemoryLimit) ;
		verdict->setResult(0) ;
	} else if(exitCode || exitStatus) {
		verdict->setVerdict(SubmissionVerdict::RuntimeError) ;
		verdict->setResult(0) ;
	} else if(QString::compare(tmpOutput,tmpTestcase)) {
		int tmpWrong = FALSE ;

		for(int i=0;i<tmpOutput.size();i++) {
			if(!tmpOutput.at(i).isSpace() && (tmpOutput.at(i) != tmpTestcase.at(i))) {
				tmpWrong = TRUE ;
				break ;
			}
		}

		verdict->setResult(0) ;

		if(tmpWrong) verdict->setVerdict(SubmissionVerdict::WrongAnswer) ;
		else verdict->setVerdict(SubmissionVerdict::PresentationError) ;
	} else {
		verdict->setVerdict(SubmissionVerdict::Accepted) ;
		verdict->setResult(100) ;
		verdict->setSolvedTestCases(1) ;
	}

	process->deleteLater() ;

	emit(ticketResult(process->ticket(),verdict)) ;

}

bool icpcPlugin::wantsLO() {
	return TRUE ;
}

bool icpcPlugin::isPublic() {
	return TRUE ;
}

Q_EXPORT_PLUGIN2(icpcPlugin,icpcPlugin)
