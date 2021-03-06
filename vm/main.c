#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vm.h"

int main(int argc, const char* argv[]){

	char ulaz[20]={0};
	int stdulaz=1;

	for(int i=1; i<argc; i++){
		if(argv[i][0]=='-')
			switch(argv[i][1]){
				case 'o':
				default:
					printf("Nepoznata komanda: %s.\n",argv[i]);
					exit(1);
			}
		else{
			stdulaz=0;
			strcpy(ulaz,argv[i]);
		}
	}

	registar prog[NRAM]={0};
	prog[NRAM-1]=HLT;

	if(!stdulaz){
		registar *t=prog;
		int n=0;
		FILE *fp=fopen(ulaz, "r");
		while((fscanf(fp, "%x\n", t++)!=EOF)&&(n++<NRAM));
		fclose(fp);
	}else{
		registar *t=prog;
		int n=0;
		while((scanf("%x\n",t++)!=EOF)&&(n++<NRAM));
	}

	//for(int i=0; i<NRAM; printf("%d\n", prog[i++]));

	struct vm *vm=malloc(sizeof(struct vm));
	resetvm(vm);

	uram(vm, prog, NRAM);

	pokrenivm(vm, 0);

	free(vm);

	return 0;
}
