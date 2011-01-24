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

#ifndef VERDICTOBJECT_H
#define VERDICTOBJECT_H

#include <QObject>

class verdictObject : public QObject {

	Q_OBJECT

public:
	verdictObject() ;
	void setVerdict(int tmpVerdict) ;
	void setResult(int tmpResult, int tmpBase = 100) ;
	void setResultStr(QString tmpResultStr) ;
	void setTestCases(int tmpTestCases) ;
	void setSolvedTestCases(int tmpSolvedTestCases) ;
	void setTimeUsage(int tmpTimeUsage) ;
	void setMemUsage(int tmpMemUsage) ;
	void setStdErr(QString tmpStdErr) ;
	int getVerdict() ;
	int getResult() ;
	QString getResultStr() ;
	int getTestCases() ;
	int getSolvedTestCases() ;
	int getTimeUsage() ;
	int getMemUsage() ;
	QString getStdErr() ;

private:
	int verdict ;
	int result ;
	QString resultStr ;
	int testCases ;
	int solvedTestCases ;
	int timeUsage ;
	int memUsage ;
	QString stdErr ;

} ;

#endif // VERDICTOBJECT_H
