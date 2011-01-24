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

/*! \class judgeQueue */

#ifndef JUDGEQUEUE_H
#define JUDGEQUEUE_H

#include "queueObject.h"

class verdictObject ;

class judgeQueue : public queueObject {

	Q_OBJECT

public:
	judgeQueue(QObject *parent=0) ;

private:
	void proccessSubmission(QString ticket) ;
	int getIdleStatus() ;
	int getProcessingStatus() ;
	int getTopStatus() ;

private slots:
	void deleteFromQueue(QString ticket,verdictObject *verdict) ;

} ;

#endif // JUDGEQUEUE_H
