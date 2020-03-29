#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../vm/vm.h"
#include "hmapa.h"

typedef struct {

} asembler;


int main(int argc, const char* argv[]){

	char ulaz[50]={0};
	char izlaz[50]={0};
	int stdulaz=1;
	int stdizlaz=1;
	int kraj=0;

	for(int i=1; i<argc; i++){
		//printf("%s ", argv[i]);
		if(argv[i][0]=='-')
			switch(argv[i][1]){
				case 'o':
					stdizlaz=0;
					if(i<argc)
						strcpy(izlaz, argv[++i]);
					else{
						printf("Upotreba: -o <izlazni fajl>\n");
						exit(1);
					}
					break;
				default:
					printf("Nepoznata komanda: %s.\n", argv[i]);
					exit(1);
			}
		else{
			stdulaz=0;
			strcpy(ulaz, argv[i]);
		}
	}
	//putchar('\n');

	char t[100];



	FILE *ul, *iz;

	if(stdulaz)
		ul=stdin;
	else
		ul=fopen(ulaz, "r");

	
	if(stdizlaz)
		iz=stdout;
	else
		iz=fopen(izlaz, "w");
	

	do {
		switch(c=fgetc(ul)){
			case EOF:
				kraj=1;
				break;

			case '\t':
				break;

			default:

		}

	} while(!kraj);


	fscanf(ul, "%s", &t);
	fprintf(iz, "%s", t);

	printf("%s\n",t);






	if(!stdizlaz)
		fclose(iz);

	if(!stdulaz)
		fclose(ul);

	return 0;
}
