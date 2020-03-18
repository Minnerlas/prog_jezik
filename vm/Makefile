CC = gcc
LINKERFLAG = -lm

cvm: vm.o main.o
	${CC} ${LINKERFLAG} vm.o main.o -o cvm
	rm -rvf *.o
	rm -rvf *.gch

vm.o: vm.c vm.h
	${CC} -c vm.c

main.o: main.c vm.h vm.c
	${CC} -c main.c
