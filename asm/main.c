#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "lista.h"
#include "../vm/vm.h"
#include "../razno/hmapa/hmapa.h"

#define DEBAGOVANJE 0

#if DEBAGOVANJE == 1
#include "../vm/dbg.h"
#endif

#if DEBAGOVANJE == 1
#define STAMPINST(inst) printf(" inst je %s:\t%d\n", strinst[(inst)], (inst))
#else 
#define STAMPINST(inst) (inst)
#endif

int parsujarg(struct lista* l, const char* t, int adr){
	int arg;
	if(isdigit(*t)){
		sscanf(t, "%d", &arg);
#if DEBAGOVANJE == 1
		printf(" arg: %d\n", arg);
#endif
		return arg;
	}else{
		char* t1=(char*)t;
		for(; isalnum(*t1) || *t1=='_'; t1++);
		*t1='\0';
		dodl(l, t, adr);
		return 0;
	}
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
	int pocadr=0, adresa=0;
	int inst[NRAM]={0};
	int arg=0;
	struct hmapa* oznake=naphmapa();
	struct lista* l=napl();

	do {
		switch(c=fgetc(ul)){
			case EOF:
				kraj=1;
				break;

			case '.':								// Uputstva za asembler
				t1=temp;
				while((*(t1++)=fgetc(ul))!=' ');
				*(t1-1)='\0';
				if(!strcmp(temp,"poc")){
					int br;
					fscanf(ul, "%d", &br);
					pocadr=adresa=br;
#if DEBAGOVANJE == 1
					printf("poc je %d\n", pocadr);
#endif
				}else{
					while(fgetc(ul)!='\n');
#if DEBAGOVANJE == 1
					printf("dir:\t%s\n", temp);
#endif
				}
				break;

			case '\t':								// Instrukcije
				t1=temp;
				while((*(t1++)=fgetc(ul))!='\n');
				*(t1-1)='\0';
				for(t1=temp; *t1 && (*t1!=' ') && (*t1!=',');t1++) *t1 = tolower(*t1);

#if DEBAGOVANJE == 1
				printf("inst:\t%s\n", temp);
#endif

				if(!strncmp(temp, "nop",3)){
					STAMPINST(NOP);
					inst[adresa++]=NOP;

				}else if(!strncmp(temp, "inka",4)){
					STAMPINST(INKA);
					inst[adresa++]=INKA;

				}else if(!strncmp(temp, "ink1",4)){
					STAMPINST(INK1);
					inst[adresa++]=INK1;

				}else if(!strncmp(temp, "ink2",4)){
					STAMPINST(INK2);
					inst[adresa++]=INK2;

				}else if(!strncmp(temp, "sab1",4)){
					STAMPINST(SAB1);
					inst[adresa++]=SAB1;

				}else if(!strncmp(temp, "sab2",4)){
					STAMPINST(SAB2);
					inst[adresa++]=SAB2;

				}else if(!strncmp(temp, "sabr",4)){
					STAMPINST(SABR);
					inst[adresa++]=SABR;
					inst[adresa++]=parsujarg(l, temp+5, adresa);

				}else if(!strncmp(temp, "spb1",4)){
					STAMPINST(SPB1);
					inst[adresa++]=SPB1;

				}else if(!strncmp(temp, "spb2",4)){
					STAMPINST(SPB2);
					inst[adresa++]=SPB2;

				}else if(!strncmp(temp, "spbr",4)){
					STAMPINST(SPBR);
					inst[adresa++]=SPBR;
					inst[adresa++]=parsujarg(l, temp+5, adresa);

				}else if(!strncmp(temp, "odu1",4)){
					STAMPINST(ODU1);
					inst[adresa++]=ODU1;

				}else if(!strncmp(temp, "odu2",4)){
					STAMPINST(ODU2);
					inst[adresa++]=ODU2;

				}else if(!strncmp(temp, "odur",4)){
					STAMPINST(ODUR);
					inst[adresa++]=ODUR;
					inst[adresa++]=parsujarg(l, temp+5, adresa);

				}else if(!strncmp(temp, "odp1",4)){
					STAMPINST(ODP1);
					inst[adresa++]=ODP1;

				}else if(!strncmp(temp, "odp2",4)){
					STAMPINST(ODP2);
					inst[adresa++]=ODP2;

				}else if(!strncmp(temp, "odpr",4)){
					STAMPINST(ODPR);
					inst[adresa++]=ODPR;
					inst[adresa++]=parsujarg(l, temp+5, adresa);

				}else if(!strncmp(temp, "pla",3)){
					STAMPINST(PLA);
					inst[adresa++]=PLA;

				}else if(!strncmp(temp, "pl1",3)){
					STAMPINST(PL1);
					inst[adresa++]=PL1;

				}else if(!strncmp(temp, "pl2",3)){
					STAMPINST(PL2);
					inst[adresa++]=PL2;

				}else if(!strncmp(temp, "pda",3)){
					STAMPINST(PDA);
					inst[adresa++]=PDA;

				}else if(!strncmp(temp, "pd1",3)){
					STAMPINST(PD1);
					inst[adresa++]=PD1;

				}else if(!strncmp(temp, "pd2",3)){
					STAMPINST(PD2);
					inst[adresa++]=PD2;

				}else if(!strncmp(temp, "brz",3)){
					STAMPINST(BRZ);
					inst[adresa++]=BRZ;

				}else if(!strncmp(temp, "upo1",4)){
					STAMPINST(UPO1);
					inst[adresa++]=UPO1;

				}else if(!strncmp(temp, "upo2",4)){
					STAMPINST(UPO2);
					inst[adresa++]=UPO2;

				}else if(!strncmp(temp, "upor",4)){
					STAMPINST(UPOR);
					inst[adresa++]=UPOR;
					inst[adresa++]=parsujarg(l, temp+5, adresa);

				}else if(!strncmp(temp, "skok",4)){
					STAMPINST(SKOK);
					inst[adresa++]=SKOK;
					inst[adresa++]=parsujarg(l, temp+5, adresa);

				}else if(!strncmp(temp, "skv",3)){
					STAMPINST(SKV);
					inst[adresa++]=SKV;
					inst[adresa++]=parsujarg(l, temp+4, adresa);

				}else if(!strncmp(temp, "skj",3)){
					STAMPINST(SKJ);
					inst[adresa++]=SKJ;
					inst[adresa++]=parsujarg(l, temp+4, adresa);

				}else if(!strncmp(temp, "skn",3)){
					STAMPINST(SKN);
					inst[adresa++]=SKN;
					inst[adresa++]=parsujarg(l, temp+4, adresa);

				}else if(!strncmp(temp, "skp",3)){
					STAMPINST(SKP);
					inst[adresa++]=SKP;
					inst[adresa++]=parsujarg(l, temp+4, adresa);

				}else if(!strncmp(temp, "skor",4)){
					STAMPINST(SKOR);
					inst[adresa++]=SKP;
					inst[adresa]=parsujarg(l, temp+5, adresa)-adresa+1;
					adresa++;

				}else if(!strncmp(temp, "srv",3)){
					STAMPINST(SRV);
					inst[adresa++]=SRV;
					inst[adresa]=parsujarg(l, temp+4, adresa)-adresa+1;
					adresa++;

				}else if(!strncmp(temp, "srj",3)){
					STAMPINST(SRJ);
					inst[adresa++]=SRJ;
					inst[adresa]=parsujarg(l, temp+4, adresa)-adresa+1;
					adresa++;

				}else if(!strncmp(temp, "srn",3)){
					STAMPINST(SRN);
					inst[adresa]=SRN;
					adresa++;
					inst[adresa]=parsujarg(l, temp+4, adresa)-adresa+1;
					adresa++;

				}else if(!strncmp(temp, "srp",3)){
					STAMPINST(SRP);
					inst[adresa++]=SRP;
					inst[adresa]=parsujarg(l, temp+4, adresa)-adresa+1;
					adresa++;

				}else if(!strncmp(temp, "ucao",4)){
					STAMPINST(UCAO);
					inst[adresa++]=UCAO;
					inst[adresa++]=parsujarg(l, temp+5, adresa);

				}else if(!strncmp(temp, "uc1o",4)){
					STAMPINST(UC1O);
					inst[adresa++]=UC1O;
					inst[adresa++]=parsujarg(l, temp+5, adresa);

				}else if(!strncmp(temp, "uc2o",4)){
					STAMPINST(UC2O);
					inst[adresa++]=UC2O;
					inst[adresa++]=parsujarg(l, temp+5, adresa);

				}else if(!strncmp(temp, "ucaa",4)){
					STAMPINST(UCAA);
					inst[adresa++]=UCAA;

				}else if(!strncmp(temp, "uca",3)){
					STAMPINST(UCA);
					inst[adresa++]=UCA;
					inst[adresa++]=parsujarg(l, temp+4, adresa);

				}else if(!strncmp(temp, "uc1a",4)){
					STAMPINST(UC1A);
					inst[adresa++]=UC1A;

				}else if(!strncmp(temp, "uc1",3)){
					STAMPINST(UC1);
					inst[adresa++]=UC1;
					inst[adresa++]=parsujarg(l, temp+4, adresa);

				}else if(!strncmp(temp, "uc2a",4)){
					STAMPINST(UC2A);
					inst[adresa++]=UC2A;

				}else if(!strncmp(temp, "uc2",3)){
					STAMPINST(UC2);
					inst[adresa++]=UC2;
					inst[adresa++]=parsujarg(l, temp+4, adresa);

				}else if(!strncmp(temp, "uar",3)){
					STAMPINST(UAR);
					inst[adresa++]=UAR;
					inst[adresa++]=parsujarg(l, temp+4, adresa);

				}else if(!strncmp(temp, "u1ra",4)){
					STAMPINST(U1RA);
					inst[adresa++]=U1RA;

				}else if(!strncmp(temp, "u1r",3)){
					STAMPINST(U1R);
					inst[adresa++]=U1R;
					inst[adresa++]=parsujarg(l, temp+4, adresa);

				}else if(!strncmp(temp, "u2ra",4)){
					STAMPINST(U2RA);
					inst[adresa++]=U2RA;

				}else if(!strncmp(temp, "u2r",3)){
					STAMPINST(U2R);
					inst[adresa++]=U2R;
					inst[adresa++]=parsujarg(l, temp+4, adresa);

				}else if(!strncmp(temp, "pa1",3)){
					STAMPINST(PA1);
					inst[adresa++]=PA1;

				}else if(!strncmp(temp, "pa2",3)){
					STAMPINST(PA2);
					inst[adresa++]=PA2;

				}else if(!strncmp(temp, "p1a",3)){
					STAMPINST(P1A);
					inst[adresa++]=P1A;

				}else if(!strncmp(temp, "p2a",3)){
					STAMPINST(P2A);
					inst[adresa++]=P2A;

				}else if(!strncmp(temp, "p12",3)){
					STAMPINST(P12);
					inst[adresa++]=P12;

				}else if(!strncmp(temp, "p21",3)){
					STAMPINST(P21);
					inst[adresa++]=P21;

				}else if(!strncmp(temp, "pas",3)){
					STAMPINST(PAS);
					inst[adresa++]=PAS;

				}else if(!strncmp(temp, "psa",3)){
					STAMPINST(PSA);
					inst[adresa++]=PSA;

				}else if(!strncmp(temp, "pab",3)){
					STAMPINST(PAB);
					inst[adresa++]=PAB;

				}else if(!strncmp(temp, "pba",3)){
					STAMPINST(PBA);
					inst[adresa++]=PBA;

				}else if(!strncmp(temp, "psb",3)){
					STAMPINST(PSB);
					inst[adresa++]=PSB;

				}else if(!strncmp(temp, "pbs",3)){
					STAMPINST(PBS);
					inst[adresa++]=PBS;

				}else if(!strncmp(temp, "doda",4)){
					STAMPINST(DODA);
					inst[adresa++]=DODA;

				}else if(!strncmp(temp, "dod1",4)){
					STAMPINST(DOD1);
					inst[adresa++]=DOD1;

				}else if(!strncmp(temp, "dod2",4)){
					STAMPINST(DOD2);
					inst[adresa++]=DOD2;

				}else if(!strncmp(temp, "dodbp",5)){
					STAMPINST(DODBP);
					inst[adresa++]=DODBP;

				}else if(!strncmp(temp, "vra",3)){
					STAMPINST(VRA);
					inst[adresa++]=VRA;

				}else if(!strncmp(temp, "vr1",3)){
					STAMPINST(VR1);
					inst[adresa++]=VR1;

				}else if(!strncmp(temp, "vr2",3)){
					STAMPINST(VR2);
					inst[adresa++]=VR2;

				}else if(!strncmp(temp, "vrbp",4)){
					STAMPINST(VRBP);
					inst[adresa++]=VRBP;

				}else if(!strncmp(temp, "fun",3)){
					STAMPINST(FUN);
					inst[adresa++]=FUN;
					inst[adresa++]=parsujarg(l, temp+4, adresa);

				}else if(!strncmp(temp, "pov",3)){
					STAMPINST(POV);
					inst[adresa++]=POV;

				}else if(!strncmp(temp, "dbg",3)){
					STAMPINST(DBG);
					inst[adresa++]=DBG;

				}else if(!strncmp(temp, "ulaa",4)){
					STAMPINST(ULAA);
					inst[adresa++]=ULAA;

				}else if(!strncmp(temp, "izlaa",5)){
					STAMPINST(IZLAA);
					inst[adresa++]=IZLAA;

				}else if(!strncmp(temp, "ulaz",4)){
					STAMPINST(ULAZ);
					inst[adresa++]=ULAZ;
					inst[adresa++]=parsujarg(l, temp+5, adresa);

				}else if(!strncmp(temp, "izlaz",5)){
					STAMPINST(IZLAZ);
					inst[adresa++]=IZLAZ;
					inst[adresa++]=parsujarg(l, temp+6, adresa);

				}else if(!strncmp(temp, "hlt",3)){
					STAMPINST(HLT);
					inst[adresa++]=HLT;
				}



				break;

			case '\n':								// Prazan red
				break;

			default:								// Oznaka
				temp[0]=c;
				t1=temp+1;
				while((*(t1++)=fgetc(ul))!='\n');
				*(t1-1)='\0';
				if(t1=strchr(temp, ':')){
					*t1='\0';
#if DEBAGOVANJE == 1
					printf("oznaka:\t%s\n", temp);
#endif
					dodhmapa(oznake, temp, NINT, &adresa);

				}else{
					printf("\"%s\"\n", temp);
				}
				break;
		}

	} while(!kraj);



	struct clan *cl = l->prvi;
	while(cl){
		inst[cl->i]+=nadjhmapa(oznake, cl->ime)->vred.i;
		cl=cl->sled;
	}




#if DEBAGOVANJE == 1
	putchar('\n');
	printf("poc: %d\n", pocadr);

	for(int i=pocadr;i<pocadr+20;i++){
		//printf("%d\n", (uint16_t)inst[i]);
		printf("%d\n", inst[i]);
	}


	putchar('\n');
	hstampaj(oznake);

	putchar('\n');
	lstampaj(l);
#endif

#if DEBAGOVANJE == 1
	int duzina = 20;
	putchar('\n');
#else
	int duzina = NRAM;
#endif


	for(int i=0; i<duzina; i++){
		fprintf(iz, "%x\n", (uint16_t)inst[i]);
	}
#if DEBAGOVANJE == 1
	putchar('\n');
	for(int i=0; i<100; i++){
		printf("%d:\t%d\t%s\n", i, (uint16_t)inst[i], strinst[inst[i]]);
	}
#endif

	if(!stdizlaz)
		fclose(iz);

	if(!stdulaz)
		fclose(ul);

	return 0;
}
