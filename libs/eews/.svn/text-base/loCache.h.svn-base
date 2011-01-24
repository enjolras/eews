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

/*! \class loCache */

#ifndef LOCACHE_H
#define LOCACHE_H

#include <QObject>
#include <QList>

class QString ;
class loObject ;
class QFile ;
class QHttp ;
class QString ;

typedef struct {
	int transId ;
	QString ticket ;
	QFile *file ;
} fileRef ;

class loCache : public QObject {

	Q_OBJECT

public:
	loCache(int loCacheSize, int loCacheExp, QString loCacheDir) ;
	loObject* getLO(QString url) ;
	void refreshLO(QString url) ;
	void refreshAll() ;
	void cleanUp() ;
	void prepareLO(QString ticket) ;

private:
	int cacheSize ;
	int cacheExp ;
	QString cacheDir ;
	QList<fileRef> *downloadFiles ;
	QFile *tmpFile ;
	QHttp *http ;

private slots:
	void closeFile(int id,bool error) ;

signals:
	void submissionReady(QString ticket) ;

} ;

#endif // LOCACHE_H
