#include "fonction.h"


int main(void)
{
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
		//	printf(" %d ", pilote.tab[i*pilote.tx+j]);
		//	printf(" &%d %d %d& ", i*pilote.tx+j,i,j);
		}
	}
/*	puts(" ");
	for(int i =0;i < pilote.taille; i++){
		printf(" %d ",pilote.tab[i]);
	}*/

	poidsDistance(&pilote);
	pilote.la = creerListeA(pilote);
	int depart = pilote.depart.y*pilote.tx + pilote.depart.x;
	int arrive = pilote.arrivee.y*pilote.tx + pilote.arrivee.x;

	printf(" depart %d, arrive %d",depart, arrive);
//	affichage(pilote.la);
	int poids;
//	for(int i =0; i < 500; i++)
//		pilote.shortPath[i]=0;
//	dijkstra(pilote,pilote.shortPath);




	return EXIT_SUCCESS;
}
