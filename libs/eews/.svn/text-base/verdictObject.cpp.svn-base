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

#include "verdictObject.h"

verdictObject::verdictObject() {

	verdict = 0 ;
	result = 0 ;
	QString resultStr ;
	testCases = 0 ;
	solvedTestCases = 0 ;
	timeUsage = 0 ;
	memUsage = 0 ;
	QString stdErr ;

}

void	verdictObject::setVerdict(int tmpVerdict)		{ verdict = tmpVerdict ; }
void	verdictObject::setResult(int tmpResult, int tmpBase)	{ result = 100 / tmpBase * tmpResult ; }
void	verdictObject::setResultStr(QString tmpResultStr)	{ resultStr = tmpResultStr ; }
void	verdictObject::setTestCases(int tmpTestCases)		{ testCases = tmpTestCases ; }
void	verdictObject::setSolvedTestCases(int tmpSolvedTestCases) { solvedTestCases = tmpSolvedTestCases ; }
void	verdictObject::setTimeUsage(int tmpTimeUsage)		{ timeUsage = tmpTimeUsage ; }
void	verdictObject::setMemUsage(int tmpMemUsage)		{ memUsage = tmpMemUsage ; }
void	verdictObject::setStdErr(QString tmpStdErr)		{ stdErr = tmpStdErr ; }
int	verdictObject::getVerdict()				{ return verdict ; }
int	verdictObject::getResult()				{ return result ; }
QString	verdictObject::getResultStr()				{ return resultStr ; }
int	verdictObject::getTestCases()				{ return testCases ; }
int	verdictObject::getSolvedTestCases()			{ return solvedTestCases ; }
int	verdictObject::getTimeUsage()				{ return timeUsage ; }
int	verdictObject::getMemUsage()				{ return memUsage ; }
QString	verdictObject::getStdErr()				{ return stdErr ; }
