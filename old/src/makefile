CC = gcc 
CFLAGS = -g -Wall -Wextra

lextest: driver.o lex.yy.o errormsg.o util.o
	${CC} ${CFLAGS} -o lextest driver.o lex.yy.o errormsg.o util.o

driver.o: driver.c tokens.h errormsg.h util.h
	${CC} ${CFLAGS} -c driver.c

errormsg.o: errormsg.c errormsg.h util.h
	${CC} ${CFLAGS} -c errormsg.c

lex.yy.o: lex.yy.c tokens.h errormsg.h util.h
	${CC} ${CFLAGS} -c lex.yy.c

lex.yy.c: si.lex
	flex si.lex

util.o: util.c util.h
	${CC} ${CFLAGS} -c util.c

clean: 
	rm -f *.o lex.yy.c