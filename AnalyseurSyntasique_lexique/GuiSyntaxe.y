%{
	#include <stdio.h>
	extern FILE* yyin;
	int yylex(void); // defini dans progL.cpp, utilise par yyparse()
	void yyerror(const char * msg);
	extern unsigned int lineNumber; // notre compteur de lignes
%}

%token GUI IDENTIF NEA ENTIER CRO_O CRO_F SI EGAL DIFF SINON SINONSI 
%token WRITE READ INFEG SUPEG INF SUP FOR CHAINE POINT
%token INLINE EGALCONDI GRIF PLUS MOINS MUL MODULO DIV

%start program

%%
program : listRetour
		{printf("Programme vide");}
		|
		listDeclaration  GUI INLINE listInstruction NEA listRetour
			;
listDeclaration :	declaration
					|
					listDeclaration declaration
					;
declaration : IDENTIF INLINE;

listInstruction :instruction 
				|
				listInstruction instruction 
				;
			
instruction :	affichage 
				|
				affectation 
				|
				condition 
				;

affichage :		WRITE CRO_O contenu CRO_F INLINE
				;
contenu: simple_affichage
		|
		texte
		|
		concat
        ;
concat: texte POINT simple_affichage
		|
		simple_affichage POINT texte
		|
		texte POINT simple_affichage POINT texte
		;
texte:	GRIF list_chaine GRIF
		;
list_chaine:  CHAINE 
			|
			list_chaine CHAINE
			;
simple_affichage:ENTIER
				|
				IDENTIF
				;

affectation :	IDENTIF EGAL expression INLINE
				;
condition: 		condition_si POINT INLINE
            	|
            	condition_si POINT INLINE condition_sinon 
            	|
            	condition_si POINT INLINE list_condition_sinon_si 
            	;
list_condition_sinon_si: condition_sinon_si POINT INLINE
						|
						condition_sinon_si POINT INLINE condition_sinon 
						|
						list_condition_sinon_si condition_sinon_si POINT INLINE
                         ;
condition_sinon_si:SINONSI CRO_O comparaison CRO_F INLINE listInstruction 
 				; 
condition_si  :SI CRO_O comparaison CRO_F INLINE listInstruction 
				;
condition_sinon: SINON INLINE listInstruction POINT INLINE
				;

comparaison: IDENTIF signe_comparaison expression
				;
signe_comparaison: EGALCONDI 
				   |
				   SUPEG 
				   |
				   INFEG
				   |
				   INF
				   |
				   SUP
				   |
				   DIFF
				   ;
expression :	IDENTIF 
				|
				ENTIER
				;		
listRetour: Retour
			|
			listRetour Retour
			;
Retour : INLINE;
%%		

void yyerror( const char * msg){
	printf("\t Ligne %d : %s\n", lineNumber, msg);
	}
	int main(int argc,char ** argv){
	if(argc>1) yyin=fopen(argv[1],"r"); // check result !!!
	lineNumber=1;
	if(!yyparse())
	printf("Expression correct\n");
	return(0);
}