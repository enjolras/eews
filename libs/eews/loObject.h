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

/*! \class loObject */

#ifndef LOOBJECT_H
#define LOOBJECT_H

#include <QObject>

class QString ;
class QuaZip ;
class QByteArray ;

class loObject : public QObject {

	Q_OBJECT

public:
	loObject() ;
	~loObject() ;
	int countCases(QString plugin) ;
	QByteArray getInputTest(QString plugin,int testId) ;
	QByteArray getOutputTest(QString plugin,int testId) ;
	int getTestValorization(QString plugin,int testId) ;
	bool setFile(QString fileName) ;

private:
	QuaZip *loFile ;
	QString getQuery(QString fileName,QString xQuery) ;

} ;

#endif // LOOBJECT_H
