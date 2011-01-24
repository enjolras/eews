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

/*! \file eewsService.cpp
    \brief This file reimplements the virtual methods of the gSOAP generated classes.

	The classes are reimplemented as void classes as the actual coding will be done in eewsObject.

*/

#include "eewsService.h"

// Void implementation of the soap methods, to be reimplemented in an object that inherits both gSoap and QObject

int eewsService::getCapabilities(struct ns1__getCapabilitiesResponse &response) { return SOAP_OK; }
int eewsService::submitCode(ns1__submissionData *data, std::string &ticket) { return SOAP_OK; }
int eewsService::getTicketResult(std::string ticket, struct ns1__getTicketResultResponse &response) { return SOAP_OK; }
int eewsService::getTicketDump(struct ns1__getTicketDumpResponse &response) { return SOAP_OK; }

