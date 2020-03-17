#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "vm.h"

int main(){
	struct vm *vm;
	vm=malloc(sizeof(struct vm));
	resetvm(vm);
	registar prog[NRAM]={
		FUN,
		18,
		INK1, 
		SAB1,
		P12,
		PA1,
		P2A,
		SRP,
		5,
		DBG,
		SKOR, 
		-7,
		HLT,

		0,
		0,
		0,
		0,
		IZLAZ,
		0,
		DBG,
		DODA,
		DBG,
		VRA,
		DBG,
		POV,
		HLT,
	};

	uram(vm, prog, NRAM);

	pokrenivm(vm, 0);

	free(vm);

	return 0;
}
