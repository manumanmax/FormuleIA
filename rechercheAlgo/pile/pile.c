#include <stdlib.h>
#include <stdio.h>
#include "pile.h"

Pile *creerPile()
{
	Pile *pile=malloc(sizeof(Pile));
	pile->head=NULL;
	pile->taille=0;

	return pile;

}

int videPile(Pile *positionsPile)
{
	if(positionsPile->taille==0)
		return 1;

	else return 0;
}

void empiler(Pile *positionsPile, ElementFile b)
{
	NoeudP *cell=malloc(sizeof(NoeudP));

	cell->a=b;

	cell->suivant=positionsPile->head;
	positionsPile->head=cell;
	positionsPile->taille++;
}

ElementFile depiler(Pile *positionsPile)
{
	ElementFile a;
	a.generation=-1;
	if(videPile(positionsPile)) return a;
	NoeudP *cell = positionsPile->head;
	a=positionsPile->head->a;	
	positionsPile->head=positionsPile->head->suivant;
	free(cell);
	positionsPile->taille--;
	return a;
}

