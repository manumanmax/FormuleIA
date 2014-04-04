#ifndef PILE_H
#define PILE_H

#include <stdlib.h>
#include <stdio.h>
#include "../struct.h"



typedef struct _NoeudP
{
	struct _NoeudP *suivant;
	Act a;
}NoeudP;

typedef struct _Pile
{
	NoeudP *head;
	NoeudP *courant;
	int taille;
}Pile;

int videPile(Pile *positionsPile);
void empiler(Pile *positionsPile, Act b);
Act depiler(Pile *positionsPile);
Pile *creerPile();

#endif
