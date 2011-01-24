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

#include <QDir>
#include <QSqlQuery>
#include <QFile>
#include "languageObject.h"
#include "verdictObject.h"
#include "compileQueue.h"
#include "eewsServer.h"

compileQueue::compileQueue(QObject *parent) : queueObject(parent) {

	activeSlots = SETTINGS->value("General/CQSlots").toInt() ;

}

void compileQueue::proccessSubmission(QString ticket) {

	LOG(QString("Processing in Compile Queue: "+ticket).toAscii()) ;

	QSqlQuery query("SELECT language,code FROM submissions WHERE ticket = '"+ticket+"'") ;
	query.next() ;

	languageObject *lang = qobject_cast<languageObject *>(LANGUAGES->getLanguageByUniqId(query.value(0).toString())) ;

	QDir workDir(SETTINGS->value("General/WorkDir").toString() + "/" + ticket) ;
	if(workDir.exists()) {
		LOG(QString("Working dir %1 exists. Removing.").arg(ticket)) ;
		foreach(QFileInfo tmpFileInfo,workDir.entryInfoList()) {
			QFile tmpFile(tmpFileInfo.absoluteFilePath()) ;
			tmpFile.remove() ;
		}
		workDir.rmdir(workDir.absolutePath()) ;
	}
	LOG(QString("Creating workdir for %1.").arg(ticket)) ;

	if(!workDir.mkdir(workDir.absolutePath())) {
		LOG(QString("Fatal Error. Can't create working dir for.").arg(ticket)) ;
		verdictObject *verdict = new verdictObject() ;
		verdict->setVerdict(SubmissionVerdict::SubmissionError) ;
		setVerdict(ticket,verdict) ;
		return ;
	}

	QFile file(workDir.absolutePath() + "/code." + lang->getSrcExt()) ;

	if(!file.open(QIODevice::WriteOnly)) {
		LOG(QString("Can't open file for write in %1.").arg(ticket)) ;
		verdictObject *verdict = new verdictObject() ;
		verdict->setVerdict(SubmissionVerdict::SubmissionError) ;
		setVerdict(ticket,verdict) ;
		return ;
	}
	file.write(query.value(1).toString().toAscii()) ;
	file.close() ;

	QString command = lang->getCompile() ;
	command.replace("$source","code." + lang->getSrcExt()) ;
	command.replace("$target","code." + lang->getObjExt()) ;

	eewsProcess *compileProcess = new eewsProcess() ;
	compileProcess->setWorkingDirectory(workDir.absolutePath()) ;
	compileProcess->setTicket(ticket) ;
	compileProcess->setLang(lang) ;

	connect(compileProcess,SIGNAL(finished(int,QProcess::ExitStatus,eewsProcess*)),this,SLOT(afterCompile(int,QProcess::ExitStatus,eewsProcess*))) ;

	setStatus(compileProcess->ticket(),SubmissionStatus::CompileCompiling) ;
	compileProcess->start(command, eewsProcess::NotSandboxed) ;

}

void compileQueue::afterCompile(int exitCode, QProcess::ExitStatus exitStatus, eewsProcess* process) {

	process->disconnect(SIGNAL(finished(int,QProcess::ExitStatus,eewsProcess*))) ;

	if(exitCode || exitStatus) {

		QSqlQuery query_queue ;
		query_queue.prepare("DELETE FROM "+sqlTable+" WHERE ticket = :ticket") ;
		query_queue.bindValue(":ticket",process->ticket()) ;
		query_queue.exec() ;

		verdictObject *verdict = new verdictObject() ;
		verdict->setStdErr(process->getStdErr()) ;
		verdict->setVerdict(SubmissionVerdict::CompilationError) ;

		setStatus(process->ticket(),SubmissionStatus::CompileCompileError) ;

		process->deleteLater() ;

		setVerdict(process->ticket(),verdict) ;

	} else {

		QString command = process->lang()->getLink() ;
		command.replace("$source","code." + process->lang()->getObjExt()) ;
		command.replace("$target","code." + process->lang()->getExeExt()) ;

		connect(process,SIGNAL(finished(int,QProcess::ExitStatus,eewsProcess*)),this,SLOT(afterLink(int,QProcess::ExitStatus,eewsProcess*))) ;

		setStatus(process->ticket(),SubmissionStatus::CompileLinking) ;
		process->start(command,eewsProcess::NotSandboxed) ;
	}

	return ;
}

void compileQueue::afterLink(int exitCode, QProcess::ExitStatus exitStatus, eewsProcess* process) {

	process->disconnect(SIGNAL(finished(int,QProcess::ExitStatus,eewsProcess*))) ;

	if(exitCode || exitStatus) {

		QSqlQuery query_queue ;
		query_queue.prepare("DELETE FROM "+sqlTable+" WHERE ticket = :ticket") ;
		query_queue.bindValue(":ticket",process->ticket()) ;
		query_queue.exec() ;

		verdictObject *verdict = new verdictObject() ;
		verdict->setStdErr(process->getStdErr()) ;
		verdict->setVerdict(SubmissionVerdict::CompilationError) ;

		setStatus(process->ticket(),SubmissionStatus::CompileLinkError) ;
		setVerdict(process->ticket(),verdict) ;

	} else {

		QSqlQuery query_delete ;
		query_delete.prepare("DELETE FROM "+sqlTable+" WHERE ticket = :ticket") ;
		query_delete.bindValue(":ticket",process->ticket()) ;
		query_delete.exec() ;

		setStatus(process->ticket(),SubmissionStatus::CompileDone) ;
		emit finishedSubmission(process->ticket()) ;
	}

	process->deleteLater() ;
	return ;

}

int compileQueue::getIdleStatus() { return SubmissionStatus::CompileIdle ; }
int compileQueue::getProcessingStatus() { return SubmissionStatus::CompileProcessing ; }
int compileQueue::getTopStatus() { return SubmissionStatus::CompileTop ; }
