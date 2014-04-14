#include <stdlib.h>
#include <stdio.h>
#include "listeA.h"



ListeA *creerListe(int taille)
{
	ListeA *l=malloc(sizeof(ListeA));
	l->tab = (Noeud**)malloc(sizeof(Noeud*)*taille);
	l->taille = taille;

	for(int i =0; i < l->taille; i++)
		l->tab[i] = NULL;

	return l;
}

Liste *creerL()
{
	Liste *l = malloc(sizeof(Liste));
	l->courant = NULL;
	l->head = NULL;
	l->taille = 0;

	return l;
}

int vide(Noeud *n)
{
	if(n == NULL)
		return 1;

	return 0;
}


void ajouter(ListeA *l, int pos,int pos2, int poids)
{
	if(l->taille <= pos)
		return;

	Noeud *n = malloc(sizeof(Noeud));
	n->position = pos2;
	n->poids = poids;
	if(l->tab[pos] == NULL) {
		Liste *li =	creerL();
		li->head = l->tab[pos];
		l->tab[pos] = n;
		n->suivant = NULL;

		return;
	}
	n->suivant = l->tab[pos]->suivant;
	l->tab[pos]->suivant =n;



}



void affichage(ListeA *l)
{
	for(int i = 0; i < l->taille ; i++)
	{
		if(vide(l->tab[i])) continue;
		Noeud *tmp = l->tab[i];
		printf("%d",i);
		while(tmp!=NULL)
		{
			printf("->(%d & %d)",tmp->poids,tmp->position);
			tmp= tmp->suivant;
		}
		puts("->NULL");
	}

}
