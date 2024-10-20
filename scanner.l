%{
#include <string.h>
#include <ctype.h>
#include "parser.tab.h"

void yyerror(const char *s,...);
void yywarn(const char *s,...);
int yywrap(void) {return(1);}

extern int debug;
%}

%x IN_DQUOTE
%x IN_SQUOTE

%%

[ \t]+          { }  /* Ignore whitespace */

"\n"            { return EOLN; }

"|"             { return PIPE; }
"<"             { return INFILE; }
">"             { return OUTFILE; }
">>"            { return OUTFILE_APPEND; }
"2>"            { return ERRFILE; }
"2>>"           { return ERRFILE_APPEND; }

\"([^\"]|\\.)*\"  { 
    yylval.string = strdup(yytext);
    return WORD;
}

\'([^\']|\\.)*\'  { 
    yylval.string = strdup(yytext);
    return WORD;
}

[^ \t\n"|<>]+   {
    yylval.string = strdup(yytext);
    return WORD;
}

\"              { BEGIN(IN_DQUOTE); yymore(); }
<IN_DQUOTE>[^\"]* { yymore(); }
<IN_DQUOTE>\"    { 
    BEGIN(INITIAL);
    yylval.string = strdup(yytext);
    return WORD;
}

\'              { BEGIN(IN_SQUOTE); yymore(); }
<IN_SQUOTE>[^\']* { yymore(); }
<IN_SQUOTE>\'    { 
    BEGIN(INITIAL);
    yylval.string = strdup(yytext);
    return WORD;
}

[^ \t\n"|<>]+   {
    yylval.string = strdup(yytext);
    return WORD;
}

.               { fprintf(stdout, "scanner: Bad character '%c'\n", *yytext); }

%%