CC = gcc
LINKERFLAG = -lm

asem: main.o hmapa.o
	${CC} ${LINKERFLAG} hmapa.o main.o -o asem
	rm -rvf *.o
	rm -rvf *.gch

hmapa.o: ../razno/hmapa/hmapa.c ../razno/hmapa/hmapa.h
	${CC} -c ../razno/hmapa/hmapa.c

main.o: main.c
	${CC} -c main.c
