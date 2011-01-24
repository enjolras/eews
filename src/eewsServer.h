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

#ifndef EEWSSERVER_H
#define EEWSSERVER_H

#include <QSettings>
#include "languageContainer.h"
#include "pluginContainer.h"
#include "loCache.h"
#include "qtservice.h"
#include "enums.h"

#define LOG(a)		QtServiceBase::instance()->logMessage(a)

#define SERVER		(eewsServer*)QtServiceBase::instance()

#define SETTINGS	(SERVER)->settings
#define LANGUAGES	(SERVER)->languages
#define PLUGINS		(SERVER)->pluginsCont
#define LOCACHE		(SERVER)->locache

class eewsServer : public QtService<QCoreApplication> {

public:
	eewsServer(int argc, char **argv) ;
	QSettings *settings ;
	languageContainer *languages ;
	pluginContainer *pluginsCont ;
	loCache *locache ;

protected:
	void start() ;
	void pause() ;
	void stop() ;
	void resume() ;

} ;

#endif // EEWSSERVER_H
