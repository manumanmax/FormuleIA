#ifndef FONCTION_H
#define FONCTION_H
#define MAX 100
#define INFINITY 1000
#define SABLE 4
#define ROUTE 2
#define ARRIVE 1
#define PORTE 3
#define DEPART 0

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Liste/listeA.h"
#include "pile/pile.h"
#include "struct.h"


typedef struct _Circuit
{
	short tab[100*100];
	short map[MAX][MAX];
	Vitesse mapD[MAX][MAX];
	short tx;
	short ty;
	short taille;
	Action action;
	Position positionCourante;
	Position arrivee;
	Position depart;
	ListeA *la;
	Position *shortPath;
	int tailleChemin;
	Vitesse *vPossible;

}Circuit;

void poidsDistance(Circuit *pilote);
void circuitCopie(short from[][MAX], short to[][MAX]);
ListeA *creerListeA(Circuit pilote);

/*Utilisé pour rapidité, principalement pour faire la listeA, seul probleme tres peu sécurisé*/
int positionG(Circuit pilote, int pos);
int positionD(Circuit pilote, int pos);
int positionH(Circuit pilote, int pos);
int positionB(Circuit pilote, int pos);
int positionHG(Circuit pilote, int pos);
int positionHD(Circuit pilote, int pos);
int positionBG(Circuit pilote, int pos);
int positionBD(Circuit pilote, int pos);

Position position_haut(Position pos,int tailley);
Position position_droite(Position pos,int taillex);
Position position_bas(Position pos,int tailley);
Position position_gauche(Position pos,int taillex);
Position position_hautGauche(Position pos,int taillex,int tailley);
Position position_hautDroite(Position pos,int taillex,int tailley);
Position position_basGauche(Position pos,int taillex,int tailley);
Position position_basDroite(Position pos,int taillex,int tailley);
int testPosition(Position pos);

void positionAutour(Position current, Circuit pilote);
void autourPosition(Position current,Vitesse vit,int taillex,int tailley,short map[][MAX],int boost, Position autour[6][6],int valeur[6][6]);
int shortCut(Circuit pilote, Action action[200]);
Vitesse *vitessePossibles(Position *shortP, int taille);
void direction(Vitesse mapD[][MAX],short map[][MAX],Position *shortP,Vitesse *vPos,int taille,int taillex,int tailley);
void perpendiculaire(int tab[],Vitesse pos);
int samePos(Position *shortP,Position current,int taille);
int verifD(Vitesse current,Vitesse mapD[][MAX],Position pos,int taillex,int tailley);
int isJumping(Vitesse vCurrent,Position current,short map[MAX][MAX]);


#endif
