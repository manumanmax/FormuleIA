#ifndef PATH_H
#define PATH_H
#define MAX 200
#define ROUTE 25
#define SAND 1
#define SIZEBOOST 25
#define NBBOOST 2
#define SIZEBIDIMTABLE 5

#include <stdlib.h>
#include <stdio.h>
#include "../include/pile.h"
#include "vitesse.h"
#include "action.h"
#include "position.h"
#include "elementFile.h"
#include "act.h"
#include "../include/file.h"

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
	 int **mapCopie;

}Carte;

int autourPosition(Position current,Vitesse vit,Carte *carte,int boost,Position autour[SIZEBIDIMTABLE][SIZEBIDIMTABLE],int valeur[SIZEBIDIMTABLE][SIZEBIDIMTABLE]);
int shortCutF(Circuit pilote,Carte carte, Position depart,Vitesse vDepart, Action *action, int* nbBoost);
int retrouverChemin(Pile *pileBackUp,Action *action,int gen,int taille);
int recherchePos(ElementFile *tab,int generation, int taille);
int isArrived(Position *posArrived,short *alreadyArrived,int **map,Position pilot1,Position pilot2,int taille);
void destruction(char ****tab,int tx,int ty);
char opti(Vitesse v);
int isPossible(Position current,Vitesse vCurrent, Carte *carte,int boost);

#endif
