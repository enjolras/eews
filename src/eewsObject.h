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

/*! \file eewsObject.h
    \brief The eewsObject definition file.

	This file defines the eewsObject object, that inherits its classes from QThread, for threading support, and eewsService,
	which holds the void classes that must be reimplemented here.*/

/*! \class eewsObject */

#ifndef EEWSOBJECT_H
#define EEWSOBJECT_H

#include <QThread>
#include <QList>
#include "eewsService.h"

class pluginContainer ;
class QSqlTableModel ;
class compileQueue ;
class languageObject ;
class verdictObject ;

class eewsObject : public QThread, public eewsService {

	Q_OBJECT

public:
	//! The class constructor.
	eewsObject() ;

	//! Reimplementation of QThread's run method to start the thread.
	void run() ;

private:
	int getCapabilities(struct ns1__getCapabilitiesResponse &response) ;
	int submitCode(ns1__submissionData *data, std::string &ticket) ;
	int getTicketResult(std::string ticket, struct ns1__getTicketResultResponse &response) ;
	int getTicketDump(struct ns1__getTicketDumpResponse &response) ;
	QSqlTableModel *submissionData ;
	compileQueue *cQueue ;

public slots:
	void calibrateLanguage(QString argLang) ;

private slots:
	void getCalibrationData(QString ticket,verdictObject *verdict) ;

} ;


#endif // EEWSOBJECT_H
