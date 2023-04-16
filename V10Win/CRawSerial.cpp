/*
 * CRawSerial.cpp
 *
 *  Created on: 1 июня 2016 г.
 *      Author: anton
 */

#include "CRawSerial.h"
#include <strings.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

const RawSerialSpeedCross_t CRawSerial::Cross[] = {
						{ 50, B50 },
						{ 75, B75 },
						{ 110, B110 },
						{ 134, B134 },
						{ 150, B150 },
						{ 200, B200 },
						{ 300, B300 },
						{ 600, B600 },
						{ 1200, B1200 },
						{ 1800, B1800 },
						{ 2400, B2400 },
						{ 4800, B4800 },
						{ 9600, B9600 },
						{ 19200, B19200 },
						{ 38400, B38400 }
					};

const size_t CRawSerial::CrossSize = sizeof(CRawSerial::Cross)/sizeof(CRawSerial::Cross[0]) ;

speed_t CRawSerial::calc_bspeed ( unsigned int speed ) {

	for ( int i = 0; i < (int)CrossSize; i++ ) {
		if ( Cross[i].speed == speed ) return Cross[i].bspeed ;
	}
	return B0 ;
}

CRawSerial::CRawSerial(const char *device, unsigned int baudrate) {

	strDevice = device ;
	BaudRate = baudrate ;

	fail = false ;
	speed_t speed = calc_bspeed( baudrate ) ;

	fd = open(device, O_RDWR | O_NOCTTY );
	if (fd <0) {
		fail = true ;
		opened = false ;
		return ;
	}

	opened = true ;

	tcgetattr(fd,&oldtio); /* save current port settings */

	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag = speed | CRTSCTS | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;

	/* set input mode (non-canonical, no echo,...) */
	newtio.c_lflag = 0;

	newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
	newtio.c_cc[VMIN]     = 1;   /* blocking read until 1 chars received */
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&newtio);
}

bool CRawSerial::is_ok ( void ) {
	return !fail ;
}

CRawSerial::~CRawSerial() {
	if (!fail) {
		tcsetattr(fd,TCSANOW,&oldtio);
	}
	if (opened) {
		close(fd) ;
	}
}

int CRawSerial::receive_data(void *p_buf, size_t size) {
	return read ( fd, p_buf, size ) ;
}

void CRawSerial::transmit_data(void *p_buf, size_t size) {
	write( fd, p_buf, size ) ;
}

void CRawSerial::getSpeed ( uint *speed[], size_t *pLen ) {
	static uint *pSpeed ;
	if (!pSpeed) {
		pSpeed = (uint*)malloc (sizeof(uint)*CrossSize) ;
		for (size_t i = 0; i < CrossSize; i++) {
			pSpeed[i] = Cross[i].speed ;
		}
	}
	*speed = pSpeed ;
	*pLen = CrossSize ;
}

const char *CRawSerial::getDevice() {
	return strDevice ;
}

int CRawSerial::getBaudRate() {
	return BaudRate ;
}
