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

#include <QtSql>
#include "databaseGod.h"

// Initial creation and population of the database

databaseGod::databaseGod() {

}

bool databaseGod::createTables() {

	QSqlQuery query ;

	// Table creation
	// dbparams - generic table for storing any required configuration parameter
	//	field	- Field name (primary key)
	//	value	- Field value
	query.exec("CREATE TABLE dbparams (field char(64) primary key,value int)") ;

	// languages - information about the languages used in the judge
	//	unidiq	- Unique identifier of the language (primary key)
	//	name	- Short name of the language
	//	description - Description of the language, including the compile options used
	//	version	- Version of the language
	//	compile	- Compile command of the language
	//	link	- Link command
	//	run	- Execution command
	//	srcext	- Source code extension
	//	objext	- Object extension
	//	exeext	- Executable extension
	query.exec("CREATE TABLE languages (uniqid char(64) primary key,name text,description text,version char(64),compile text,link text,run text,srcext text,objext text,exeext text,memoffset int default 0,calcode text,enabled bool default 1)") ;

	// submissions - information about the submissions we are working on
	//	ticket	- Ticket identifier for the submissions (primary key)
	//	language - Unique identifier of language used in the submission
	//	plugin	- Unique identifier of the plugin used
	//	priority - Priority value passed by the client
	//	timeusage - Time used in the execution of the program
	//	memusage - Memory used in the execution of the program
	//	verdict	- Verdict of the submission
	//	result	- Result (grading) in percentage
	//	resultstr - Reserved field for plugin specific feedback
	//	status	- Status of the submission (i.e. which stage we are in)
	//	statusstr - Free text about the status
	//	code	- Source code of the submission
	//	lo	- Learning Object URL we are using
	//	stderr	- Standard Error in case of compilation error
	query.exec("CREATE TABLE submissions (ticket char(32) primary key,language text,plugin text,priority int,timeusage int,memusage int,verdict int,result int,resultstr text,status int,statusstr text,code text,lo text,stderr text)") ;

	// compilequeue - Table holding information about the submission in the compilequeue
	//	ticket	- Identifier of the submission
	//	timestamp - Time the submission entered the queue
	//	priority - Calculated priority of the submission
	query.exec("CREATE TABLE compilequeue (ticket char(32) primary key,timestamp int,priority int)") ;

	// judgequeue - Table holding information about the submission in the judgequeue
	//	ticket	- Identifier of the submission
	//	timestamp - Time the submission entered the queue
	//	priority - Calculated priority of the submission
	query.exec("CREATE TABLE judgequeue (ticket char(32) primary key,timestamp int,priority int)") ;

	// locache - Learning Object cache information
	//	url	- URL of the learning object
	//	filename - File where the Learning Object is cached
	//	expiration - Expiration of the cache entry
	//	status - Status control while the LO is being downloaded, 0 otherwise
	query.exec("CREATE TABLE locache (url text primary key,filename text,expiration int,status int)") ;

	// Table filling
	// dbparams
	query.exec("INSERT INTO dbparams (field,value) VALUES ('dbversion',1)") ;

	return TRUE ;

}
