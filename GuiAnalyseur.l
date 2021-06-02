%{
	#include <string.h>
	#include "GuiSyntaxe.h"
	unsigned int lineNumber=1;
	int valEntier;
 	char valIdentif[256];
	char valChaine[255];
%}

nbr [0-9]
entier {nbr}+
identifInt @n_[a-zA-Z][0-9a-zA-Z_]*
identifStr @s_[a-zA-Z][0-9a-zA-Z_]*
chaine [a-zA-Z][0-9a-zA-Z_ -@]*



%%
"Gui"          { ECHO; return GUI; }
"nea"        { ECHO; return NEA; }
"write"        { ECHO; return WRITE; }
"read"        { ECHO; return READ; }
"function"        { ECHO; return FUNCTION; }
"#"          { ECHO; return SI; }
"!"          { ECHO; return SINON; }
"["          { ECHO; return CRO_O; }
"]"          { ECHO; return CRO_F; }
"!#"         { ECHO; return SINONSI; }
"##"         { ECHO; return FOR;}
"//"         { ECHO; return COMMENT;}
"!="         { ECHO; return DIFF; }
"=="         { ECHO; return EGALCONDI; }
"="          { ECHO ; return EGAL;}
"<="         { ECHO; return INFEG; }
">="         { ECHO; return SUPEG; }
"<"          { ECHO; return INF; }
">"          { ECHO; return SUP; }
"."          { ECHO; return POINT;}
","          { ECHO; return VIRGUL;}
"\""         { ECHO; return GRIF;}
"-"          { ECHO; return MOINS;}
"("          { ECHO; return PA_O; }
")"          { ECHO; return PA_F; }
"*"          { ECHO; return MUL;}
"/"          { ECHO; return DIV;}
"%"          { ECHO; return MODULO;}
"+"          { ECHO; return PLUS;}
"\n"          {ECHO; lineNumber++;return INLINE;}
[" "\t]      { }
{entier}     { ECHO; strcpy(yylval.var, yytext); return ENTIER; };
{identifInt}    { ECHO;strcpy(yylval.var, yytext); return IDENTIFINT; };
{identifStr}    { ECHO;strcpy(yylval.var, yytext); return IDENTIFSTR; };

{chaine}    { strcpy(yylval.var, yytext); return CHAINE; }

. {
    fprintf(stderr,"\tERREUR LEXICAL: Lexeme inconnu a la ligne %d. Il s'agit de %s et comporte %d lettre(s)\n",lineNumber,yytext,yyleng);
	exit(-1);
}
%%
int valEntier;
char valIdentif[256];
char valChaine[255];
int yywrap(void) {
return 1;
}