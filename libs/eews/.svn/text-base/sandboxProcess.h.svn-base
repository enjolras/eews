
#ifndef SANDBOXPROCESS_H
#define SANDBOXPROCESS_H

#include <QProcess>

class sandboxProcess : public QProcess {

	Q_OBJECT

public:
	enum ProcessModeFlags {
		NotSandboxed = 0x0001,
		Sandboxed = 0x0002
	} ;
	Q_DECLARE_FLAGS(ProcessMode, ProcessModeFlags) ;

	sandboxProcess(ProcessMode modeFlags = sandboxProcess::Sandboxed) ;
	void setTimeLimit(int argTimeLimit) ;

protected:
	void setupChildProcess() ;

private:
	int timeLimit ;
	ProcessMode mode ;

} ;

Q_DECLARE_OPERATORS_FOR_FLAGS(sandboxProcess::ProcessMode) ;

#endif // SANDBOXPROCESS_H

