#ifndef LISTA_H
#define LISTA_H

//Makroi

//Tipovi

struct lista{
	struct clan* prvi;
	struct clan* posl;
};

struct clan{
	struct clan* sled;
	char* ime;
	int i;
};

//Funkcije

struct lista*	napl();
void			dodl(struct lista* l, const char* ime, int i);
void 			brisil(struct lista* l);
void			lstampaj(struct lista* l);

#endif /* LISTA_H */
