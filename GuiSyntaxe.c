
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "GuiSyntaxe.y"

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
		printf("\tErreur : la variable => %s n'est pas declare vers la ligne %d\n",s,lineNumber-1);
		exit(-2);
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

void CopyFile(char *NameFile1,char *NameFile2){
  FILE *file1=fopen(NameFile1,"r");
  FILE *file2=fopen(NameFile2,"a+");
   char texte[255];
  if(file1!=NULL){
    while(!feof(file1))
    {
      fgets(texte,255,file1);
      fputs(texte,file2);      
    }
  }
   fclose(file1);
  fclose(file2);
}
void InsertCode(){
  char *header="HeaderGui.txt";
  char *CodeGen="CodeGenere.txt";
  char *CodeInte="CodeIntermediair.c";
  char *Footer="FooterGui.txt";
  CopyFile(header,CodeInte);
  CopyFile(CodeGen,CodeInte);
  CopyFile(Footer,CodeInte);
}
void GenereCode(char* string){
    FILE *file = fopen("CodeGenere.txt","a+");
      fputs(string, file);
      fseek(file,0,SEEK_END);
    fclose(file);
}

void concatenation(char *s,int type){
	char *temp ="\tint ";
	strcat(temp,strcat(s,";")) ;
	printf("%s\n",temp);
}




/* Line 189 of yacc.c  */
#line 220 "GuiSyntaxe.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MOINS = 258,
     PLUS = 259,
     DIV = 260,
     MUL = 261,
     PA_F = 262,
     PA_O = 263,
     ENTIER = 264,
     IDENTIFINT = 265,
     IDENTIFSTR = 266,
     GUI = 267,
     NEA = 268,
     CRO_O = 269,
     CRO_F = 270,
     SI = 271,
     EGAL = 272,
     DIFF = 273,
     SINON = 274,
     SINONSI = 275,
     WRITE = 276,
     READ = 277,
     INFEG = 278,
     SUPEG = 279,
     INF = 280,
     SUP = 281,
     FOR = 282,
     CHAINE = 283,
     POINT = 284,
     INLINE = 285,
     EGALCONDI = 286,
     GRIF = 287,
     MODULO = 288,
     COMMENT = 289,
     VIRGUL = 290,
     FUNCTION = 291,
     VIDE = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 222 of yacc.c  */
#line 146 "GuiSyntaxe.y"

	char var[256];
	int entier;



/* Line 222 of yacc.c  */
#line 300 "GuiSyntaxe.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 312 "GuiSyntaxe.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   168

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNRULES -- Number of states.  */
#define YYNSTATES  136

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      38,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    39,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,    11,    18,    20,    22,    25,    28,
      30,    41,    43,    45,    49,    53,    54,    56,    58,    60,
      63,    65,    67,    69,    71,    73,    75,    79,    84,    89,
      93,    98,   103,   110,   117,   123,   129,   141,   150,   154,
     158,   160,   162,   164,   166,   168,   170,   175,   180,   182,
     186,   190,   192,   196,   200,   202,   206,   209,   211,   213,
     215,   218
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    64,    -1,    42,    12,    30,    47,    13,
      -1,    42,    12,    30,    47,    13,    64,    -1,    43,    -1,
      64,    -1,    42,    43,    -1,    46,    30,    -1,    44,    -1,
      36,    28,    14,    45,    15,    38,    42,    47,    29,    30,
      -1,    10,    -1,    11,    -1,    45,    39,    10,    -1,    45,
      39,    11,    -1,    -1,    10,    -1,    11,    -1,    48,    -1,
      47,    48,    -1,    59,    -1,    54,    -1,    55,    -1,    56,
      -1,    49,    -1,    30,    -1,    52,    29,    30,    -1,    52,
      29,    30,    53,    -1,    52,    29,    30,    50,    -1,    51,
      29,    30,    -1,    51,    29,    30,    53,    -1,    50,    51,
      29,    30,    -1,    20,    14,    57,    15,    30,    47,    -1,
      16,    14,    57,    15,    30,    47,    -1,    19,    30,    47,
      29,    30,    -1,    21,    14,    28,    15,    30,    -1,    27,
      10,    14,     9,    35,     9,    15,    30,    47,    29,    30,
      -1,    27,    14,    57,    15,    30,    47,    29,    30,    -1,
      10,    58,    61,    -1,    11,    58,    11,    -1,    31,    -1,
      24,    -1,    23,    -1,    25,    -1,    26,    -1,    18,    -1,
      10,    17,    61,    30,    -1,    11,    17,    60,    30,    -1,
      11,    -1,    61,     4,    62,    -1,    61,     3,    62,    -1,
      62,    -1,    62,     6,    63,    -1,    62,     5,    63,    -1,
      63,    -1,     8,    61,     7,    -1,     3,    63,    -1,     9,
      -1,    10,    -1,    65,    -1,    64,    65,    -1,    30,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   172,   172,   175,   177,   179,   181,   183,   185,   187,
     189,   192,   193,   194,   195,   196,   198,   203,   206,   209,
     212,   217,   222,   224,   226,   228,   231,   233,   235,   237,
     239,   241,   243,   245,   247,   249,   254,   263,   265,   270,
     277,   279,   281,   283,   285,   287,   289,   295,   301,   308,
     313,   318,   324,   329,   334,   339,   344,   349,   354,   361,
     363,   365
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MOINS", "PLUS", "DIV", "MUL", "PA_F",
  "PA_O", "ENTIER", "IDENTIFINT", "IDENTIFSTR", "GUI", "NEA", "CRO_O",
  "CRO_F", "SI", "EGAL", "DIFF", "SINON", "SINONSI", "WRITE", "READ",
  "INFEG", "SUPEG", "INF", "SUP", "FOR", "CHAINE", "POINT", "INLINE",
  "EGALCONDI", "GRIF", "MODULO", "COMMENT", "VIRGUL", "FUNCTION", "VIDE",
  "'\\n'", "','", "$accept", "program", "listDeclaration", "declaration",
  "fonction", "listArgument", "variable", "listInstruction", "instruction",
  "condition", "list_condition_sinon_si", "condition_sinon_si",
  "condition_si", "condition_sinon", "affichage", "for", "while",
  "comparaison", "signe_comparaison", "affectation", "texte",
  "expressionArithmetique", "terme", "facteur", "listRetour", "Retour", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,    10,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    41,    41,    42,    42,    42,    43,    43,
      44,    45,    45,    45,    45,    45,    46,    46,    47,    47,
      48,    48,    48,    48,    48,    48,    49,    49,    49,    50,
      50,    50,    51,    52,    53,    54,    55,    56,    57,    57,
      58,    58,    58,    58,    58,    58,    59,    59,    60,    61,
      61,    61,    62,    62,    62,    63,    63,    63,    63,    64,
      64,    65
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     5,     6,     1,     1,     2,     2,     1,
      10,     1,     1,     3,     3,     0,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     3,     4,     4,     3,
       4,     4,     6,     6,     5,     5,    11,     8,     3,     3,
       1,     1,     1,     1,     1,     1,     4,     4,     1,     3,
       3,     1,     3,     3,     1,     3,     2,     1,     1,     1,
       2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    16,    17,    61,     0,     0,     0,     5,     9,     0,
       6,    59,     0,     1,     0,     7,     8,    60,    15,     0,
      11,    12,     0,     0,     0,     0,     0,     0,    25,     0,
      18,    24,     0,    21,    22,    23,    20,     0,     0,     0,
       0,     0,     0,     0,     0,     3,    19,     0,     0,    13,
      14,     0,     0,    57,    58,     0,    51,    54,    48,     0,
       0,     0,     0,     0,     0,     0,     4,    26,     0,     6,
      56,     0,     0,     0,    46,     0,     0,    47,    45,    42,
      41,    43,    44,    40,     0,     0,     0,     0,     0,     0,
       0,     0,    28,     0,    27,    16,    17,     0,    55,    50,
      49,    53,    52,    38,    39,     0,    35,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,     0,
      29,    10,     0,     0,     0,     0,    31,    30,     0,    37,
      34,     0,     0,    32,     0,    36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    22,     9,    29,    30,    31,
      92,    93,    32,    94,    33,    34,    35,    62,    84,    36,
      59,    55,    56,    57,    10,    11
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -67
static const yytype_int16 yypact[] =
{
       8,   -67,   -67,   -67,   -15,    15,    13,   -67,   -67,    24,
       6,   -67,    57,   -67,    59,   -67,   -67,   -67,    10,   109,
     -67,   -67,    -6,    65,    77,    84,    88,     0,   -67,    42,
     -67,   -67,    76,   -67,   -67,   -67,   -67,    71,    35,   113,
     106,    37,   100,   115,    37,   101,   -67,   102,     8,   -67,
     -67,   113,   113,   -67,   -67,     4,    45,   -67,   -67,   103,
      52,    52,   119,   120,   128,   123,   101,    40,     1,   101,
     -67,    23,   113,   113,   -67,   113,   113,   -67,   -67,   -67,
     -67,   -67,   -67,   -67,   113,   129,   111,   112,   108,   114,
     116,   131,   127,   121,   -67,    65,    77,    63,   -67,    45,
      45,   -67,   -67,    53,   -67,   109,   -67,   139,   109,   109,
      37,   122,   124,   125,   109,   134,    70,    85,   137,   126,
     138,   -67,   130,   132,   133,   135,   -67,   -67,   109,   -67,
     -67,   109,    97,   109,   136,   -67
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -67,   -67,   105,    -2,   -67,   -67,   -67,   -66,   -29,   -67,
     -67,    66,   -67,    39,   -67,   -67,   -67,   -43,   107,   -67,
     -67,   -49,    38,   -35,   -16,    -5
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
      46,    65,    97,    71,    15,    17,    -2,    72,    73,    37,
      43,    95,    96,    12,    44,    13,    70,    25,     1,     2,
      20,    21,    26,     1,     2,    14,    72,    73,    27,    66,
      98,    28,    69,    38,    74,   103,     3,     4,     3,   114,
     101,   102,   116,   117,     4,    49,    50,    60,    61,     4,
      75,    76,    23,    24,    16,    45,    72,    73,    25,    90,
      91,    17,   132,    26,    17,   133,    15,   118,    46,    27,
      78,    18,    28,    23,    24,    79,    80,    81,    82,    25,
      23,    24,    39,    83,    26,    46,    25,    46,    46,    19,
      27,    26,   113,    28,    40,    23,    24,    27,    41,   123,
      28,    25,    42,    46,    46,    47,    26,    23,    24,    48,
      99,   100,    27,    25,   124,    28,    51,    58,    26,    23,
      24,    52,    53,    54,    27,    25,   134,    28,    63,    64,
      26,     3,    67,    77,    86,    87,    27,    88,    89,    28,
     104,   105,   106,   107,   108,   110,   109,    91,   115,   122,
     112,   119,   125,    68,   120,   121,   126,    90,   111,   127,
     128,     0,   129,   130,     0,   131,   135,     0,    85
};

static const yytype_int16 yycheck[] =
{
      29,    44,    68,    52,     6,    10,     0,     3,     4,    15,
      10,    10,    11,    28,    14,     0,    51,    16,    10,    11,
      10,    11,    21,    10,    11,    12,     3,     4,    27,    45,
       7,    30,    48,    39,    30,    84,    30,    36,    30,   105,
      75,    76,   108,   109,    36,    10,    11,    10,    11,    36,
       5,     6,    10,    11,    30,    13,     3,     4,    16,    19,
      20,    66,   128,    21,    69,   131,    68,   110,    97,    27,
      18,    14,    30,    10,    11,    23,    24,    25,    26,    16,
      10,    11,    17,    31,    21,   114,    16,   116,   117,    30,
      27,    21,    29,    30,    17,    10,    11,    27,    14,    29,
      30,    16,    14,   132,   133,    29,    21,    10,    11,    38,
      72,    73,    27,    16,    29,    30,     3,    11,    21,    10,
      11,     8,     9,    10,    27,    16,    29,    30,    28,    14,
      21,    30,    30,    30,    15,    15,    27,     9,    15,    30,
      11,    30,    30,    35,    30,    14,    30,    20,     9,    15,
      29,    29,    15,    48,    30,    30,    30,    19,    92,   120,
      30,    -1,    30,    30,    -1,    30,    30,    -1,    61
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    11,    30,    36,    41,    42,    43,    44,    46,
      64,    65,    28,     0,    12,    43,    30,    65,    14,    30,
      10,    11,    45,    10,    11,    16,    21,    27,    30,    47,
      48,    49,    52,    54,    55,    56,    59,    15,    39,    17,
      17,    14,    14,    10,    14,    13,    48,    29,    38,    10,
      11,     3,     8,     9,    10,    61,    62,    63,    11,    60,
      10,    11,    57,    28,    14,    57,    64,    30,    42,    64,
      63,    61,     3,     4,    30,     5,     6,    30,    18,    23,
      24,    25,    26,    31,    58,    58,    15,    15,     9,    15,
      19,    20,    50,    51,    53,    10,    11,    47,     7,    62,
      62,    63,    63,    61,    11,    30,    30,    35,    30,    30,
      14,    51,    29,    29,    47,     9,    47,    47,    57,    29,
      30,    30,    15,    29,    29,    15,    30,    53,    30,    30,
      30,    30,    47,    47,    29,    30
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 173 "GuiSyntaxe.y"
    { printf("Warning	: Le programme est vide !"); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 196 "GuiSyntaxe.y"
    {/*vide*/;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 199 "GuiSyntaxe.y"
    { 
					AjoutIdentif((yyvsp[(1) - (1)].var),0);
				;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 204 "GuiSyntaxe.y"
    { AjoutIdentif((yyvsp[(1) - (1)].var),1); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 207 "GuiSyntaxe.y"
    { strcpy((yyval.var),(yyvsp[(1) - (1)].var)); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 213 "GuiSyntaxe.y"
    {
					strcpy((yyval.var),(yyvsp[(1) - (1)].var));
				;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 218 "GuiSyntaxe.y"
    {
					//strcpy($$,$1);
				;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 250 "GuiSyntaxe.y"
    {
					//
				;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 255 "GuiSyntaxe.y"
    {
					noDeclareError((yyvsp[(2) - (11)].var));
					if(atoi((yyvsp[(6) - (11)].var))<atoi((yyvsp[(4) - (11)].var))){
						printf("Dans la boucle for la valeur %s superieure a %s",(yyvsp[(4) - (11)].var),(yyvsp[(6) - (11)].var));
						exit(-1);	
					} 
				;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 266 "GuiSyntaxe.y"
    {
			noDeclareError((yyvsp[(1) - (3)].var));
		;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 271 "GuiSyntaxe.y"
    { 
			noDeclareError((yyvsp[(1) - (3)].var));
			noDeclareError((yyvsp[(3) - (3)].var));
		;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 290 "GuiSyntaxe.y"
    {	
					noDeclareError((yyvsp[(1) - (4)].var));
					strcpy((yyval.var),strcat(strcat((yyvsp[(1) - (4)].var)," = "),(yyvsp[(3) - (4)].var)));
				;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 296 "GuiSyntaxe.y"
    {	
					noDeclareError((yyvsp[(1) - (4)].var));
					strcpy((yyval.var),strcat(strcat((yyvsp[(1) - (4)].var)," = "),(yyvsp[(3) - (4)].var)));	
				;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 302 "GuiSyntaxe.y"
    {	
					noDeclareError((yyvsp[(1) - (1)].var));
					strcpy((yyval.var),(yyvsp[(1) - (1)].var));	
				;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 309 "GuiSyntaxe.y"
    { 
								strcpy((yyval.var),strcat(strcat(strdup((yyvsp[(1) - (3)].var)),"+"),strdup((yyvsp[(3) - (3)].var)))); 
							;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 314 "GuiSyntaxe.y"
    { 
								strcpy((yyval.var),strcat(strcat(strdup((yyvsp[(1) - (3)].var)),"-"),strdup((yyvsp[(3) - (3)].var)))); 
							;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 319 "GuiSyntaxe.y"
    { 
								strcpy((yyval.var),strdup((yyvsp[(1) - (1)].var))); 
							;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 325 "GuiSyntaxe.y"
    { 
					strcpy((yyval.var),strcat(strcat(strdup((yyvsp[(1) - (3)].var)),"*"),strdup((yyvsp[(3) - (3)].var)))); 
				;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 330 "GuiSyntaxe.y"
    { 
					strcpy((yyval.var),strcat(strcat(strdup((yyvsp[(1) - (3)].var)),"/"),strdup((yyvsp[(3) - (3)].var)))); 
				;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 335 "GuiSyntaxe.y"
    { 
					strcpy((yyval.var),strdup((yyvsp[(1) - (1)].var))); 
				;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 340 "GuiSyntaxe.y"
    { 
					strcpy((yyval.var),strcat(strcat(strdup("("),strdup((yyvsp[(2) - (3)].var))),strdup(")")));
				;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 345 "GuiSyntaxe.y"
    { 
					strcpy((yyval.var),strcat("-",strdup((yyvsp[(2) - (2)].var)))); 
				;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 350 "GuiSyntaxe.y"
    { 
					strcpy((yyval.var),strdup((yyvsp[(1) - (1)].var)));
				;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 355 "GuiSyntaxe.y"
    {	
					noDeclareError((yyvsp[(1) - (1)].var));	
					strcpy((yyval.var),strdup((yyvsp[(1) - (1)].var)));
				;}
    break;



/* Line 1455 of yacc.c  */
#line 1842 "GuiSyntaxe.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 366 "GuiSyntaxe.y"
		

void yyerror(char * msg){
	printf("\t Erreur de syntaxe vers la ligne %d \n", lineNumber);
}
int main(int argc,char ** argv){
	creerDico();
	if(argc>1) yyin=fopen(argv[1],"r"); // check result !!!
	lineNumber=1;
	if(!yyparse())
	//printf("Expression correct\n");
	return(0);
}
