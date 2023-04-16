%option noyywrap

%{

#include "parser.y.hpp"
#define YY_NO_UNPUT

#define YY_INPUT(buf, result, max_size)  \
	result = 0; \
	while (1) { \
		int c = fgetc(yyin); \
		if ( c == EOF ) { \
			break; \
		} \
		buf[result++] = c; \
		if (result == max_size || c == '\n') { \
			break; \
		} \
		if (c == '-') { \
			buf[result++] = '\n' ; \
			break ; \
		} \
	}
%}

%%

[1-9][0-9]?+	{
	/* Remember the number.	*/
	yylval.val = atoi(yytext) ;
	
	printf("l: Number : %s\n", yytext) ;
	fflush(stdout) ;
	return NUMBER ;
}

[0][0-9A-F]+ {
	/* Remember the hex number.	*/
	sscanf(yytext, "%x", &yylval.val) ;
	
	printf("l: Hex : %s\n", yytext) ;
	fflush(stdout) ;
	return HEX ;
}

\. {
	printf("l: Point : %s\n", yytext) ;
	fflush(stdout) ;
	return POINT ;
}

[ \t]+ {
	printf("l: Space : %s\n", yytext) ;
	fflush(stdout) ;
	return SPACE ;
}

[:] {
	printf("l: Colon : %s\n", yytext) ;
	fflush(stdout) ;
	return COLON ;
}

[-] {

	printf("l: Minus : %s\n", yytext) ;
	fflush(stdout) ;
	return MINUS ;
}

[\n] {
	yylineno++ ;
}

[абвгдеёжзийклмнопрстуфхцчшщъыьэюяМ][абвгдеёжзийклмнопрстуфхцчшщъыьэюяМ 0-9/\(\)X\.F]+ {

	yylval.str = strdup(yytext) ;

	printf ("l: Text: %s\n", yytext) ;
	fflush(stdout) ;
	return TEXT ;
}

%%
