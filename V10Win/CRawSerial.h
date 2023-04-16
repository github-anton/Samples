/*
 * CRawSerial.h
 *
 *  Created on: 1 июня 2016 г.
 *      Author: anton
 */

#ifndef CRAWSERIAL_H_
#define CRAWSERIAL_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>

/* Cross table with possible speeds of the COM port */
typedef struct {
	unsigned int 	speed ;
	speed_t 		bspeed ;
} RawSerialSpeedCross_t ;

class CRawSerial {

private:
	int fd ;
	struct termios oldtio, newtio;
	char buf[255];
	bool fail ;
	bool opened ;
	static const RawSerialSpeedCross_t Cross[] ;
	static const size_t CrossSize ;
	const char *strDevice ;
	int BaudRate ;

	speed_t calc_bspeed ( unsigned int speed ) ;

public:
	CRawSerial(const char *device, unsigned int baudrate);
	virtual ~CRawSerial();
	bool is_ok ( void ) ;
	void transmit_data ( void *p_buf, size_t size ) ;
	int receive_data ( void *p_buf, size_t size ) ;
	static void getSpeed ( uint *speed[], size_t *pLen ) ;
	const char *getDevice() ;
	int getBaudRate() ;
};

#endif /* CRAWSERIAL_H_ */
