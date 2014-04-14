#ifndef PILE_H
#define PILE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct _NoeudP
{
	struct _NoeudP *suivant;
	int pos;
}NoeudP;

typedef struct _Pile
{
	NoeudP *head;
	NoeudP *courant;
	int taille;
}Pile;

int videPile(Pile *positionsPile);
void empiler(Pile *positionsPile, int posi);
int depiler(Pile *positionsPile);
Pile *creerPile();

#endif
