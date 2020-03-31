#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista* napl(){
	struct lista* l = malloc(sizeof(*l));
	l->prvi=NULL;
	l->posl=NULL;
	return l;
}
void dodl(struct lista* l, const char* ime, int i){
	struct clan* c=malloc(sizeof(*c));
	c->sled = NULL;
	if(l->posl!=NULL)
		l->posl->sled = c;
	else
		l->prvi=c;

	l->posl = c;

	c->ime=malloc(sizeof(char)*(strlen(ime)+1));

	strcpy(c->ime, ime);
	c->i=i;
}

void brisil(struct lista* l){
	struct clan* c=l->prvi;
	while(c!=NULL){
		free(c->ime);
		void *t=c->sled;
		free(c);
		c=t;
	}
}

void lstampaj(struct lista *l){
	struct clan* c=l->prvi;
	while(c){
		printf("%s, %d\n", c->ime, c->i);
		c=c->sled;
	}
}
