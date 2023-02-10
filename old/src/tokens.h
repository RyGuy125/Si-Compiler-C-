typedef union  {
	int pos;
	int ival;
	float fval;
	char *sval;
	} YYSTYPE;
extern YYSTYPE yylval;

# define ID 257
# define CADENA 258
# define ENT 259
# define COMMA 260
# define COLON 261
# define SEMICOLON 262
# define LPAREN 263
# define RPAREN 264
# define LBRACK 265
# define RBRACK 266
# define LBRACE 267
# define RBRACE 268
# define DOT 269
# define PLUS 270
# define MINUS 271
# define TIMES 272
# define DIVIDE 273
# define EQ 274
# define NEQ 275
# define LT 276
# define LE 277
# define GT 278
# define GE 279
# define Y 280
# define O 281
# define ASSIGN 282
# define SI 283
# define MAS 284
# define PARA 285
# define POR 286
# define ES 287
# define ESTA 288
# define ESTARA 289
# define SERA 290
# define SEA 291
# define ESTE 292
# define CAMBIAR 293
# define PAUSA 294
# define DEJAR 295
# define EN 296
# define TERMINAR 297
# define DI 298
# define NIL 299
# define CAR 300
# define VACUO 301
# define FLOTA 302
# define EXTERNX 303
# define CONSTANTE 304
# define INMUTABLE 305
# define REGRESAR 306
# define UNION 307
# define REDEFINE 308
# define CREA 309
# define ENTRE 310
# define LISTA 311
# define MAPA 312
# define CADENA_LIT 313
# define ENT_LIT 314
# define FLOTA_LIT 315
# define VERDADERX 316
# define FALSX 317