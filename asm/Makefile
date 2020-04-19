CC = gcc
LINKERFLAG = -lm
OFAJLOVI = hmapa.o main.o lista.o
PROFFAJLOVI = prof_hmapa.o prof_main.o prof_lista.o

asem: main.o hmapa.o lista.o
	rm -rvf gmon.out
	${CC} ${LINKERFLAG} ${OFAJLOVI} -o asem
	rm -rvf *.o
	rm -rvf *.gch

prof: prof_main.o prof_hmapa.o prof_lista.o
	${CC} ${LINKERFLAG} ${PROFFAJLOVI} -o asem -pg
	rm -rvf *.o
	rm -rvf *.gch

hmapa.o: ../razno/hmapa/hmapa.c ../razno/hmapa/hmapa.h
	${CC} -c ../razno/hmapa/hmapa.c

main.o: main.c
	${CC} -c main.c

lista.o: lista.c lista.h
	${CC} -c lista.c

prof_hmapa.o: ../razno/hmapa/hmapa.c ../razno/hmapa/hmapa.h
	${CC} -c ../razno/hmapa/hmapa.c -o prof_hmapa.o -pg

prof_main.o: main.c
	${CC} -c main.c -o prof_main.o -pg

prof_lista.o: lista.c lista.h
	${CC} -c lista.c -o prof_lista.o -pg
