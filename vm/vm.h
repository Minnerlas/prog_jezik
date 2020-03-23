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
	SABR,					//SABR	- a+=arg1
	SPB1,					//SPB1	- a+=(r1+prenos)
	SPB2,					//SPB2	- a+=(r2+prenos)
	SPBR,					//SPBR	- a+=(arg1+prenos)
	
	ODU1,					//ODU1	- a-=r1
	ODU2,					//ODU2	- a-=r2
	ODUR,					//ODUR	- a-=arg1
	ODP1,					//ODP1	- a-=(r1+prenos)
	ODP2,					//ODP2	- a-=(r2+prenos)
	ODPR,					//ODPR	- a-=(arg1+prenos)

	PLA,					//PLA	- a	 <<= 1
	PL1,					//PL1	- r1 <<= 1
	PL2,					//PL2	- r2 <<= 1
	PDA,					//PDA	- a	 >>= 1
	PD1,					//PD1	- r1 >>= 1
	PD2,					//PD2	- r2 >>= 1

	BRZ,					//BRZ	- prenos=vece=jed=0

	UPO1,					//UPO1	- a==r1?jed=1:a>r1?vece=1
	UPO2,					//UPO2	- a==r2?jed=1:a>r2?vece=1
	UPOR,					//UPOR	- 

	SKOK,					//SKOK	- ip=RAM[ip+1]
	SKV,					//SKV	- vece	?ip=RAM[ip+1]:ip+=2
	SKJ,					//SKJ	- jed 	?ip=RAM[ip+1]:ip+=2
	SKN,					//SKN	- !jed	?ip=RAM[ip+1]:ip+=2
	SKP,					//SKP	- prenos?ip=RAM[ip+1]:ip+=2

	SKOR,					//SKOR	- ip+=(int16_t)RAM[ip+1]
	SRV,					//SRV	- vece	?ip+=(int16_t)RAM[ip+1]:ip+=2
	SRJ,					//SRJ	- jed	?ip+=(int16_t)RAM[ip+1]:ip+=2
	SRN,					//SRN	- !jed	?ip+=(int16_t)RAM[ip+1]:ip+=2
	SRP,					//SRP	- prenos?ip+=(int16_t)RAM[ip+1]:ip+=2

	UCA,					//UCA	- a	=RAM[RAM[ip+1]]
	UC1,					//UC1	- r1=RAM[RAM[ip+1]]
	UC2,					//UC2	- r2=RAM[RAM[ip+1]]
	UCAO,					//UCAO	- a	=RAM[ip+1]
	UC1O,					//UC1O	- r1=RAM[ip+1]
	UC2O,					//UC2O	- r2=RAM[ip+1]
	UCAA,					//UCAA	- a =RAM[a]
	UC1A,					//UC1A	- r1=RAM[a]
	UC2A,					//UC2A	- r2=RAM[a]

	UAR,					//UAR	- RAM[ip+1]=a
	U1R,					//U1R	- RAM[ip+1]=r1
	U2R,					//U2R	- RAM[ip+1]=r2
	U1RA,					//U1RA,	- RAM[a]=r1
	U2RA,					//U2RA, - RAM[a]=r2
	
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
	PSB,					//PSB	- sp=bp
	PBS,					//PBS	- bp=sp

	DODA,					//DODA	- RAM[--sp]=a
	DOD1,					//DOD1	- RAM[--sp]=r1
	DOD2,					//DOD2	- RAM[--sp]=r2
	DODBP,					//DODBP	- RAM[--sp]=bp

	VRA,					//VRA	- a =RAM[sp++]
	VR1,					//VR1	- r1=RAM[sp++]
	VR2,					//VR2	- r2=RAM[sp++]
	VRBP,					//VRBP	- bp=RAM[sp++]

	FUN,					//FUN	- gurni ip+2 na stek,ip=RAM[ip+1],bp=sp
	POV,					//POV	- ip=vrati sa steka,bp=sp 

	DBG		=((1<<BRBIT)-6),//DBG	- Stampa r1,r2,a
	ULAA	=((1<<BRBIT)-5),//ULAA	- a postaje ulaz sa stdin
	IZLAA	=((1<<BRBIT)-4),//IZLAA	- Ispisuje a na stdout
	ULAZ	=((1<<BRBIT)-3),//ULAZ	- RAM[arg1] postaje ulaz iz stdin
	IZLAZ	=((1<<BRBIT)-2),//IZLAZ	- Ispisuje RAM[arg1] na stdout
	HLT		=((1<<BRBIT)-1),//HLT	- Zaustavlja procesor
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

#endif /* VM_H */
