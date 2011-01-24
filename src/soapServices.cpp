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

#include "soapServices.h"
#include "eewsObject.h"
#include "eewsadmObject.h"

soapServices::soapServices(QObject *parent) : QObject(parent) {

	eewsObject *eews = new eewsObject() ;
	eewsadmObject *eewsadm = new eewsadmObject() ;

	connect(eewsadm,SIGNAL(startLanguageCalibration(QString)),eews,SLOT(calibrateLanguage(QString))) ;

	eews->start() ;
	eewsadm->start() ;

}
