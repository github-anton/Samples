/*
 * CRingBuf.h
 *
 *  Created on: 30 марта 2017 г.
 *      Author: anton
 */

#ifndef CRINGBUF_H_
#define CRINGBUF_H_

#include <sys/types.h>

class CRingBuf {

private:
	char *pChunk ;
	int BIdx ;
	size_t Fill ;
	size_t Size ;

public:
	CRingBuf(size_t size);
	virtual ~CRingBuf();
	int put(void *data, size_t len) ;
	int get(void *data, size_t len) ;
	int read(void *data, size_t len) ;
	size_t getFillSize() ;
};

#endif /* CRINGBUF_H_ */
