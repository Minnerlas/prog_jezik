#include <stdlib.h>
#include <stdio.h>
#include "vm.h"

int main(){
		struct vm *vm;
		vm=malloc(sizeof(struct vm));
		resetvm(vm);
		uint16_t prog[NRAM]={
				INK1, 
				SAB1,
				P12,
				PA1,
				P2A,
				SKP,
				99,
				DBG,
				SKOK, 
				1
		};

		prog[654]=HLT;
		uram(vm, prog, NRAM);

		pokrenivm(vm, 0);

		return 0;
}
