#include "vm.h"
#include <stdint.h>
#include <stdio.h>

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

int pokrenivm(struct vm *vm, registar adr){
	vm->ip=adr;
	regx2 t=0;
	registar arg1=0;
	enum instrukcije inst;
	while(!vm->hlt){
		inst=vm->ram[vm->ip];
		//printf("%d\n",vm->aku);
		switch(inst){
			case NOP:
				vm->ip++;
				break;

			case INKA:
				vm->aku++;
				vm->ip++;
				break;

			case INK1:
				vm->r1++;
				vm->ip++;
				break;

			case INK2:
				vm->r2++;
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

				//ODUZIMANJE
				//ODUZIMANJE
				//ODUZIMANJE
				//ODUZIMANJE


				//POMERANJE
				//POMERANJE
				//POMERANJE
				//POMERANJE


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

			case BRZ:
				brzast(vm);
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

			case SRP:
				if(vm->prenos)
					vm->ip+=(int16_t)vm->ram[vm->ip+1];
				else
					vm->ip+=2;
				break;


				//Ucitavanje iz memorije

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

			case UCO1:
				vm->r1=vm->ram[vm->ip+1];
				vm->ip+=2;
				break;

			case UCO2:
				vm->r2=vm->ram[vm->ip+1];
				vm->ip+=2;
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




			case DBG:
				printf("r1=%5d, r2=%5d, aku=%5d, sp=%5d, bp=%5d, ip=%5d\n",
						vm->r1, vm->r2, vm->aku, vm->sp, vm->bp, vm->ip);
				vm->ip++;
				break;

			case ULAZ:
				printf("ULAZ:  ");
				scanf("%hd",&(vm->ram[vm->ram[vm->ip+1]]));
				vm->ip+=2;
				break;

			case IZLAZ:
				printf("IZLAZ: %d\n",vm->ram[vm->ram[vm->ip+1]]);
				vm->ip+=2;
				break;

			case HLT:
				vm->hlt=1;
				break;

			default:
				printf("Nepoznata instrukcija: %d\n",inst);
				return 0;
		}

	}

	return 1;
}
