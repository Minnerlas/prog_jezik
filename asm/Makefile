CC = gcc
LINKERFLAG = -lm

asem: main.o hmapa.o lista.o
	${CC} ${LINKERFLAG} hmapa.o main.o lista.o -o asem
	rm -rvf *.o
	rm -rvf *.gch

hmapa.o: ../razno/hmapa/hmapa.c ../razno/hmapa/hmapa.h
	${CC} -c ../razno/hmapa/hmapa.c

main.o: main.c
	${CC} -c main.c

lista.o: lista.c lista.h
	${CC} -c lista.c
