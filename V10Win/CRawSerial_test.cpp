/*
 * CRawSerial_test.cpp
 *
 *  Created on: 1 июня 2016 г.
 *      Author: anton
 */

#include "CRawSerial.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define DEVICE "/dev/ttyS0"

CRawSerial *pSer ;
pthread_t pt ;

void *key_proc(void *) ;

int main ( void ) {

	pSer = new CRawSerial( DEVICE, 1200 ) ;
	if ( !pSer->is_ok() ) {
		perror( DEVICE );
		return -1 ;
	}

	pthread_create(&pt, NULL, &key_proc, NULL) ;

	while (1) {
		char repl ;
		pSer->receive_data ( &repl, 1 ) ;
		printf("%c", repl) ;
	}

	return 0 ;
}

void *key_proc(void *) {
	system ("/bin/stty raw") ;
	while(1) {
		char sym = getchar() ;
		if(sym == '\n') sym = '\r' ;
		pSer->transmit_data(&sym, 1) ;
	}
}
