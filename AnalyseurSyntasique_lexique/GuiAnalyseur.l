%{
	#include <string.h>
	#include "GuiSyntaxe.h"
	unsigned int lineNumber=1;
	int valEntier;
 	char valIdentif[256];
%}

nbr [0-9]
chaine [a-zA-Z0-9 ]+
entier {nbr}+
identif @[a-zA-Z][0-9a-zA-Z_]*

%%
"Gui"          { ECHO; return GUI; }
"nea"        { ECHO; return NEA; }
"write"        { ECHO; return WRITE; }
"read"        { ECHO; return READ; }
"#"          { ECHO; return SI; }
"!"          { ECHO; return SINON; }
"["          { ECHO; return CRO_O; }
"]"          { ECHO; return CRO_F; }
"!#"         { ECHO; return SINONSI; }
"##"         { ECHO; return FOR;}
"!="         { ECHO; return DIFF; }
"=="         { ECHO; return EGALCONDI; }
"="          { ECHO ; return EGAL;}
"<="         { ECHO; return INFEG; }
">="         { ECHO; return SUPEG; }
"<"          { ECHO; return INF; }
">"          { ECHO; return SUP; }
"."          { ECHO; return POINT;}
"\""         { ECHO; return GRIF;}
"-"          { ECHO; return MOINS;}
"*"          { ECHO; return MUL;}
"/"          { ECHO; return DIV;}
"%"          { ECHO; return MODULO;}
"+"          { ECHO; return PLUS;}
"\n"          {ECHO; lineNumber++;return INLINE;}
[" "\t]      { }
{entier}     { ECHO; valEntier = atoi(yytext); return ENTIER; };
{identif}    { ECHO; strcpy(valIdentif, yytext); return IDENTIF; }
{chaine}    { ECHO; strcpy(valIdentif, yytext); return CHAINE; }
. {
    fprintf(stderr,"\tERREUR LEXICAL: Lexeme inconnu a la ligne %d. Il s'agit de %s et comporte %d lettre(s)\n",lineNumber,yytext,yyleng);
}
%%
int valEntier;
char valIdentif[256];
int yywrap(void) {
return 1;
}