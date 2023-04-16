/*
 * CTransliter.cpp
 *
 *  Created on: 17 марта 2017 г.
 *      Author: anton
 */

#include "CTransliter.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

CTransliter::CTransliter() {
	cd = iconv_open("utf-8", "wchar_t");
}

CTransliter::~CTransliter() {

	iconv_close(cd);
}

char *CTransliter::convert(char sym) {

	typedef struct sym_ref_t {
		char in ;
		wchar_t out ;
	} sym_ref_t ;

	sym_ref_t ref[] = {
			{'a', L'а'}, {'b', L'б'}, {'w', L'в'}, {'g', L'г'},
			{'d', L'д'}, {'e', L'е'}, {'\0', L'ё'}, {'v', L'ж'},
			{'z', L'з'}, {'i', L'и'}, {'j', L'й'}, {'k', L'к'},
			{'l', L'л'}, {'m', L'м'}, {'n', L'н'}, {'o', L'о'},
			{'p', L'п'}, {'r', L'р'}, {'s', L'с'}, {'t', L'т'},
			{'u', L'у'}, {'f', L'ф'}, {'h', L'х'}, {'c', L'ц'},
			{'~', L'ч'}, {'{', L'ш'}, {'}', L'щ'}, {'\0', L'ъ'},
			{'y', L'ы'}, {'x', L'ь'}, {'\0', L'э'}, {'\0', L'ю'},
			{'q', L'я'}, {'M', L'М'}, {'\r', '\0'}
	} ;

	// Find appropriate symbol

	for (size_t i = 0; i < sizeof(ref)/sizeof(sym_ref_t); i++) {
		if (sym == ref[i].in && sym != '\0') {

			wchar_t in[2] ;
			char *pin = (char*)in ;
			char *pout = usec ;

			swprintf(in, 2, L"%lc", ref[i].out ) ;
			size_t inlen = sizeof(in), outlen = sizeof(usec);

			// Convert the symbol to UTF-8.RU
			iconv(cd, &pin, &inlen, &pout, &outlen);

			return usec ;
		}
	}

	sprintf(usec, "%c", sym ) ;
	//fprintf(stderr, "tl: usec=%s\n", usec) ;

	return usec ;
}
