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

/*! \file compileQueue.h
    \brief The compileQueue definition file.

	This file defines the compileQueue object, that inherits from queueObject.*/

/*! \class compileQueue */

#ifndef COMPILEQUEUE_H
#define COMPILEQUEUE_H

#include "eewsProcess.h"
#include "queueObject.h"

class compileQueue : public queueObject {

	Q_OBJECT

public:
	//! The class constructor
	compileQueue(QObject *parent=0) ;

private:
	void proccessSubmission(QString ticket) ;
	int getIdleStatus() ;
	int getProcessingStatus() ;
	int getTopStatus() ;

private slots:
	void afterCompile(int exitCode, QProcess::ExitStatus exitStatus, eewsProcess* process) ;
	void afterLink(int exitCode, QProcess::ExitStatus exitStatus, eewsProcess* process) ;

} ;

#endif // COMPILEQUEUE_H
