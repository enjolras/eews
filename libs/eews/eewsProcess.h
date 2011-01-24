#ifndef EEWSPROCESS_H
#define EEWSPROCESS_H

#include "sandboxProcess.h"

class QString ;
class QByteArray ;
class loObject ;
class languageObject ;

class eewsProcess : public QObject {

	Q_OBJECT

public:
	enum ProcessModeFlags {
		NotSandboxed = 0x0001,
		Sandboxed = 0x0002
	} ;
	Q_DECLARE_FLAGS(ProcessMode, ProcessModeFlags) ;

	eewsProcess() ;
	~eewsProcess() ;
	void setTicket(const QString &argTicketId) ;
	QString ticket() const ;
	void setTimeLimit(int argTimeLimit) ;
	void setMemLimit(int argMemLimit) ;
	int timeUsage() ;
	int memUsage() ;
	void setWorkingDirectory(const QString &argDirectory) ;
	void start(QString argCommand, ProcessMode mode = eewsProcess::Sandboxed) ;
	void setStdIn(const QByteArray &argStdIn) ;
	void setMemoryOffset(int argMemOffset) ;
	QByteArray getStdOut() ;
	QByteArray getStdErr() ;
	void setLo(loObject *argLo) ;
	void setLang(languageObject *argLang) ;
	loObject *lo() ;
	languageObject *lang() ;
	int totalCases ;
	int solvedCases ;
	int processedCases ;
	QString command ;

private:
	QString ticketId ;
	QString directory ;
	int memOffset ;
	int timeLimit ;
	int memLimit ;
	sandboxProcess *subProcess ;
	loObject *loData ;
	languageObject *langData ;

private slots:
	void finishedSlot(int exitCode, QProcess::ExitStatus exitStatus) ;

signals:
	void finished(int exitCode, QProcess::ExitStatus exitStatus, eewsProcess* process) ;
} ;

Q_DECLARE_OPERATORS_FOR_FLAGS(eewsProcess::ProcessMode)

#endif // EEWSPROCESS_H

