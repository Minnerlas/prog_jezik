#include "vm.h"
#include <stdint.h>
#include <stdio.h>

#define DEBAGOVANJE 0

void resetvm(struct vm *vm){
	vm->r1	= 0;
	vm->r2	= 0;
	vm->aku	= 0;
	vm->sp	= NRAM-1;
	vm->bp	= NRAM-1;
	vm->ip	= 0;
	brisistatus(vm);
}

void uram(struct vm *vm, registar *inst, size_t br){
	registar *p= vm->ram;
	for(size_t i=0; (i<br) && (i<NRAM); *p++=*inst++,i++);
}

void brisistatus(struct vm *vm){
	vm->hlt    = 0;
	vm->prenos = 0;
	vm->jed    = 0;
	vm->vece   = 0;
}

void brzast(struct vm *vm){
	vm->prenos	= 0;
	vm->jed		= 0;
	vm->vece	= 0;
}

#if DEBAGOVANJE == 1

char *strinst[NRAM] = {
	"NOP"		,
	"INKA"		,
	"INK1"		,
	"INK2"		,
	"SAB1"		,
	"SAB2"		,
	"SABR"		,
	"SPB1"		,
	"SPB2"		,
	"SPBR"		,
	"ODU1"		,
	"ODU2"		,
	"ODUR"		,
	"ODP1"		,
	"ODP2"		,
	"ODPR"		,
	"PLA"		,
	"PL1"		,
	"PL2"		,
	"PDA"		,
	"PD1"		,
	"PD2"		,
	"BRZ"		,
	"UPO1"		,
	"UPO2"		,
	"UPOR"		,
	"SKOK"		,
	"SKV"		,
	"SKJ"		,
	"SKN"		,
	"SKP"		,
	"SKOR"		,
	"SRV"		,
	"SRJ"		,
	"SRN"		,
	"SRP"		,
	"UCA"		,
	"UC1"		,
	"UC2"		,
	"UCAO"		,
	"UC1O"		,
	"UC2O"		,
	"UCAA"		,
	"UC1A"		,
	"UC2A"		,
	"UAR"		,
	"U1R"		,
	"U2R"		,
	"U1RA"		,
	"U2RA"		,
	"PA1"		,
	"PA2"		,
	"P1A"		,
	"P2A"		,
	"P12"		,
	"P21"		,
	"PAS"		,
	"PSA"		,
	"PAB"		,
	"PBA"		,
	"PSB"		,
	"PBS"		,
	"DODA"		,
	"DOD1"		,
	"DOD2"		,
	"DODBP"		,
	"VRA"		,
	"VR1"		,
	"VR2"		,
	"VRBP"		,
	"FUN"		,
	"POV"		,

	[((1<<BRBIT)-6)] = "DBG"	,
	[((1<<BRBIT)-5)] = "ULAA"	,
	[((1<<BRBIT)-4)] = "IZLAA"	,
	[((1<<BRBIT)-3)] = "ULAZ"	,
	[((1<<BRBIT)-2)] = "IZLAZ"	,
	[((1<<BRBIT)-1)] = "HLT"	,
};

#endif

int pokrenivm(struct vm *vm, registar adr){
	vm->ip=adr;
	regx2 t=0;
	registar arg1=0;
	enum instrukcije inst;
	while(!vm->hlt){
		inst=vm->ram[vm->ip];
#if DEBAGOVANJE == 1
		//printf("adr: %d inst: %d\n", vm->ip, inst);
		printf("adr: %d inst: %s\n", vm->ip, strinst[inst]);
		printf("r1=%5d, r2=%5d, aku=%5d, sp=%5d, bp=%5d, ip=%5d\n",
				vm->r1, vm->r2, vm->aku, vm->sp, vm->bp, vm->ip);
		//printf("%d\n",vm->aku);
#endif
		switch(inst){
			case NOP:
				vm->ip++;
				break;

			case INKA:
				t=vm->aku+1;
				if(t>((1<<BRBIT)-1))
					vm->prenos=1,t-=((1<<BRBIT)-1);
				vm->aku=t;
				vm->ip++;
				break;

			case INK1:
				t=vm->r1+1;
				if(t>((1<<BRBIT)-1))
					vm->prenos=1,t-=((1<<BRBIT)-1);
				vm->r1=t;
				vm->ip++;
				break;

			case INK2:
				t=vm->r2+1;
				if(t>((1<<BRBIT)-1))
					vm->prenos=1,t-=((1<<BRBIT)-1);
				vm->r2=t;
				vm->ip++;
				break;

				//Sabiranje

			case SAB1:
				t=vm->r1+vm->aku;
				if(t>((1<<BRBIT)-1))
					vm->prenos=1,t-=((1<<BRBIT)-1);
				vm->aku=t;
				vm->ip++;
				break;

			case SAB2:
				t=vm->r2+vm->aku;
				if(t>((1<<BRBIT)-1))
					vm->prenos=1,t-=((1<<BRBIT)-1);
				vm->aku=t;
				vm->ip++;
				break;

			case SABR:
				t=vm->aku+vm->ram[vm->ip+1];
				if(t>((1<<BRBIT)-1))
					vm->prenos=1,t-=((1<<BRBIT)-1);
				vm->aku=t;
				vm->ip+=2;
				break;

			case SPB1:
				t=vm->r1+vm->aku+vm->prenos;
				if(t>((1<<BRBIT)-1))
					vm->prenos=1,t-=((1<<BRBIT)-1);
				vm->aku=t;
				vm->ip++;
				break;

			case SPB2:
				t=vm->r2+vm->aku+vm->prenos;
				if(t>((1<<BRBIT)-1))
					vm->prenos=1,t-=((1<<BRBIT)-1);
				vm->aku=t;
				vm->ip++;
				break;

			case SPBR:
				t=vm->ram[vm->ip]+vm->aku+vm->prenos;
				if(t>((1<<BRBIT)-1))
					vm->prenos=1,t-=((1<<BRBIT)-1);
				vm->aku=t;
				vm->ip+=2;
				break;

				//Oduzimanje

			case ODU1:
				vm->prenos= vm->aku < vm->r1 ?1:0;
				vm->aku-=vm->r1;
				vm->ip++;
				break;

			case ODU2:
				vm->prenos= vm->aku < vm->r2 ?1:0;
				vm->aku-=vm->r2;
				vm->ip++;
				break;

			case ODUR:
				arg1=vm->ram[vm->ip+1];
				vm->prenos= vm->aku < arg1 ?1:0;
				vm->aku-=arg1;
				vm->ip+=2;
				break;

			case ODP1:
				vm->prenos= vm->aku < vm->r1 ?1:0;
				vm->aku-=(vm->r1+vm->prenos);
				vm->ip++;
				break;

			case ODP2:
				vm->prenos= vm->aku < vm->r2 ?1:0;
				vm->aku-=(vm->r2+vm->prenos);
				vm->ip++;
				break;

			case ODPR:
				arg1=vm->ram[vm->ip+1];
				vm->prenos= vm->aku < arg1 ?1:0;
				vm->aku-=(arg1+vm->prenos);
				vm->ip+=2;
				break;

				//Pomeranje

			case PLA:
				arg1=vm->prenos;
				vm->prenos=vm->aku & (1<<(BRBIT-1))?1:0;
				vm->aku<<=1;
				vm->aku+=arg1;
				vm->ip++;
				break;

			case PL1:
				arg1=vm->prenos;
				vm->prenos=vm->r1 & (1<<(BRBIT-1))?1:0;
				vm->r1<<=1;
				vm->r1+=arg1;
				vm->ip++;
				break;

			case PL2:
				arg1=vm->prenos;
				vm->prenos=vm->r2 & (1<<(BRBIT-1))?1:0;
				vm->r2<<=1;
				vm->r2+=arg1;
				vm->ip++;
				break;

			case PDA:
				arg1=vm->prenos;
				vm->prenos=vm->aku & 0x1 ?1:0;
				vm->aku>>=1;
				vm->aku+=((1<<BRBIT-1)*arg1);
				vm->ip++;
				break;

			case PD1:
				arg1=vm->prenos;
				vm->prenos=vm->r1 & 0x1 ?1:0;
				vm->r1>>=1;
				vm->r1+=((1<<BRBIT-1)*arg1);
				vm->ip++;
				break;

			case PD2:
				arg1=vm->prenos;
				vm->prenos=vm->r2 & 0x1 ?1:0;
				vm->r2>>=1;
				vm->r2+=((1<<BRBIT-1)*arg1);
				vm->ip++;
				break;

				//Brrisanje statusa

			case BRZ:
				brzast(vm);
				vm->ip++;
				break;

				//Uporedjivanje

			case UPO1:
				if(vm->aku == vm->r1)
					vm->jed=1,vm->vece=0;
				else if(vm->aku>vm->r1)
					vm->jed=0,vm->vece=1;
				else
					vm->jed=0,vm->vece=0;
				vm->ip++;
				break;

			case UPO2:
				if(vm->aku == vm->r2)
					vm->jed=1,vm->vece=0;
				else if(vm->aku>vm->r2)
					vm->jed=0,vm->vece=1;
				else
					vm->jed=0,vm->vece=0;
				vm->ip++;
				break;

			case UPOR:
				arg1=vm->ram[vm->ip+1];
				if(vm->aku == arg1)
					vm->jed=1,vm->vece=0;
				else if(vm->aku>arg1)
					vm->jed=0,vm->vece=1;
				else
					vm->jed=0,vm->vece=0;
				vm->ip+=2;
				break;

				//Skokovi

			case SKOK:
				vm->ip=vm->ram[vm->ip+1];
				break;

			case SKV:
				if(vm->vece)
					vm->ip=vm->ram[vm->ip+1];
				else
					vm->ip+=2;
				break;

			case SKJ:
				if(vm->jed)
					vm->ip=vm->ram[vm->ip+1];
				else
					vm->ip+=2;
				break;

			case SKN:
				if(!vm->jed)
					vm->ip=vm->ram[vm->ip+1];
				else
					vm->ip+=2;
				break;

			case SKP:
				if(vm->prenos)
					vm->ip=vm->ram[vm->ip+1];
				else
					vm->ip+=2;
				break;

				//Relativni skokovi

			case SKOR:
				vm->ip+=(int16_t)vm->ram[vm->ip+1];
				break;

			case SRV:
				if(vm->vece)
					vm->ip+=(int16_t)vm->ram[vm->ip+1];
				else
					vm->ip+=2;
				break;

			case SRJ:
				if(vm->jed)
					vm->ip+=(int16_t)vm->ram[vm->ip+1];
				else
					vm->ip+=2;
				break;

			case SRN:
				if(!vm->jed)
					vm->ip+=(int16_t)vm->ram[vm->ip+1];
				else
					vm->ip+=2;
				break;

			case SRP:
				if(vm->prenos)
					vm->ip+=(int16_t)vm->ram[vm->ip+1];
				else
					vm->ip+=2;
				break;

				//Ucitavanje iz memorije

			case UCA:
				arg1=vm->ram[vm->ip+1];
				vm->aku=vm->ram[arg1];
				vm->ip+=2;
				break;

			case UC1:
				arg1=vm->ram[vm->ip+1];
				vm->r1=vm->ram[arg1];
				vm->ip+=2;
				break;

			case UC2:
				arg1=vm->ram[vm->ip+1];
				vm->r2=vm->ram[arg1];
				vm->ip+=2;
				break;

			case UCAO:
				vm->aku=vm->ram[vm->ip+1];
				vm->ip+=2;
				break;

			case UC1O:
				vm->r1=vm->ram[vm->ip+1];
				vm->ip+=2;
				break;

			case UC2O:
				vm->r2=vm->ram[vm->ip+1];
				vm->ip+=2;
				break;

			case UCAA:
				vm->aku=vm->ram[vm->aku];
				vm->ip++;
				break;

			case UC1A:
				vm->r1=vm->ram[vm->aku];
				vm->ip++;
				break;

			case UC2A:
				vm->r2=vm->ram[vm->aku];
				vm->ip++;
				break;

				//U ram

			case UAR:
				vm->ram[vm->ip+1]=vm->aku;
				vm->ip+=2;
				break;

			case U1R:
				vm->ram[vm->ip+1]=vm->r1;
				vm->ip+=2;
				break;

			case U2R:
				vm->ram[vm->ip+1]=vm->r2;
				vm->ip+=2;
				break;

			case U1RA:
				vm->ram[vm->aku]=vm->r1;
				vm->ip++;
				break;

			case U2RA:
				vm->ram[vm->aku]=vm->r2;
				vm->ip++;
				break;

				//Premestanje iz registra u registar

			case PA1:
				vm->r1=vm->aku;
				vm->ip++;
				break;

			case PA2:
				vm->r2=vm->aku;
				vm->ip++;
				break;

			case P1A:
				vm->aku=vm->r1;
				vm->ip++;
				break;

			case P2A:
				vm->aku=vm->r2;
				vm->ip++;
				break;

			case P12:
				vm->r2=vm->r1;
				vm->ip++;
				break;

			case P21:
				vm->r1=vm->r2;
				vm->ip++;
				break;

			case PAS:
				vm->sp=vm->aku;
				vm->ip++;
				break;

			case PSA:
				vm->aku=vm->sp;
				vm->ip++;
				break;

			case PAB:
				vm->bp=vm->aku;
				vm->ip++;
				break;

			case PBA:
				vm->aku=vm->bp;
				vm->ip++;
				break;

			case PSB:
				vm->bp=vm->sp;
				vm->ip++;
				break;

			case PBS:
				vm->sp=vm->bp;
				vm->ip++;
				break;

				//Operacije na steku

			case DODA:
				vm->ram[vm->sp--]=vm->aku;
				vm->ip++;
				break;

			case DOD1:
				vm->ram[vm->sp--]=vm->r1;
				vm->ip++;
				break;

			case DOD2:
				vm->ram[vm->sp--]=vm->r2;
				vm->ip++;
				break;

			case DODBP:
				vm->ram[vm->sp--]=vm->bp;
				vm->ip++;
				break;

			case VRA:
				vm->aku=vm->ram[++vm->sp];
				vm->ip++;
				break;

			case VR1:
				vm->r1=vm->ram[++vm->sp];
				vm->ip++;
				break;

			case VR2:
				vm->r2=vm->ram[++vm->sp];
				vm->ip++;
				break;

			case VRBP:
				vm->bp=vm->ram[++vm->sp];
				vm->ip++;
				break;

				//Poziv funkcije

			case FUN:
				arg1=vm->ram[vm->ip+1];
				vm->ram[vm->sp--]=vm->ip+2;
				vm->ip=arg1;
				break;

			case POV:
				vm->ip=vm->ram[++vm->sp];
				break;




			case DBG:
				printf("r1=%5d, r2=%5d, aku=%5d, sp=%5d, bp=%5d, ip=%5d\n",
						vm->r1, vm->r2, vm->aku, vm->sp, vm->bp, vm->ip);
				vm->ip++;
				break;

			case ULAA:
				printf("ULAZ:  ");
				scanf("%hu",&(vm->aku));
				vm->ip++;
				break;

			case IZLAA:
				printf("IZLAZ: %hu\n", vm->aku);
				vm->ip++;
				break;

			case ULAZ:
				printf("ULAZ:  ");
				scanf("%hu",&(vm->ram[vm->ram[vm->ip+1]]));
				vm->ip+=2;
				break;

			case IZLAZ:
				printf("IZLAZ: %hu\n",vm->ram[vm->ram[vm->ip+1]]);
				vm->ip+=2;
				break;

			case HLT:
				vm->hlt=1;
				break;

			default:
				printf("Nepoznata instrukcija: %hu, na adresi %hu\n", inst, vm->ip);
				return 0;
		}

	}

	return 1;
}
