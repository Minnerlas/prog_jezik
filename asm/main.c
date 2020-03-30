#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../vm/vm.h"
#include "../razno/hmapa/hmapa.h"

typedef struct {

} asembler;


void parsujdir(){
}

void parsujinst(){
}


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




	char c, temp[100]={0}, *t1;
	struct hmapa *mapa = naphmapa();
	int adresa=0;

	do {
		switch(c=fgetc(ul)){
			case EOF:
				kraj=1;
				break;

			case '.':								// Uputstva za asembler
				t1=temp;
				while((*(t1++)=getchar())!=' ');
				*(t1-1)='\0';
				if(!strcmp(temp,"poc")){
					int br;
					scanf("%d", &br);
					printf("poc je %d", br);
				}else{
					while(getchar()!='\n');
					printf("dir:\t%s\n", temp);
				}
				parsujdir();
				break;

			case '\t':								// Instrukcije
				t1=temp;
				while((*(t1++)=getchar())!='\n');
				*(t1-1)='\0';
				printf("inst:\t%s\n", temp);
				parsujinst();
				break;

			case '\n':								// Prazan red
				break;

			default:								// Oznaka
				temp[0]=c;
				t1=temp+1;
				while((*(t1++)=getchar())!='\n');
				*(t1-1)='\0';
				if(t1=strchr(temp, ':')){
					*t1='\0';
					printf("oznaka:\t%s\n", temp);
				}
				//printf("\"%c\"\n", c);
				break;
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
