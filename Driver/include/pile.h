/**
  *\file pile.h
  */

#ifndef PILE_H
#define PILE_H

#include <stdlib.h>
#include <stdio.h>
#include "elementFile.h"



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

/**
  *\fn int videPile(Pile *positionsPile);
  *\brief permet de savoir si la pile est vide
  *\param La pile
  *\return 1 si vide 0 sinon
  */
int videPile(Pile *positionsPile);

/**
  *\fn void empiler(Pile *positionsPile, ElementFile b);
  *\brief permet d'empiler un élément sur la pile
  *\param la pile et l'élemnt à empiler 
  *\return void
  */
void empiler(Pile *positionsPile, ElementFile b);

/**
  *\fn ElementFile depiler(Pile *positionsPile);
  *\brief permet de défiler un élément de la pile
  *\param La pile
  *\return l'élément dépilé
  */
ElementFile depiler(Pile *positionsPile);

/**
  *\fn Pile *creerPile()
  *\brief Permet de créer la pile
  *\return la pile
  */
Pile *creerPile();

#endif
