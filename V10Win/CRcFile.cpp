/*
 * CConfig.cpp
 *
 *  Created on: 13 нояб. 2015 г.
 *      Author: anton
 */

#include "CRcFile.h"
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

CRcFile::CRcFile(const char *file) {
	char *home ;
	struct stat sb ;
	home = getenv("HOME") ;
	sprintf( path, "%s/%s", home, file ) ;
	stat( path, &sb ) ;
	if ( sb.st_size == 0 ) {
		empty = true ;
	} else {
		empty = false ;
		load() ;
	}
}

CRcFile::~CRcFile() {
	save () ;
}

bool CRcFile::load() {
	FILE* fp ;
	fp = fopen ( path, "r" ) ;
	if ( fp != NULL ) {
		while ( !feof(fp) ) {
			fscanf(fp, "%s %s %s", line[0], line[1], line[2] ) ;
			/*
			 * Skip empty line.
			 */
			if (line_is_section()) {
				selectSection(line[1]) ;
			}
			if ( line_is_param() ) {
				setParamValue(line[0], line[2]) ;
			}
		}
		fclose(fp) ;
	}
	return true ;
}

bool CRcFile::line_is_param() {
	if ( strcmp(line[1], "=") == 0 ) return true ;
	return false ;
}

bool CRcFile::line_is_section() {
	if ( strcmp(line[0], "[") == 0 && strcmp(line[2], "]") == 0) return true ;
	return false ;
}

void CRcFile::selectSection( const char *sect ) {
	bool found = false ;
		for( p_cur_sect = section.begin(); p_cur_sect != section.end(); p_cur_sect++) {
			if (p_cur_sect->name == sect ) {
				found = true ;
				break ;
			}
		}
	if (!found) {
		section_t s ;
		s.name = sect ;
		section.push_back(s) ;
		p_cur_sect = section.end() - 1 ;
	}
}

void CRcFile::setParamValue( const char *param, const char *val ) {
	std::vector<param_t>::iterator p_param ;
	bool found = false ;
	for ( p_param = p_cur_sect->param.begin();
			 p_param != p_cur_sect->param.end();
			 p_param ++ ) {
		if ( p_param->name == param ) {
			found = true ;
			break ;
		}
	}
	if (found) {
		p_param->value = val ;
	} else {
		param_t p ;
		p.name = param ;
		p.value = val ;
		p_cur_sect->param.push_back(p) ;
	}
}

void CRcFile::getParamValue( const char *param, char **pvalue, const char *defaultv ) {
	size_t i ;
	bool found = false ;
	for ( i = 0; i < p_cur_sect->param.size(); i++ ) {
		if ( p_cur_sect->param[i].name == param ) {
			*pvalue = (char*)p_cur_sect->param[i].value.c_str() ;
			found = true ;
		}
	}
	if (!found) {
		*pvalue = (char*)defaultv ;
	}
}

void CRcFile::save() {
	FILE *fp ;
	fp = fopen(path, "w+") ;
	for ( size_t i = 0; i < section.size(); i++ ) {
		fprintf(fp, "[ %s ]\n", section[i].name.c_str()) ;
		for ( size_t j = 0; j < section[i].param.size(); j++ ) {
			fprintf(fp, "%s = %s\n",
					section[i].param[j].name.c_str(),
					section[i].param[j].value.c_str()) ;
		}
	}
	fclose(fp) ;
}

bool CRcFile::isEmpty() {
	return empty ;
}
