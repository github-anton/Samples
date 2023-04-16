/*
 * CLexInput.cpp
 *
 *  Created on: 17 марта 2017 г.
 *      Author: anton
 */

#include "CLexInput.h"
#include <stdarg.h>
#include <malloc.h>
#include <string.h>
#include <wchar.h>
#include <unistd.h>
#include "aux.h"
#include <time.h>

cookie_io_functions_t CLexInput::Func = {
		.read = CLexInput::read,
		.write = CLexInput::write,
		.seek = CLexInput::seek,
		.close = CLexInput::close
};

size_t CLexInput::RingBufSize = 1024 ;

ssize_t CLexInput::write(void *li, const char *buf, size_t size) {
	CLexInput *pLi = (CLexInput*)li;

	pthread_mutex_lock(&pLi->share) ;
	pLi->pBuf->put((void*)buf, size) ;

	size_t fill = pLi->pBuf->getFillSize() ;

	// DEBUG
	char *pbuf = (char*)buf ;
	pbuf[size] = '\0' ;
	fprintf (stderr, "li: w %ib d=%s, -> fill=%i\n", (int)size, buf, (int)fill) ;

	pthread_mutex_unlock(&pLi->share) ;
	if(fill)
		pthread_mutex_unlock(&pLi->eof) ;
	return size ;
}

ssize_t	CLexInput::read(void *li, char *buf, size_t size) {
	CLexInput *pLi = (CLexInput*)li;

/*	Strange possible Lex bug
 *
 */
	pthread_mutex_lock(&pLi->share) ;
	int fill = pLi->pBuf->getFillSize() ;
	pthread_mutex_unlock(&pLi->share) ;
	if (!fill) {
		pthread_mutex_lock(&pLi->eof) ;
	}

	pthread_mutex_lock(&pLi->share) ;
	int msize = MIN(size, pLi->pBuf->getFillSize()) ;
	pLi->pBuf->get(buf, msize) ;

	// DEBUG
	char *pbuf = (char*)buf ;
	pbuf[msize] = '\0' ;
	fprintf (stderr, "li: r %ib d=%s, -> fill=%i\n", msize, buf, (int)pLi->pBuf->getFillSize()) ;

	pthread_mutex_unlock(&pLi->share) ;
	return msize ;
}

int	CLexInput::seek(void *c, off64_t *offset, int whence) {
	return 0 ;
}

int	CLexInput::close(void *c) {
	return 0 ;
}

CLexInput::CLexInput() {
	pBuf = new CRingBuf(RingBufSize) ;
	FsRead = fopencookie(this,"r", CLexInput::Func) ;
	FsWrite = fopencookie(this,"w", CLexInput::Func) ;

	pthread_mutex_init(&eof, NULL) ;
	pthread_mutex_lock(&eof) ;

	pthread_mutex_init(&share, NULL) ;

}

CLexInput::~CLexInput() {

}

FILE *CLexInput::getRead() {
	return FsRead ;
}

FILE *CLexInput::getWrite() {
	return FsWrite ;
}

void CLexInput::feedChar(char sym) {
	fprintf(FsWrite, "%c", sym) ;
	fflush(FsWrite) ;
}

void CLexInput::feedStr(const char *format, ...) {
	va_list args ;
	va_start(args, format) ;
	fprintf(FsWrite, format) ;
	fflush(FsWrite) ;
	va_end(args) ;
}

