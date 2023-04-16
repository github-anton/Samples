/*
 * parser_test.cpp
 *
 *  Created on: 28 марта 2017 г.
 *      Author: anton
 */

#include "CLexInput.h"
#include "parser.y.hpp"
#include <stdio.h>
#include <unistd.h>
#include "CTransliter.h"
#include <pthread.h>
#include <locale.h>
#include <QtCore/QString>

extern FILE *yyin ;
int yylex() ;
CLexInput *pLi ;
pthread_t wrt ;
CTransliter *pTl ;

void *writer(void *) ;

int main (void) {
	pLi = new CLexInput() ;
	yyin = pLi->getRead() ;
	pTl = new CTransliter ;

	setlocale( LC_ALL, "ru_RU.UTF-8" ) ;

	pthread_create(&wrt, NULL, writer, NULL) ;

	sleep(2) ;
	while(1) {
		yylex() ;
	}

	return 0 ;
}

void *writer(void *) {
	QString qstr ;

	//pLi->feedChar('\n') ;
	//sleep(3) ;
	qstr += pTl->convert('p') ;
	qstr += pTl->convert('r') ;
	qstr += pTl->convert('i') ;

	pLi->feedStr(qstr.toAscii().data()) ;
	qstr = "" ;

	sleep(3) ;
	qstr += pTl->convert('w') ;
	qstr += pTl->convert('e') ;
	qstr += pTl->convert('t') ;
	qstr += '\n' ;

	pLi->feedStr(qstr.toAscii().data()) ;

	sleep(2) ;

	return NULL ;
}
