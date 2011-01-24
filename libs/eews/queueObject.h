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

/*! \class queueObject */

#ifndef QUEUEOBJECT_H
#define QUEUEOBJECT_H

#include <QObject>
#include <QSqlRecord>
#include <QString>

// #include "eewsObject.h"

class verdictObject ;

class queueObject : public QObject {

	Q_OBJECT

public:
	queueObject(QObject *parent=0) ;
	void setSlots(int tmpSlots) ;
	int getSlots() ;
	void setTable(QString table) ;

protected:
	virtual void proccessSubmission(QString ticket) = 0 ;
	virtual int getIdleStatus() = 0 ;
	virtual int getProcessingStatus() = 0 ;
	virtual int getTopStatus() = 0 ;
	int activeSlots ;
	int usedSlots() ;
	QString sqlTable ;
	void setStatus(QString ticket, int status) ;

public slots:
	void addSubmission(QString ticket) ;
	void setVerdict(QString ticket,verdictObject *verdict) ;

private slots:
	void calculatePriority() ;

signals:
	void finishedSubmission(QString ticket) ;

} ;

#endif // QUEUEOBJECT_H
