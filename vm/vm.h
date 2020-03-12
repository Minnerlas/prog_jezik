#ifndef VM_H
#define VM_H

#include <stdint.h>
#include <stddef.h>

//Makroi

#define BRBIT	(8*sizeof(registar))
#define NRAM	(1<<BRBIT)

//Tipovi

typedef uint16_t registar;
typedef uint32_t regx2;

enum instrukcije{
	NOP=0,					//NOP	- Bez operacije
	INKA,					//INKA	- aku++
	INK1,					//INK1	- r1++
	INK2,					//INK2	- r2++
	SAB1,					//SAB1	- a+=r1
	SAB2,					//SAB2	- a+=r2
	SPB1,					//SPB1	- a+=(r1+prenos)
	SPB2,					//SPB2	- a+=(r2+prenos)
	ODU1,					//ODU1	- a-=r1
	ODU2,					//ODU2	- a-=r2
	ODP1,					//ODP1	- a-=(r1+prenos)
	ODP2,					//ODP2	- a-=(r2+prenos)
	PLA,					//PLA	- a	 <<= 1
	PL1,					//PL1	- r1 <<= 1
	PL2,					//PL2	- r2 <<= 1
	PDA,					//PDA	- a	 >>= 1
	PD1,					//PD1	- r1 >>= 1
	PD2,					//PD2	- r2 >>= 1
	UPO1,					//UPO1	- a==r1?jed=1 a>r1?vece=1
	UPO2,					//UPO2	- a==r2?jed=1 a>r2?vece=1
	BRZ,					//BRZ	- prenos=vece=jed=0
	SKOK,					//SKOK	- ip=RAM[ip+1]
	SKV,					//SKV	- vece	?ip=RAM[ip+1]:ip+=2
	SKJ,					//SKJ	- jed 	?ip=RAM[ip+1]:ip+=2
	SKP,					//SKP	- prenos?ip=RAM[ip+1]:ip+=2
	SKOR,					//SKOR	- ip+=(int16_t)RAM[ip+1]
	SRV,					//SRV	- vece	?ip+=(int16_t)RAM[ip+1]:ip+=2
	SRJ,					//SRJ	- jed	?ip+=(int16_t)RAM[ip+1]:ip+=2
	SRP,					//SRP	- prenos?ip+=(int16_t)RAM[ip+1]:ip+=2
	URA,					//UCA	- a	=RAM[RAM[ip+1]]
	UR1,					//UC1	- r1=RAM[RAM[ip+1]]
	UR2,					//UC2	- r2=RAM[RAM[ip+1]]
	URAO,					//UCA	- a	=RAM[ip+1]
	UR1O,					//UCO1	- r1=RAM[ip+1]
	UR2O,					//UCO2	- r2=RAM[ip+1]
	UAR,					//UAR	- RAM[ip+1]=a
	U1R,					//U1R	- RAM[ip+1]=r1
	U2R,					//U2R	- RAM[ip+1]=r2
	
	PA1,					//PA1	- r1=a
	PA2,					//PA1	- r2=a
	P1A,					//P1A	- a=r1
	P2A,					//P1A	- a=r2
	P12,					//P12	- r2=r1
	P21,					//P21	- r1=r2
	PAS,					//PAS	- sp=a
	PSA,					//PSA	- a=sp
	PAB,					//PAB	- bp=a
	PBA,					//PBA	- a=bp

	DBG     =((1<<BRBIT)-4),//DBG	- Stampa r1,r2,a
	ULAZ    =((1<<BRBIT)-3),//ULAZ	- RAM[arg1] postaje ulaz iz stdin
	IZLAZ   =((1<<BRBIT)-2),//IZLAZ	- Ispisuje RAM[arg1] na stdout
	HLT     =((1<<BRBIT)-1),//HLT	- Zaustavlja procesor
};

struct vm {
	registar r1; 			//R1
	registar r2;			//R2
	registar aku;			//Akumulator
	registar sp;			//Pokazivac na stek
	registar bp;			//Pokazivac na pocetak trenutnog okvira steka
	registar ip;			//Pokazicac na instrukciju
	unsigned int hlt:1;		//Da li je zaustavljen
	unsigned int prenos:1;	//Ima li prenosa
	unsigned int jed:1;		//Da li je jendako
	unsigned int vece:1;	//Da li je vece

	registar ram[NRAM];
};

//Funkcije

void resetvm(struct vm*);
void uram(struct vm *vm, registar *instrukcije, size_t br);
void brisistatus(struct vm *vm);
int  pokrenivm(struct vm *vm, registar adresa);
void brzast(struct vm *vm);

#endif
