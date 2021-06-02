%{
	#include <stdio.h>
	#include <stdlib.h>
    #include <string.h>
	extern FILE* yyin;
	extern int valEntier;
    extern char valIdentif[256];
    extern char valChaine[255];
	int yylex(void); // defini dans progL.cpp, utilise par yyparse()
	void yyerror(char * msg);
	extern unsigned int lineNumber; // notre compteur de lignes

    typedef struct {
      	char *identif;
       	int type;
		union
		{
			int intValue;
			char* charValue;
		} valeur;
    } ENTREE_DICO;

#define TAILLE_INITIALE_DICO 50
#define INCREMENT_TAILLE_DICO 100

char TOKENS[5][8]={"Gui","nea","write","read", "CONST"};
ENTREE_DICO *dico;
int maxDico, sommet, base;

void creerDico(void) {
    maxDico = TAILLE_INITIALE_DICO;
    dico = malloc(maxDico * sizeof(ENTREE_DICO));
    if (dico == NULL)
        yyerror("Erreur interne (pas assez de mémoire)");
    sommet = base = 0;
}

void agrandirDico(void) {
    maxDico = maxDico + INCREMENT_TAILLE_DICO;
    dico = realloc(dico, maxDico);
    if (dico == NULL)
        yyerror("Erreur interne (pas assez de mémoire)");
}

void printDico(){
	for(int i=0;i<sommet;i++){
		printf("NomVariable:  %s, TypeVariable: %d ,",dico[i].identif,dico[i].type);
		if(dico[i].type==0)
		{
			printf("ValVariable: %d\n",dico[i].valeur.intValue);
		}
		else 	printf("ValVariable: %s\n",dico[i].valeur.charValue);
	}
}

int isDeclared(char *s){
	for(int i=0;i<sommet;i++){
		if(strcmp(s,dico[i].identif)==0) {
           return 1;
		}
	}
	return 0;
}

void noDeclareError(char *s){
	if(isDeclared(s)==0){
		printf("\tErreur : la variable => %s n'est pas declare vers la ligne %d\n",s,lineNumber);
		//exit(-2);
	}
}



int isInt(char *s){
	char c[4];
	strcpy(c,"");
	strncat(c,s,2);
	if(strcmp("@n",c)==0) return 0;
	else{
		if(strcmp("@s",c)==0) return 1;
	} 
}

void AjoutIdentif(char *identif,int type) {
    if(isDeclared(identif)==1) {
		printf("ERREUR --- linge %d : Variable => %s deja declaree\n", lineNumber-1,identif);
		exit(-2);
	}
	printf("%d---%d\n", sommet,maxDico);
    if (sommet >= maxDico){
		agrandirDico();
	}
        

    dico[sommet].identif = malloc(strlen(identif) + 1);
    if (dico[sommet].identif == NULL){
		printf("Erreur interne pas assez de mémoire)");
		exit(-1);
	}
        
    strcpy(dico[sommet].identif, identif);
    dico[sommet].type = type;
	if(type == 0){
		dico[sommet].valeur.intValue = 0;
	}else{
		dico[sommet].valeur.charValue = "";
	}
    sommet++;
}


%}
%union{
	char var[256];
	int entier;
}

%left                   PLUS        MOINS       /* +- */
%left                   MUL         DIV         /* /* */
%right                  PA_O        PA_F  

%type<var> program listRetour Retour listInstruction instruction declaration listDeclaration variable
%type<var>	expressionArithmetique affectation texte terme facteur
%token<var>	ENTIER 
%token<var>	IDENTIFINT
%token<var>	IDENTIFSTR

%token<var> GUI  NEA  
%token<var>	CRO_O CRO_F SI EGAL DIFF SINON SINONSI 
%token<var> WRITE READ INFEG SUPEG INF SUP FOR CHAINE POINT PA_O PA_F
%token<var> INLINE EGALCONDI GRIF PLUS MOINS MUL MODULO DIV  COMMENT VIRGUL FUNCTION VIDE

%start program

%%
program : listRetour
		|
		listDeclaration GUI INLINE listInstruction  NEA
		|
		listDeclaration GUI INLINE listInstruction  NEA listRetour
		;
listDeclaration : declaration 
				|
				listRetour
				|
				listDeclaration declaration
				;
declaration : 	variable INLINE
				;

variable    :	IDENTIFINT
				{ AjoutIdentif($1,0); }
				|
				IDENTIFSTR
				{ AjoutIdentif($1,1); }
				;
listInstruction : 	instruction
					|
					listInstruction instruction
					;

instruction	:	affectation
				|
				INLINE
				;
affectation	:	IDENTIFINT EGAL expressionArithmetique INLINE
				{	
					noDeclareError($1);
					strcpy($$,strcat(strcat($1," = "),$3));
					printf("%s\n",$$);	
				}
				|
				IDENTIFSTR EGAL texte INLINE
				{	
					noDeclareError($1);
					strcpy($$,strcat(strcat($1," = "),$3));	
					printf("%s\n",$$);
				}
				;
texte		:	IDENTIFSTR
				{	
					noDeclareError($1);
					strcpy($$,$1);	
				}
				;

expressionArithmetique :	expressionArithmetique PLUS terme
							{ 
								strcpy($$,strcat(strcat(strdup($1),"+"),strdup($3))); 
							}
							|
							expressionArithmetique MOINS terme
							{ 
								strcpy($$,strcat(strcat(strdup($1),"-"),strdup($3))); 
							}
							|
							terme
							{ 
								strcpy($$,strdup($1)); 
							}
							;

terme	:		terme MUL facteur
				{ 
					strcpy($$,strcat(strcat(strdup($1),"*"),strdup($3))); 
				}
				|
				terme DIV facteur
				{ 
					strcpy($$,strcat(strcat(strdup($1),"/"),strdup($3))); 
				}
				|
				facteur
				{ 
					strcpy($$,strdup($1)); 
				}
				;
facteur	:		PA_O expressionArithmetique PA_F
				{ 
					strcpy($$,strcat(strcat(strdup("("),strdup($2)),strdup(")")));
				}
				|
				MOINS facteur 
				{ 
					strcpy($$,strcat("-",strdup($2))); 
				}
				|
				ENTIER
				{ 
					strcpy($$,strdup($1));
				}
				|
				IDENTIFINT
				{	
					noDeclareError($1);	
					strcpy($$,strdup($1));
				}
				;

listRetour: Retour
			|
			listRetour Retour
			;
Retour : INLINE;
%%		

void yyerror(char * msg){
	printf("\t Ligne %d : %s\n", lineNumber, msg);
}
int main(int argc,char ** argv){
	creerDico();
	if(argc>1) yyin=fopen(argv[1],"r"); // check result !!!
	lineNumber=1;
	if(!yyparse())
	printf("Expression correct\n");
	printf("============Affichage du DICO==============\n");
	printDico();
	return(0);
}