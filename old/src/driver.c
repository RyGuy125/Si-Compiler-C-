#include <stdio.h>
#include "util.h"
#include "errormsg.h"
#include "tokens.h"
#include <stdlib.h>

YYSTYPE yylval;

int yylex(void); /* prototype for the lexing function */

string toknames[] = {
"ID", "CADENA", "ENT", "COMMA", "COLON", "SEMICOLON", "LPAREN",
"RPAREN", "LBRACK", "RBRACK", "LBRACE", "RBRACE", "DOT", "PLUS",
"MINUS", "TIMES", "DIVIDE", "EQ", "NEQ", "LT", "LE", "GT", "GE",
"Y", "O", "ASSIGN", "SI", "MAS", "PARA", "POR", "ES", "ESTA",
"ESTARA", "SERA", "SEA", "ESTE", "CAMBIAR", "PAUSA", "DEJAR", 
"EN", "TERMINAR", "DI", "NIL", "CAR", "VACUO", "FLOTA", "EXTERNX", 
"CONSTANTE", "INMUTABLE", "REGRESAR", "UNION", "REDEFINE", "CREA", 
"ENTRE", "LISTA", "MAPA", "CADENA_LIT", "ENT_LIT", "FLOTA_LIT",
"VERDADERX", "FALSX"
};

string tokname(int tok) {
  return tok<257 || tok>317 ? "BAD_TOKEN" : toknames[tok-257];
}

int main(int argc, char **argv) {
 string fname; int tok;
 if (argc!=2) {fprintf(stderr,"usage: a.out filename\n"); exit(1);}
 fname=argv[1];
 EM_reset(fname);
 for(;;) {
   tok=yylex();
   if (tok==0) break;
   switch(tok) {
   case ID: case CADENA_LIT:
     printf("%10s %4d %s\n",tokname(tok),EM_tokPos,yylval.sval);
     break;
   case ENT_LIT:
     printf("%10s %4d %d\n",tokname(tok),EM_tokPos,yylval.ival);
     break;
   case FLOTA_LIT:
     printf("%10s %4d %f\n",tokname(tok), EM_tokPos, yylval.fval);
     break;
   default:
     printf("%10s %4d\n",tokname(tok),EM_tokPos);
   }
 }
 return 0;
}

