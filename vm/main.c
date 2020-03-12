#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "vm.h"

int main(){
	struct vm *vm;
	vm=malloc(sizeof(struct vm));
	resetvm(vm);
	registar prog[NRAM]={
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
	};

	prog[654]=IZLAZ;
	prog[655]=0;
	prog[656]=DBG;
	prog[657]=HLT;

	uram(vm, prog, NRAM);

	pokrenivm(vm, 0);

	free(vm);

	return 0;
}
