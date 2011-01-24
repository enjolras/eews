#include <QString>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include <QFlags>
#include "eewsProcess.h"
#include "sandboxProcess.h"
#include "loObject.h"
#include "languageObject.h"

#define PAGESIZE sysconf(_SC_PAGESIZE)

eewsProcess::eewsProcess() {

	timeLimit = memLimit = memOffset = 0 ;
	totalCases = solvedCases = processedCases = 0 ;

}

eewsProcess::~eewsProcess() {

}

void eewsProcess::setTicket(const QString &argTicketId) {

	ticketId = argTicketId ;

}

QString eewsProcess::ticket() const {

	return ticketId ;

}

void eewsProcess::setTimeLimit(int argTimeLimit) {

	timeLimit = argTimeLimit ;

}

void eewsProcess::setMemLimit(int argMemLimit) {

	memLimit = argMemLimit ;

}

int eewsProcess::timeUsage() {

	int timeUsed ;

	QFile file(this) ;
	file.setFileName(directory + "/cpuUsage") ;
	file.open(QIODevice::ReadOnly | QIODevice::Text) ;
	QTextStream timeUsageData(&file) ;
	timeUsageData >> timeUsed ;
	file.close() ;

	return timeUsed ;

}

int eewsProcess::memUsage() {

	int memUsed ;

	QFile file(this) ;
	file.setFileName(directory + "/memUsage") ;
	file.open(QIODevice::ReadOnly | QIODevice::Text) ;
	QTextStream memUsageData(&file) ;
	memUsageData >> memUsed ;
	file.close() ;

	return memUsed ;

}

void eewsProcess::finishedSlot(int exitCode, QProcess::ExitStatus exitStatus) {

	QFile file(this) ;

	file.setFileName(directory + "/exitCode") ;
	file.open(QIODevice::WriteOnly | QIODevice::Text) ;
	file.write(QString::number(exitCode).toAscii()) ;
	file.close() ;

	file.setFileName(directory + "/exitStatus") ;
	file.open(QIODevice::WriteOnly | QIODevice::Text) ;
        file.write(QString::number(exitStatus).toAscii()) ;
	file.close() ;

}

void eewsProcess::start(QString argCommand, ProcessMode mode) {

	int pid = fork() ;

	if(!pid) {
		
		struct rusage execusage ;
		int timeUsed, memUsed ;
		timeUsed = memUsed = 0 ;

		QFlags<eewsProcess::ProcessMode> flags(mode) ;

		if(flags.testFlag(eewsProcess::Sandboxed)) {
			subProcess = new sandboxProcess(sandboxProcess::Sandboxed) ;
			subProcess->setTimeLimit((timeLimit/1000)+1) ;
		} else {
			subProcess = new sandboxProcess(sandboxProcess::NotSandboxed) ;
		}

		connect(subProcess,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(finishedSlot(int,QProcess::ExitStatus))) ;

		subProcess->setWorkingDirectory(directory) ;
		subProcess->start(argCommand) ;

		subProcess->waitForStarted() ;

		if(QFile::exists(directory + "/stdin")) {
			QFile file(this) ;
			file.setFileName(directory + "/stdin") ;
			file.open(QIODevice::ReadOnly) ;
			subProcess->write(file.readAll()) ;
			file.close() ;
			subProcess->closeWriteChannel() ;
		}

		while(!subProcess->waitForFinished(100)) {

			QFile file(this) ;
			file.setFileName(QString("/proc/%1/statm").arg(subProcess->pid())) ;
			file.open(QIODevice::ReadOnly | QIODevice::Text) ;
			QTextStream salida(&file) ;

			int shit ;
			int tmpMemUsed ;

			salida >> shit >> shit >> shit >> shit >> shit >> tmpMemUsed ;

			file.close() ;

			tmpMemUsed = (tmpMemUsed * PAGESIZE) - memOffset ;

			if(tmpMemUsed > memUsed) memUsed = tmpMemUsed ;

			if(memLimit && memLimit < memUsed) subProcess->kill() ;

		}

		getrusage(RUSAGE_CHILDREN,&execusage) ;

		QFile file(this) ;

		file.setFileName(directory + "/cpuUsage") ;
		file.open(QIODevice::WriteOnly | QIODevice::Text) ;
		file.write(QString::number((execusage.ru_utime.tv_usec / 1000) + (execusage.ru_utime.tv_sec * 1000)).toAscii()) ;
		file.close() ;

		file.setFileName(directory + "/memUsage") ;
		file.open(QIODevice::WriteOnly | QIODevice::Text) ;
		file.write(QString::number(memUsed).toAscii()) ;
		file.close() ;

		file.setFileName(directory + "/stdout") ;
		file.open(QIODevice::WriteOnly) ;
		file.write(subProcess->readAllStandardOutput()) ;
		file.close() ;

		file.setFileName(directory + "/stderr") ;
		file.open(QIODevice::WriteOnly) ;
		file.write(subProcess->readAllStandardError()) ;
		file.close() ;

		_exit(0) ;
	}

	int pid_status ;

	waitpid(pid,&pid_status,0) ;

	int exitCode, exitStatus ;

	QFile file(this) ;
	file.setFileName(directory + "/exitCode") ;
	file.open(QIODevice::ReadOnly | QIODevice::Text) ;
	QTextStream exitCodeData(&file) ;
	exitCodeData >> exitCode ;
	file.close() ;

	file.setFileName(directory + "/exitStatus") ;
	file.open(QIODevice::ReadOnly | QIODevice::Text) ;
	QTextStream exitStatusData(&file) ;
	exitStatusData >> exitStatus ;
	file.close() ;

	emit finished(exitCode,(QProcess::ExitStatus)exitStatus,this) ;

}

void eewsProcess::setWorkingDirectory(const QString &argDirectory) {

	directory = argDirectory ;

}

void eewsProcess::setStdIn(const QByteArray &argStdIn) {

	QFile file(this) ;
	file.setFileName(directory + "/stdin") ;
	file.open(QIODevice::WriteOnly) ;
	file.write(argStdIn) ;
	file.close() ;

}

QByteArray eewsProcess::getStdOut() {

	QByteArray tmpByteArray ;

	QFile file(this) ;
	file.setFileName(directory + "/stdout") ;
	file.open(QIODevice::ReadOnly) ;
	tmpByteArray = file.readAll() ;
	file.close() ;

	return tmpByteArray ;

}

QByteArray eewsProcess::getStdErr() {

	QByteArray tmpByteArray ;

	QFile file(this) ;
	file.setFileName(directory + "/stderr") ;
	file.open(QIODevice::ReadOnly) ;
	tmpByteArray = file.readAll() ;
	file.close() ;

	return tmpByteArray ;

}

void eewsProcess::setMemoryOffset(int argMemOffset) {

	memOffset = argMemOffset ;

}

void eewsProcess::setLo(loObject *argLo) {

	loData = argLo ;

}

loObject *eewsProcess::lo() {

	return loData ;

}

void eewsProcess::setLang(languageObject *argLang) {

	langData = argLang ;

}

languageObject *eewsProcess::lang() {

	return langData ;

}
