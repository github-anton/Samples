/*
 * CConfig.h
 *
 *  Created on: 13 нояб. 2015 г.
 *      Author: anton
 */

#ifndef CRCFILE_H_
#define CRCFILE_H_

#include <stdio.h>
#include <vector>
#include <string>

typedef struct {
	std::string name ;
	std::string value ;
} param_t;

typedef struct {
	std::string name ;
	std::vector<param_t> param ;
} section_t;

class CRcFile {
private:
	bool empty ;
	char path[256] ;
	char line[3][256] ;
	std::vector<section_t> section ;
	std::vector<section_t>::iterator p_cur_sect ;
	bool load() ;
	bool line_is_section() ;
	bool line_is_param() ;
public:
	CRcFile(const char *file);
	virtual ~CRcFile();
	void selectSection ( const char *sect ) ;
	void save() ;
	void setParamValue( const char *param, const char *value ) ;
	void getParamValue( const char *param, char **pvalue, const char *defaultv) ;
	bool isEmpty() ;
};

#endif /* CRCFILE_H_ */
