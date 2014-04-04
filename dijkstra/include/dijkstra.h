#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#define POSITION 0
#define POIDS 1
#define PARCOURU 2
#define	INFILE 3
#define ANTECEDANT 1
#define T_CIRCUIT1 32
#define PATHCIRCUIT ../circuits/
#define SIZE_TAB_PARCOURS 200

void rempliTabs(ListeA* liste, int tabPoids[][4], int tabAntecedents[][2]);
int fin(int **tab, int taille, int arrivee);
int recherchePetitPoids(Noeud* courant, int tabPoids[][4]);
void enfileSommets(File* f, Noeud* courant,int poids,int tabPoids[][4]);
void decouverte(Noeud* courant, Noeud* pere,int tabPoids[][4], int tabAntecedents[][2]);
void afficheTabPoids(int tabPoids[][4], Circuit* pilote);
int in(int i, int parcours[SIZE_TAB_PARCOURS]);
void afficheParcours(Position *shortP,Circuit circuit);
void afficheParcoursInfo(Position *shortP,Circuit circuit,FILE* info);
Position *dijkstra( int tabPoids[][4], int tabAntecedents[][2], Circuit pilote, int depart, int arrive,int *taille);
#endif
