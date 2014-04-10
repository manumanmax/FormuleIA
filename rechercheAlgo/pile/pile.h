#ifndef PILE_H
#define PILE_H

#include <stdlib.h>
#include <stdio.h>
#include "../struct.h"



typedef struct _NoeudP
{
	struct _NoeudP *suivant;
	ElementFile a;
}NoeudP;

typedef struct _Pile
{
	NoeudP *head;
	NoeudP *courant;
	int taille;
}Pile;

int videPile(Pile *positionsPile);
void empiler(Pile *positionsPile, ElementFile b);
ElementFile depiler(Pile *positionsPile);
Pile *creerPile();

#endif
