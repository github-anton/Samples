/*
 * aux.h
 *
 *  Created on: 31 марта 2017 г.
 *      Author: anton
 */

#ifndef AUX_H_
#define AUX_H_

#include <time.h>

#define MIN(a,b) ( a < b ? a: b )

#define snooze(msec)  { \
	struct timespec ts = {.tv_sec = 0, .tv_nsec = msec * 1000000} ; \
	nanosleep(&ts, NULL) ; \
}

#endif /* AUX_H_ */
