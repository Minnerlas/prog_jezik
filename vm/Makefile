CC = gcc
LINKERFLAG = -lm
OFAJLOVI = vm.o main.o 
PROFFAJLOVI = prof_vm.o prof_main.o 

cvm: vm.o main.o
	rm -rvf gmon.out
	${CC} ${LINKERFLAG} ${OFAJLOVI} -o cvm
	rm -rvf *.o
	rm -rvf *.gch

prof: prof_vm.o prof_main.o
	${CC} ${LINKERFLAG} ${PROFFAJLOVI} -o cvm -pg
	rm -rvf *.o
	rm -rvf *.gch

vm.o: vm.c vm.h
	${CC} -c vm.c

main.o: main.c vm.h vm.c
	${CC} -c main.c

prof_vm.o: vm.c vm.h
	${CC} -c vm.c -o prof_vm.o -pg

prof_main.o: main.c vm.h vm.c
	${CC} -c main.c -o prof_main.o -pg
