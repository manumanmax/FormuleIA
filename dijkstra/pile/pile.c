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

void empiler(Pile *positionsPile, int posi)
{
	NoeudP *cell=malloc(sizeof(NoeudP));
	cell->pos=posi;
	cell->suivant=positionsPile->head;
	positionsPile->head=cell;
	positionsPile->taille++;
}

int depiler(Pile *positionsPile)
{
	int pos;
	if(videPile(positionsPile)) return -1;
	NoeudP *cell = positionsPile->head;
	pos=positionsPile->head->pos;	
	positionsPile->head=positionsPile->head->suivant;
	free(cell);
	positionsPile->taille--;
	return pos;
}

