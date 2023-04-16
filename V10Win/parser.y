%{

#include "V10Win.h"

#define YYDEBUG 1

extern char *yytext ;
extern int yylineno ;

int yylex(void) ;
void yyerror(const char *) ;

%}

%define api.value.type {union {char* str; int val; } }

%token NUMBER
%token TEXT
%token POINT
%token SPACE
%token MINUS
%token COLON
%token HEX

%%

session:
	session MENU_OPTION	
		| session SELECT_COMMAND
		| session MESSAGE
		| session PROMPT
		| session OPTION_ECHO
		|
		;

MENU_OPTION:
	NUMBER POINT SPACE TEXT {
	
	printf("y: Menu option: %s\n", $4.str) ;
	fflush(stdout) ;
	
	if ( $1.val == 1 ) {
		pmf->removeAllCmdMenuButtons() ;
	}
	
	pmf->emitAddCmdMenuButton(QString($4.str), $1.val) ;
}
	;

SELECT_COMMAND:
	NUMBER '\n'
	;

MESSAGE:
	TEXT {
	
	printf("y: Message: %s\n", $1.str) ;
	fflush(stdout) ;
}
	| TEXT COLON SPACE NUMBER SPACE TEXT COLON SPACE HEX SPACE TEXT COLON SPACE HEX {
	
	printf("y: ADC message: %s 0x%x\n", $1.str, $14.val) ;
	printf("y: line %i\n", yylineno) ;
	fflush(stdout) ;
}
	;

PROMPT: 
	TEXT MINUS {
	
	printf("y: Prompt1: %s\n", $1.str) ;
	fflush(stdout) ;
}
	| TEXT COLON SPACE MINUS {
	
	printf("y: Prompt2: %s\n", $1.str) ;
	fflush(stdout) ;
}
	;
	
OPTION_ECHO:
	NUMBER
	;

%%

void yyerror(const char *str) {
	fprintf(stderr, "%s: %s\n", str, yytext) ;
}


