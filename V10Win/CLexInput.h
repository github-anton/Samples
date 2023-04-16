/*
 * CLexInput.h
 *
 *  Created on: 17 марта 2017 г.
 *      Author: anton
 */

#ifndef CLEXINPUT_H_
#define CLEXINPUT_H_

#include <stdio.h>
#include <pthread.h>
#include "CRingBuf.h"

class CLexInput {

private:
	static cookie_io_functions_t Func ;
	CRingBuf *pBuf ;
	static size_t RingBufSize ;
	FILE *FsRead, *FsWrite ;
	pthread_mutex_t eof ;
	pthread_mutex_t share ;

	static ssize_t	write(void *c, const char *buf, size_t size) ;
	static ssize_t	read(void *c, char *buf, size_t size) ;
	static int	seek(void *c, off64_t *offset, int whence) ;
	static int	close(void *c) ;

public:

	CLexInput();
	virtual ~CLexInput();
	FILE *getRead() ;
	FILE *getWrite() ;
	void feedChar(char sym) ;
	void feedStr(const char *format, ...) ;
};

#endif /* CLEXINPUT_H_ */
