#include <sys/time.h>
#include <sys/resource.h>
#include <QFlags>
#include "sandboxProcess.h"

sandboxProcess::sandboxProcess(ProcessMode argMode) : mode(argMode) {

	timeLimit = 0 ;

}

void sandboxProcess::setupChildProcess() {

	QFlags<sandboxProcess::ProcessMode> flags(mode) ;

	if(flags.testFlag(sandboxProcess::Sandboxed)) {

		struct rlimit cpuTimeLimit ;

		cpuTimeLimit.rlim_cur = (timeLimit ? timeLimit : RLIM_INFINITY) ;
		cpuTimeLimit.rlim_max = (timeLimit ? timeLimit : RLIM_INFINITY) ;

		setrlimit(RLIMIT_CPU, &cpuTimeLimit) ;
	}

}

void sandboxProcess::setTimeLimit(int argTimeLimit) {

	timeLimit = argTimeLimit ;

}

