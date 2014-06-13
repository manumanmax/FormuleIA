/**
  \file path.h
  */

#ifndef PATH_H
#define PATH_H
#define MAX 200
#define ROUTE 25
#define SAND 1
#define SIZEBOOST 25
#define NBBOOST 5
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


/**
  *\fn int autourPosition(Position current,Vitesse vit,Carte *carte,int boost,Position autour[SIZEBIDIMTABLE][SIZEBIDIMTABLE],int valeur[SIZEBIDIMTABLE][SIZEBIDIMTABLE]);

  *\brief Permet de savoir ce qui se situe autour de la voiture
  *\param La position courrante
  *\param La vitesse en cours
  *\param La carte
  *\param Si on utilise un boost
  *\param Le tableau qui sera rempli
  *\param Le tableau de poids
  *\return 1 si il existe une valeur atteignable par la voiture, ou 0 sinon
  */
int autourPosition(Position current,Vitesse vit,Carte *carte,int boost,Position autour[SIZEBIDIMTABLE][SIZEBIDIMTABLE],int valeur[SIZEBIDIMTABLE][SIZEBIDIMTABLE]);


/**
  *\fn int shortCutF(Circuit pilote,Carte carte, Position depart,Vitesse vDepart, Action *action, int* nbBoost);
  *\brief Permet de calculer le meilleur chemin
  *\param Le pilote
  *\param La carte
  *\param La position de départ
  *\param La vitesse de départ
  *\param Le tableau d'action qui sera rempli
  *\param Le nombre de boosts
  *\return le nombre d'accélérations à faire
  */
int shortCutF(Circuit pilote,Carte carte, Position depart,Vitesse vDepart, Action *action, int* nbBoost);


/**
  *\fn int retrouverChemin(Pile *pileBackUp,Action *action,int gen,int taille);
  *\brief Permet de retourner le chemin dans le bon ordre
  *\param La pile sera mise dans l'ordre
  *\param Le tableau qui sera rempli
  *\param Le numéro de la dernière génération de cellule
  *\param La taille du tableau
  *\return la taille du tableau
  */
int retrouverChemin(Pile *pileBackUp,Action *action,int gen,int taille);


/**
  *\fn int isArrived(Position *posArrived,short *alreadyArrived,int **map,Position pilot1,Position pilot2,int taille);
  *\brief Permet de savoir si une voiture est arrivée à l'arrivée et de prévenir le pilote qu'il devra recalculer le chemin possible
  *\param Un tableau contenant toutes les différentes arrivées 
  *\param un tableau qui dit si on a déjà été prévenu
  *\param la carte
  *\param La position du pilote 1
  *\param La position du pilote 2
  *\param La taille du tableau d'arrivées
  *\return 1 si une nouvelle arrivée est détectée
  */

int isArrived(Position *posArrived,short *alreadyArrived,int **map,Position pilot1,Position pilot2,int taille);
/**
  *\fn void destruction(char ****tab,int tx,int ty);
  *\brief Permet de détruire un tableau de ***char
  *\param Le tableau à détruire
  *\param La taille du tableau en x
  *\param La taille du tableau en y
  *\return void
  */
void destruction(char ****tab,int tx,int ty);
/**
  *\fn char opti(Vitesse v)
  *\brief Fonction d'optimisation qui permet de regrouper deux char dans le même char (Non utilisée)
  *\param Vitesse
  *\return le char contenant deux valeurs
  */
char opti(Vitesse v);
/**
  *\fn int isPossible(Position current,Vitesse vCurrent, Carte *carte,int boost);
  *\brief Permet de savoir si le calcul de parcours est possible
  *\param La position courante
  *\param La vitesse courante
  *\param La carte
  *\param 1 si on utilise un boost, ou 0 sinon
  *\return 1 si possible, 0 sinon
  */
int isPossible(Position current,Vitesse vCurrent, Carte *carte,int boost);

#endif
