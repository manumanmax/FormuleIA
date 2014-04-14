#ifndef LISTEA_H
#define LISTEA_H

typedef struct _Noeud
{
	struct _Noeud *suivant;
	int position;
	int poids;

}Noeud;

typedef struct
{
	Noeud *courant;
	int taille;

}Liste;

struct _ListeA
{
	Noeud *tab;
	int taille;

};

ListeA* creerListe(int taille);

#endif
