#ifndef LISTEA_H
#define LISTEA_H

typedef struct _Noeud
{
	struct _Noeud *suivant;
	int position;
	int poids;

}Noeud;

typedef struct _Liste
{
	Noeud *courant;
	Noeud *head;
	int taille;

}Liste;

typedef struct _ListeA
{
Noeud **tab;
int taille;

}ListeA;

ListeA *creerListe(int taille);
Liste *creerL();
void ajouter(ListeA *l, int pos, int pos2, int poids);
int vide(Noeud *n);
void affichage(ListeA *l);


#endif
