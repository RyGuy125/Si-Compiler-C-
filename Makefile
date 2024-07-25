CC=g++
RM=rm
CFLAGS= -c -std=c++17 -Wall -pedantic -g
LFLAGS= -std=c++17 -Wall -pedantic -g

BIN=./bin/
SOURCE=./src/
PROG=CFG LL1

OBJS = $(addprefix $(BIN), $(PROG))

all: $(OBJS)

# LL1.o: src/LL1.cpp
#	$(CC) $(CFLAGS) $^

# CFG.o: src/CFG.cpp
#	$(CC) $(CFLAGS) $^

main: main.cpp
	$(CC) $(LFLAGS) $^ $(OBJS) -o $@ 

$(BIN)%: $(SOURCE)%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) *.o main

.PHONY : all clean
