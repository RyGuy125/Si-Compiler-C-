CC=g++
RM=rm
CFLAGS= -c -std=c++17 -Wall -pedantic -g
LFLAGS= -std=c++17 -Wall -pedantic -g

# SRC := $(wildcard *.cpp)
# OBJS := $(SRC:.cpp=.o)
OBJS = CFG.o LL1.o

all: $(OBJS)

CFG.o: CFG.cpp
	$(CC) $(CFLAGS) $^

LL1.o: LL1.cpp
	$(CC) $(CFLAGS) $^

main: main.cpp
	$(CC) $(LFLAGS) $^ $(OBJS) -o $@

# %.o: %.cpp
# 		$(CC) $(CFLAGS) $< -o $@ -I.

clean:
	$(RM) *.o

.PHONY : all clean