/*
 * CRingBuf_test.cpp
 *
 *  Created on: 30 марта 2017 г.
 *      Author: anton
 */

#include "CRingBuf.h"
#include <stdio.h>

void print_data(char *data, size_t len) ;

int main (void) {
	CRingBuf *pRb = new CRingBuf(8) ;
	char idata[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	char odata[12] = { 0 } ;

	printf("Write(%i): ", pRb->write(idata, 5)) ;
	print_data(idata, 5) ;

	printf("Read(%i): ", pRb->read(odata, 5)) ;
	print_data(odata, 5) ;

	printf("Write(%i): ", pRb->write(&idata[5], 5)) ;
	print_data(&idata[5], 5) ;

	printf("Read(%i): ", pRb->read(odata, 1)) ;
	print_data(odata, 1) ;

	printf("Read(%i): ", pRb->read(odata, 4)) ;
	print_data(odata, 4) ;

	return 0 ;
}

void print_data(char *data, size_t len) {
	for(int i = 0; i < (int)len; i++) {
		printf("%i ", data[i]) ;
	}
	printf("\n") ;
}
