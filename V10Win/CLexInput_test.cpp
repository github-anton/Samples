#include "CLexInput.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

CLexInput *pLi ;

void *reader(void*) ;

int main (void) {

	pLi = new CLexInput() ;
	pthread_t th ;
	pthread_create(&th, NULL, reader, NULL) ;

	char msg[] = "Hello, World!\n" ;

	printf("feedStr():\n") ;
	pLi->feedStr(msg) ;

	printf("feedChar():\n") ;
	for (size_t i = 0; i < sizeof(msg); i++) {
		pLi->feedChar(msg[i]) ;
		sleep(1) ;
	}

	sleep(2) ;

	return 0 ;
}

void *reader(void*) {
	FILE *fs = pLi->getRead() ;
	char buff[8] = "" ;
	while(1) {
		fread(buff, 1, 1, fs) ;
		printf(buff) ;
		fflush(stdout) ;
	}
}
