#ifndef FONCTION_H
#define FONCTION_H
#define MAX 200
#define INFINITY 1000
#define SABLE 4
#define ROUTE 2
#define ARRIVE 1
#define PORTE 3
#define DEPART 0

#include <stdlib.h>
#include <stdio.h>
#include "pile/pile.h"
#include "struct.h"
#include "file/file.h"

typedef struct _Circuit
{
	short taille;
	Position arrivee;
	Position depart;

}Circuit;

typedef struct _Carte
{

	int **map;
	short tx;
	short ty;

}Carte;

void autourPosition(Position current,Vitesse vit,Carte *carte,int boost, Position autour[6][6],int valeur[6][6]);
int shortCutF(Circuit pilote,Carte carte, Position depart,Vitesse vDepart, Action action[300]);
int retrouverChemin(Pile *pileBackUp,Action action[300],int gen,int taille);
int recherchePos(ElementFile *tab,int generation, int taille);
int isArrived(Position *posArrived,short *alreadyArrived,int **map,Position pilot1,Position pilot2,int taille);

#endif
