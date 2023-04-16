/*
 * CRingBuf.cpp
 *
 *  Created on: 30 марта 2017 г.
 *      Author: anton
 */

#include "CRingBuf.h"
#include "aux.h"
#include <stdlib.h>

CRingBuf::CRingBuf(size_t size) {
	pChunk = (char*)malloc(size) ;
	BIdx = 0 ;
	Fill = 0 ;
	Size = size ;
}

CRingBuf::~CRingBuf() {
	BIdx = 0 ;
	Fill = 0 ;
	free(pChunk) ;
}

int CRingBuf::put(void *data, size_t len) {
	char *pData = (char*)data ;

	int i ;
	for ( i = 0; i < (int)MIN(len, Size - Fill); i++) {
		pChunk[(BIdx + Fill++) % Size] = pData[i] ;
	}
	return i ;
}

int CRingBuf::get(void *data, size_t len) {
	char *pData = (char*)data ;
	int i ;
	for(i = 0; (i < (int)len) && Fill ; i++) {
		pData[i] = pChunk[(BIdx++) % Size] ;
		Fill -- ;
	}
	return i ;
}

int CRingBuf::read(void *data, size_t len) {
	char *pData = (char*)data ;
	int i ;
	for(i = 0; (i < (int)len) && Fill ; i++) {
		pData[i] = pChunk[(BIdx+i) % Size] ;
	}
	return i ;
}

size_t CRingBuf::getFillSize() {
	return Fill ;
}
