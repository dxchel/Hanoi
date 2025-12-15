
# Makefile for g++ program Hanoi
#Made by David Xchel

#VARIABLES
CC = g++
CLIBS =  -lncurses
OBJECTS = obj/disk.o obj/game.o obj/hanoi.o obj/main.o

debug: CFLAGS = -g -Wall -Wextra
debug: obj ${OBJECTS}
	${CC} ${CFLAGS} ${CLIBS} ${OBJECTS} -o Hanoi.exe

release: CFLAGS = -O3
release: clear obj ${OBJECTS}
	${CC} ${CFLAGS} ${CLIBS} ${OBJECTS} -o Hanoi.exe
	make clean

obj:
	mkdir obj

${OBJECTS}: obj/%.o: src/%.cpp
	${CC} ${CFLAGS} ${CLIBS} -c $< -o $@

clear: clean
	rm -r Hanoi.exe
clean:
	touch obj
	rm -r obj
