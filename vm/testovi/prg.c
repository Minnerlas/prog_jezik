#include <stdio.h>
#include "../vm.h"

int main(){
	registar prog[NRAM]={
		ULAA,
		DODA,
		FUN,
		7,
		VRA,
		SKOK,
		590,

		//f(n)

		DODBP,
		PSB,

		PSA,
		SABR,
		3,
		UCAA,
		UPOR,
		1,
		SRN,
		7,//kraj
		UC2O,
		1,
		PBS,
		VRBP,
		POV,

		DODA,
		ODUR,
		1,
		DODA,
		FUN,
		7,
		VRA,
		VRA,
		SAB2,


		PA2,

		PBS,
		VRBP,
		POV,
	};
	prog[598]=P2A;
	prog[599]=IZLAA;
	prog[600]=HLT;

	FILE *fp=fopen("test2.prg","w");

	for(int i=0;i<NRAM;i++)
		fprintf(fp, "%x\n", prog[i]);

	return 0;
}
