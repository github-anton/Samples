/*
 * CTransliter.h
 *
 *  Created on: 17 марта 2017 г.
 *      Author: anton
 */

#ifndef CTRANSLITER_H_
#define CTRANSLITER_H_

#include <iconv.h>

class CTransliter {
private:
	char usec[16] ;
	iconv_t cd;
public:
	CTransliter() ;
	virtual ~CTransliter() ;
	char *convert(char sym) ;
} ;

#endif /* CTRANSLITER_H_ */
