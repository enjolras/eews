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

#ifndef ENUMS_H
#define ENUMS_H

namespace SubmissionStatus {
	enum SubmissionStatus {
		CompileIdle		=	0,
		CompileProcessing	=	1,
		CompileCompiling	=	2,
		CompileLinking		=	3,
		CompileCompileError	=	4,
		CompileLinkError	=	5,
		CompileDone		=	8,
		CompileTop		=	9,
		JudgeIdle		=	10,
		JudgeProcessing		=	11,
		JudgeRunning		=	12,
		JudgeJudging		=	13,
		JudgeDone		=	18,
		JudgeTop		=	19,
		WaitingForLO		=	70,
		LONotAvailable		=	80,
		PluginNotAvailable	=	90,
		Finished		=	100
	} ;
}

namespace SubmissionVerdict {
	enum SubmissionVerdict {
		SubmissionError		=	10,
		InQueue			=	20,
		CompilationError	=	30,
		RuntimeError		=	40,
		TimeLimit		=	50,
		MemoryLimit		=	60,
		WrongAnswer		=	70,
		PresentationError	=	80,
		Accepted		=	90
	} ;
}

#endif // ENUMS_H
