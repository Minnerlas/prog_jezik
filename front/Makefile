CC = gcc
LINKERFLAG = -lm

front: main.o skener.o lista.o dinniz.o hmapa.o
	${CC} ${LINKERFLAG} main.o skener.o lista.o dinniz.o hmapa.o -o front
	rm -rvf *.o
	rm -rvf *.gch

skener.o: skener.h skener.c
	${CC} -c skener.c

lista.o: lista.h lista.c
	${CC} -c lista.c

dinniz.o: ../razno/dinniz/dinniz.h ../razno/dinniz/dinniz.c
	${CC} -c ../razno/dinniz/dinniz.c

hmapa.o: ../razno/hmapa/hmapa.h ../razno/hmapa/hmapa.c
	${CC} -c ../razno/hmapa/hmapa.c

main.o: main.c
	${CC} -c main.c

