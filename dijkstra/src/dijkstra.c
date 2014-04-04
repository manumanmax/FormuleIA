#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../rechercheAlgo/fonction.h"
#include "../../rechercheAlgo/listeA.h"
#include "../../TP1/include/file.h"
#include "../include/dijkstra.h"



void rempliTabs(ListeA* liste, int tabPoids[][4], int tabAntecedents[][2]){
	/*int** tabPoids = malloc(liste->taille*sizeof(int*));
	  for(int i =0; i < liste->taille; i++){
	  tabPoids[i] = malloc(3*sizeof(int));

	  }*/
	  for(int i = 0; i < liste->taille; i++){
		if(vide(liste->tab[i])){
			tabPoids[i][POSITION] = -1;		
			tabPoids[i][POIDS] = -1;		
			tabPoids[i][PARCOURU] = 0;		// visite ou non (0/1)
			tabPoids[i][INFILE] = 0;
			tabAntecedents[i][POSITION] = -1; 
			tabAntecedents[i][ANTECEDANT] = -1; 

			continue;
		}
		tabPoids[i][POSITION] = i;		// numero du sommet
		tabPoids[i][POIDS] = -1;		// poids courant (initialisé à -1 sauf pour le point de depart)
		tabPoids[i][PARCOURU] = 0;		// visite ou non (0/1)
		tabPoids[i][INFILE] = 0;
		tabAntecedents[i][POSITION] = i;// rempli le tableau des antecedents avec les numeros des sommets
		tabAntecedents[i][ANTECEDANT] = -1;		// on met tous les antecedents à -1
	}

	return ;
}


int fin(int **tab, int taille, int arrivee){
	
	if(tab[arrivee][POIDS] == -1) return 0;
	for(int i = 0; i < taille; i++){
		if(tab[i][POIDS] == -1) continue;
		if(tab[i][POIDS] < tab[arrivee][POIDS]){
			//printf("%d < %d \n",tab[i][POIDS], tab[arrivee][POIDS]);
			return 0;	

		}
	}
	return 1;
}


int recherchePetitPoids(Noeud* courant, int tabPoids[][4]){
	int poids = 10000;
	while(courant->suivant != NULL){
		//printf("%d->",courant->suivant->position);
		/*	printf("poids inferieur : %d\npoids != -1 : %d\ninfile : %d\n",tabPoids[courant->suivant->position][POIDS] < poids
			,tabPoids[courant->suivant->position][POIDS] != -1
			,!tabPoids[courant->suivant->position][INFILE]);*/
		if(tabPoids[courant->suivant->position][POIDS] < poids
				&& tabPoids[courant->suivant->position][POIDS] != -1
				&& !tabPoids[courant->suivant->position][INFILE]) // on cherche le plus petit poids des sommets adjacents non enfilés
			poids = tabPoids[courant->suivant->position][POIDS];

		courant = courant->suivant;	
	}
	//puts("");
	//printf("petit poids : %d\n",poids);
	return poids;
}


void enfileSommets(File* f, Noeud* courant,int poids,int tabPoids[][4]){ //TODO: verifier si le sommet a deja ete parcouru
	if(poids != 10000){
		while(courant->suivant != NULL){
			//printf("sommet %d de poids %d : %d %d %d\n",courant->suivant->position, tabPoids[courant->suivant->position][POIDS], courant->suivant->poids == poids, !tabPoids[courant->suivant->position][PARCOURU], !tabPoids[courant->suivant->position][INFILE]);
			if(tabPoids[courant->suivant->position][POIDS] == poids && !tabPoids[courant->suivant->position][PARCOURU]
					&& !tabPoids[courant->suivant->position][INFILE]){
				enfiler(courant->suivant->position,f);
				tabPoids[courant->suivant->position][INFILE] = 1;
				//printf("sommet %d enfilé\n",courant->suivant->position);
			}
			courant = courant->suivant;	
		}
	}
}


void decouverte(Noeud* courant, Noeud* pere,int tabPoids[][4], int tabAntecedents[][2]){

	tabPoids[pere->position][PARCOURU] = 1; 
	while(courant->suivant != NULL){ // reinitialiser au suivant avec la->tab ! Normalement regle avec le noeud pere
		if(!tabPoids[courant->suivant->position][PARCOURU]){
			if(tabPoids[courant->suivant->position][POIDS] != -1){
				if(((tabPoids[pere->position][POIDS] + courant->suivant->poids) < tabPoids[courant->suivant->position][POIDS])){
					// si la somme des poids est inferieur au poids du noeud suivant alors le chemin le plus court change
					//printf("poids du pere : %d\n", tabPoids[pere->position][POIDS]);
					tabPoids[courant->suivant->position][POIDS] = tabPoids[pere->position][POIDS] + courant->suivant->poids;
					tabAntecedents[courant->suivant->position][1] = pere->position;
					//printf("tabPoids[%d][%d] = %d\n",courant->suivant->position,POIDS,tabPoids[courant->suivant->position][POIDS]);
				}
			}
			else{

				tabPoids[courant->suivant->position][POIDS] = tabPoids[pere->position][POIDS] + courant->suivant->poids;
				tabAntecedents[courant->suivant->position][1] = pere->position;

				//printf("nouveau poids de %d : %d\n",courant->suivant->position,tabPoids[courant->suivant->position][POIDS]);
			}
		}
		courant = courant->suivant;
	}
}


void afficheTabPoids(int tabPoids[][4], Circuit* pilote){
	for(int i = 0; i < pilote->la->taille; i++){
		if(tabPoids[i][POSITION] != -1){
			printf("%d : poids %d parcouru %d enfile %d\n",tabPoids[i][POSITION],tabPoids[i][POIDS],tabPoids[i][PARCOURU],tabPoids[i][INFILE]);
		}
	}

	return;
}


int in(int i, int parcours[SIZE_TAB_PARCOURS]){

	for(int j = 0; j < SIZE_TAB_PARCOURS; j++){
		if(parcours[j] == i)
			return 1;
	}


	return 0;
}


void afficheParcours(Position *shortP,Circuit circuit){
	int k=0;
	int flag=0;
	for(int i=0;i<circuit.ty;i++){
		for(int j=0; j<circuit.tx;j++){
			flag=0;
			for(k=0;k<circuit.tailleChemin;k++){
				if(shortP[k].x==j && shortP[k].y==i) {
					printf(" ");
					flag=1;
					break;
				}
				
			}
			if(flag) continue;

			if(circuit.map[i][j]==1000) {printf(".");continue;}
			printf("%d",circuit.map[i][j]);

		}
		puts(" ");

	}
}

void afficheParcoursInfo(Position *shortP,Circuit circuit,FILE* info){
	int k=0;
	int flag=0;
	for(int i=0;i<circuit.ty;i++){
		for(int j=0; j<circuit.tx;j++){
			flag=0;
			for(k=0;k<circuit.tailleChemin;k++){
				if(shortP[k].x==j && shortP[k].y==i) {
					fprintf(info," ");
					flag=1;
					break;
				}
				
			}
			if(flag) continue;

			if(circuit.map[i][j]==1000) {fprintf(info,".");continue;}
			fprintf(info,"%d",circuit.map[i][j]);

		}
		fprintf(info,"\n");
	}
}
Position *dijkstra(int tabPoids[][4], int tabAntecedents[][2], Circuit pilote, int depart, int arrive,int *taille){

	//****************************** debut de l'algorithme ***************************
	int tab[SIZE_TAB_PARCOURS];
	File* f = creerFile();
	Noeud* courant = malloc(sizeof(Noeud));
	Noeud* pere = malloc(sizeof(Noeud));
	tabPoids[depart][POIDS] = 0; //depart parcouru

	pere = pilote.la->tab[depart];

	int sommet;
	int poids;

	courant = pere;
	decouverte(courant, pere, tabPoids, tabAntecedents);
	poids = recherchePetitPoids(courant,tabPoids);
	courant = pere;

	enfileSommets(f,courant,poids, tabPoids);

	while((sommet = defiler(f)) != -1){

		pere = pilote.la->tab[sommet]; 	
		courant = pere;
		decouverte(courant,pere,tabPoids,tabAntecedents);
		courant = pere;
		poids = recherchePetitPoids(courant,tabPoids);
		courant = pere;
		enfileSommets(f,courant,poids,tabPoids);
	}


	memset(tab,-1,SIZE_TAB_PARCOURS);
	int pos = arrive, i = 0; 

	if(tabPoids[arrive][POIDS] != -1)
		while(pos != depart){
			tab[i] = pos;
			pos = tabAntecedents[pos][ANTECEDANT]; 
			i++;
		}
	int tailleChemin=i;
	*taille=i;
	Position *shortP=malloc(sizeof(Position)*tailleChemin);

	/*Inversion position */
	for(int i=0; i<tailleChemin/2;i++){
		int tmp=tab[i];
		tab[i]=tab[tailleChemin-i-1];
		tab[tailleChemin-i-1]=tmp;

	}
	for (int i = 0; i < tailleChemin ; i++) {

		shortP[i].x=tab[i]%pilote.tx;
		shortP[i].y=tab[i]/pilote.tx;
		
	}

	return shortP;

}

