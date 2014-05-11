#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "../include/struct.h"
#include "../include/fonction.h"

int calculBecauseCollision(Circuit pilote,Carte map,Position current,Vitesse vCurrent,Action *action1,Position pilote1,int *posTab);
void displayMap(Carte map,FILE *f);
void displayAction(Action *action,FILE *f,int taille);

#endif
