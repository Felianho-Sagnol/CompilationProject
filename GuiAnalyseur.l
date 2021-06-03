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
"Gui"          {  return GUI; }
"nea"        {  return NEA; }
"write"        {  return WRITE; }
"read"        {  return READ; }
"function"        {  return FUNCTION; }
"#"          {  return SI; }
"!"          {  return SINON; }
"["          {  return CRO_O; }
"]"          {  return CRO_F; }
"!#"         {  return SINONSI; }
"##"         {  return FOR;}
"//"         {  return COMMENT;}
"!="         {  return DIFF; }
"=="         {  return EGALCONDI; }
"="          {  return EGAL;}
"<="         {  return INFEG; }
">="         {  return SUPEG; }
"<"          {  return INF; }
">"          {  return SUP; }
"."          {  return POINT;}
","          {  return VIRGUL;}
"\""         {  return GRIF;}
"-"          {  return MOINS;}
"("          {  return PA_O; }
")"          {  return PA_F; }
"*"          {  return MUL;}
"/"          {  return DIV;}
"%"          {  return MODULO;}
"+"          {  return PLUS;}
"\n"          { lineNumber++;return INLINE;}
[" "\t]      { }
{entier}     {  strcpy(yylval.var, yytext); return ENTIER; };
{identifInt}    { strcpy(yylval.var, yytext); return IDENTIFINT; };
{identifStr}    { strcpy(yylval.var, yytext); return IDENTIFSTR; };

{chaine}    { strcpy(yylval.var, yytext); return CHAINE; }

. {
    printf("\tERREUR LEXICAL: Lexeme inconnu a la ligne %d. Il s'agit de %s et comporte %d lettre(s)\n",lineNumber,yytext,yyleng);
	exit(-1);
}
%%
int valEntier;
char valIdentif[256];
char valChaine[255];
int yywrap(void) {
return 1;
}