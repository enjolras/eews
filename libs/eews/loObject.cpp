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

#include <quazip.h>
#include <quazipfile.h>
#include <QXmlQuery>
#include <QXmlFormatter>
#include <QBuffer>
#include <QByteArray>
#include <QtSql>
#include <QString>
#include "loObject.h"
#include "eewsServer.h"

loObject::loObject() {

}

loObject::~loObject() {

	delete loFile ;

}

bool loObject::setFile(QString fileName) {

	loFile = new QuaZip(fileName) ;

	if(!loFile->open(QuaZip::mdUnzip)) {
		LOG(QString("QuaZip: Error opening ZIP file. Error code: %1").arg(loFile->getZipError())) ;
		delete loFile ;
		this->deleteLater() ;
		return FALSE ;
	}

	return TRUE ;

}

int loObject::countCases(QString plugin) {

	return getQuery(QString("imsmanifest.xml"),
			QString("declare namespace ejmd = \"http://www.edujudge.eu/ejmd_v2\";") +
			QString("count(doc($document)//ejmd:evaluation[@ejmd:evaluationModel='%1']/ejmd:tests/ejmd:testFiles)" ).arg(plugin) ).toInt() ;

}

QByteArray loObject::getInputTest(QString plugin,int testId) {

	QString tmpResource(getQuery(QString("imsmanifest.xml"),
			QString("declare namespace ejmd = \"http://www.edujudge.eu/ejmd_v2\";") +
			QString("data(doc($document)//ejmd:evaluation[@ejmd:evaluationModel='%1']/ejmd:tests/ejmd:testFiles[fn:position() = (").arg(plugin) +
			QString::number(testId+1) + QString(")]/ejmd:input/@ejmd:resource)"))) ;

	QString tmpFileName(getQuery(QString("imsmanifest.xml"),
			QString("declare namespace ims = \"http://www.imsglobal.org/xsd/imscp_v1p1\";") +
			QString("data(doc($document)//ims:resource[@identifier='") +
			tmpResource.trimmed() + QString("']/ims:file/@href)"))) ;

	loFile->setCurrentFile(tmpFileName.trimmed()) ;
	QuaZipFile tmpFile(loFile) ;
	tmpFile.open(QIODevice::ReadOnly) ;

	QByteArray tmpReturnValue(tmpFile.readAll()) ;

	tmpFile.close() ;

	return tmpReturnValue ;

}

QByteArray loObject::getOutputTest(QString plugin,int testId) {

	QString tmpResource(getQuery(QString("imsmanifest.xml"),
			QString("declare namespace ejmd = \"http://www.edujudge.eu/ejmd_v2\";") +
			QString("data(doc($document)//ejmd:evaluation[@ejmd:evaluationModel='%1']/ejmd:tests/ejmd:testFiles[fn:position() = (").arg(plugin) +
			QString::number(testId+1) + QString(")]/ejmd:output/@ejmd:resource)"))) ;

	QString tmpFileName(getQuery(QString("imsmanifest.xml"),
			QString("declare namespace ims = \"http://www.imsglobal.org/xsd/imscp_v1p1\";") +
			QString("data(doc($document)//ims:resource[@identifier='") +
			tmpResource.trimmed() + QString("']/ims:file/@href)"))) ;

	loFile->setCurrentFile(tmpFileName.trimmed()) ;
	QuaZipFile tmpFile(loFile) ;
	tmpFile.open(QIODevice::ReadOnly) ;

	QByteArray tmpReturnValue(tmpFile.readAll()) ;

	tmpFile.close() ;

	return tmpReturnValue ;

}

int loObject::getTestValorization(QString plugin,int testId) {

	return getQuery(QString("imsmanifest.xml"),
			QString("declare namespace ejmd = \"http://www.edujudge.eu/ejmd_v2\";") +
			QString("data(doc($document)//ejmd:evaluation[@ejmd:evaluationModel='%1']/ejmd:tests/ejmd:testFiles[fn:position() = (").arg(plugin) +
			QString::number(testId) + QString(")]/@ejmd:valorization)")).toInt() ;

}

QString loObject::getQuery(QString fileName,QString xQuery) {

	loFile->setCurrentFile(fileName) ;
	QuaZipFile tmpFile(loFile) ;
        if(!tmpFile.open(QIODevice::ReadOnly)) return QString("") ;

	QString tmpString(tmpFile.readAll()) ;

	tmpFile.close() ;

	QBuffer buffer ;
	buffer.setData(tmpString.toAscii()) ;
	buffer.open(QIODevice::ReadOnly) ;

	QXmlQuery query ;
	query.bindVariable("document",&buffer) ;
	query.setQuery(xQuery) ;

	QString queryOutput ;
	query.evaluateTo(&queryOutput) ;

	return queryOutput ;

}
