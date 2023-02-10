%{

#include <string.h>
#include "util.h"
#include "tokens.h"
#include "errormsg.h"

int charPos=1;

int yywrap(void)
{
 charPos=1;
 return 1;
}

void adjust(void)
{
 EM_tokPos=charPos;
 charPos+=yyleng;
}
 
%}

%x M_COMMENT		
%x S_COMMENT 		
%x ERROR_HANDLE     
%%
" "	 {adjust(); continue;}
\t   {adjust(); continue;}
\n	 {adjust(); EM_newline(); continue;}
"/*" {adjust(); BEGIN M_COMMENT;}
"!"  {adjust(); BEGIN S_COMMENT;}
"?"  {adjust(); BEGIN S_COMMENT;}
","	 {adjust(); return COMMA;}
":"  {adjust(); return COLON;}
";"  {adjust(); return SEMICOLON;}
"("  {adjust(); return LPAREN;}
")"  {adjust(); return RPAREN;}
"["  {adjust(); return LBRACK;}
"]"  {adjust(); return RBRACK;}
"{"  {adjust(); return LBRACE;}
"}"  {adjust(); return RBRACE;}
"."  {adjust(); return DOT;}
"+"  {adjust(); return PLUS;}
"-"  {adjust(); return MINUS;}
"*"  {adjust(); return TIMES;}
"/"  {adjust(); return DIVIDE;}
"==" {adjust(); return EQ;}
"<>" {adjust(); return NEQ;}
"<"  {adjust(); return LT;}
"<=" {adjust(); return LE;}
">"  {adjust(); return GT;}
">=" {adjust(); return GE;}
"&"  {adjust(); return Y;}
"|"  {adjust(); return O;}
"="  {adjust(); return ASSIGN;}
":=" {adjust(); return ASSIGN;}
por  	    {adjust(); return POR;}
para	    {adjust(); return PARA;}
es		    {adjust(); return ES;}
esta 	    {adjust(); return ESTA;}
estara    {adjust(); return ESTARA;}
sera	    {adjust(); return SERA;}
sea	      {adjust(); return SEA;}
este	    {adjust(); return ESTE;}
cambiar   {adjust(); return CAMBIAR;}
pausa     {adjust(); return PAUSA;}
si        {adjust(); return SI;}
mas       {adjust(); return MAS;}
dejar     {adjust(); return DEJAR;}
en        {adjust(); return EN;}
terminar  {adjust(); return TERMINAR;}
nil       {adjust(); return NIL;}
ent       {adjust(); return ENT;}
cadena    {adjust(); return CADENA;}
car 	    {adjust(); return CAR;}
vacuo     {adjust(); return VACUO;}
flota	    {adjust(); return FLOTA;}
externx   {adjust(); return EXTERNX;}
constante {adjust(); return CONSTANTE;}
inmutable {adjust(); return INMUTABLE;}
regresar 	{adjust(); return REGRESAR;}
union	    {adjust(); return UNION;}
y         {adjust(); return Y;}
o         {adjust(); return O;}
redefine  {adjust(); return REDEFINE;}
crea      {adjust(); return CREA;}
entre     {adjust(); return ENTRE;}
lista	    {adjust(); return LISTA;}
mapa      {adjust(); return MAPA;}
di		    {adjust(); return DI;}
verdaderx {adjust(); return VERDADERX;}
falsx     {adjust(); return FALSX;}
[a-zA-Z][a-zA-Z0-9_]* {adjust(); yylval.sval=yytext; return ID;}
\"([^"\\]|\\.)*\"     {adjust(); yylval.sval=yytext; return CADENA_LIT;}
[0-9]+	  			  {adjust(); yylval.ival=atoi(yytext); return ENT_LIT;}
[0-9]*"."[0-9]+     {adjust(); yylval.fval=atof(yytext); return FLOTA_LIT;}
.    {adjust(); yymore(); BEGIN ERROR_HANDLE;}
<M_COMMENT>[^*]     {adjust(); }
<M_COMMENT>"*"/[^/] {adjust(); }
<M_COMMENT>"*/"     {adjust(); BEGIN INITIAL;}
<M_COMMENT>.   		{adjust(); }
<S_COMMENT>\n		{adjust(); BEGIN INITIAL;}
<S_COMMENT>.		{adjust(); }
<ERROR_HANDLE>[ \t] { 
                        adjust(); 
                        yytext[--yyleng] = '\0';
                        EM_error(EM_tokPos, "unrecognized token: %s", yytext);
                        BEGIN INITIAL;
                      }
<ERROR_HANDLE>\n {
                    adjust();
                    EM_newline();
                    yytext[--yyleng] = '\0';
                    EM_error(EM_tokPos, "unrecognized token: %s", yytext);
                    BEGIN INITIAL;
                 }
<ERROR_HANDLE><<EOF>> {
                        EM_error(EM_tokPos, "unrecognized token before EOF");
                        yyterminate();
                      }
<ERROR_HANDLE>.  { adjust(); yymore();}
