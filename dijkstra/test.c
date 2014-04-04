#define POSITION 0
#define POIDS 1
#define PARCOURU 2
#define	INFILE 3
#define ANTECEDANT 1
#define T_CIRCUIT1 80



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../rechercheAlgo/fonction.h"
#include "../rechercheAlgo/listeA.h"
#include "../TP1/include/file.h"


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
int in(int i, int parcours[200]){

	for(int j = 0; j < 200; j++){
		if(parcours[j] == i)
			return 1;
	}


	return 0;
}

void afficheParcours(int parcours[200],Circuit circuit){

	for(int i = 0; i < circuit.taille; i++){
		if(i%circuit.tx == 0)
			puts("");
		if(in(i,parcours)){
			printf("x");
		}
		else{if(circuit.tab[i]==1000){ printf(".");continue;}

			printf("%d",circuit.tab[i]);
		}
	}
	puts("");
	return;
}


int main(int argc, char** argv){
	clock_t start,stop;
	double time;

	Circuit pilote;
	FILE *info = fopen("circuit1","r");
	char c;
	fscanf(info," %hd %hd",&pilote.tx,&pilote.ty);
	pilote.taille =pilote.tx*pilote.ty;

	for(int i=0; i < pilote.ty; i++){
		for(int j = 0; j <pilote.tx; j++) {
			c=getc(info);
			if(c=='\n')
				c=getc(info);
			pilote.tab[i*pilote.tx +j]=c;
			pilote.map[i][j]=c;
		}
	}

	poidsDistance(&pilote);
	
	int depart = pilote.depart.y*pilote.tx + pilote.depart.x;
	int arrive = pilote.arrivee.y*pilote.tx + pilote.arrivee.x;
	start = clock();
	pilote.la = creerListeA(pilote);
	//affichage(pilote.la);
	printf(" depart %d, arrive %d, taille %d\n",depart, arrive,pilote.la->taille);

	//initialisation des tableaux
	int tabPoids[pilote.la->taille][4];
	int tabAntecedents[pilote.la->taille][2];

	rempliTabs(pilote.la,tabPoids,tabAntecedents);


	//****************************** debut de l'algorithme ***************************

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

	//puts("");
	int tab[200];
	memset(tab,-1,200);
	int pos = arrive, i = 0; 

	if(tabPoids[arrive][POIDS] != -1){
		while(pos != depart){
			tab[i] = pos;
			pos = tabAntecedents[pos][ANTECEDANT]; 
			i++;
		}
	}
	//Taille Chemin à garder 
	int tailleChemin=i;
/*Inversion position */
	for(int i=0; i<tailleChemin/2;i++){
		int tmp=tab[i];
		tab[i]=tab[tailleChemin-i];
		tab[tailleChemin-i]=tmp;

	}
	printf(" Taille Chemin %d ", tailleChemin);
	for(int i=0; i < tailleChemin;i++)
		printf("%d\n",tab[i]);

	stop = clock();

	time = (double) (stop-start);
	afficheParcours(tab,pilote);
	printf("%f\n",time/CLOCKS_PER_SEC);

	return EXIT_SUCCESS;
}
