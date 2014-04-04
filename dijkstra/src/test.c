#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../rechercheAlgo/fonction.h"
#include "../../rechercheAlgo/listeA.h"
#include "../../TP1/include/file.h"
#include "../include/dijkstra.h"




int main(int argc, char** argv){

	Circuit pilote;

	int pv1x, pv1y;
	int pv3x, pv3y;
	FILE *info = fopen("test.log","w");
	char c;
	fscanf(stdin,"%hd %hd",&pilote.tx,&pilote.ty);

	fprintf(info,"taille %d x %d\n\n", pilote.tx, pilote.ty);
	pilote.taille =pilote.tx*pilote.ty;

	for(int i=0; i < pilote.ty; i++){
		for(int j = 0; j <pilote.tx; j++) {
			c=getc(stdin);
			if(c=='\n')
				c=getc(stdin);
			pilote.tab[i*pilote.tx +j]=c;
			pilote.map[i][j]=c;
		}
	}
	fflush(stdin);

	for(int i = 0; i < pilote.ty; i++){
		for(int j = 0; j < pilote.tx; j++){
			fprintf(info, "%c", pilote.map[i][j]);
		}
		fprintf(info, "\n");
	}



	fflush(info);
	fprintf(info,"\n === Debut Course === \n");

	fflush(info);
	int px;
	int py;
	int flagPosDepartSet = 1;
	//fscanf(stdin,"%d %d\n",&px,&py);
	fscanf(stdin,"%d %d\t%d %d\t%d %d",&px, &py, &pv1x, &pv1y, &pv3x, &pv3y);
fflush(stdin);
	fprintf(info,"position de depart : %d %d\n", px, py);	
	pilote.depart.x = px;
	pilote.depart.y = py;

	pilote.map[pilote.depart.y][pilote.depart.x]=0;
	poidsDistance(&pilote);

	fprintf(info,"Tableau des poids :\n");	
	for(int i = 0; i < pilote.ty; i++){
		for(int j = 0; j < pilote.tx; j++){
			if(pilote.map[i][j] == 1000) fprintf(info,".");
			else fprintf(info,"%d",pilote.map[i][j]);
		}
		fprintf(info,"\n");
	}
	fprintf(info,"--------------------------------\n");	
	fflush(info);
	int depart = pilote.depart.y*pilote.tx + pilote.depart.x;
	int arrive = pilote.arrivee.y*pilote.tx + pilote.arrivee.x;
	pilote.la = creerListeA(pilote);
	//	affichage(pilote.la);
	//	printf(" %d %d\n",pilote.arrivee.x,pilote.arrivee.y);
	//	printf(" depart %d, arrive %d\n",depart, arrive);

	//initialisation des tableaux
	int tabPoids[pilote.la->taille][4];
	int tabAntecedents[pilote.la->taille][2];

	rempliTabs(pilote.la,tabPoids,tabAntecedents);


	pilote.shortPath=dijkstra(tabPoids,tabAntecedents,pilote,depart,arrive,&pilote.tailleChemin);
	fprintf(info, "------------ DIJKSTRA -----------\n");
	afficheParcoursInfo(pilote.shortPath,pilote,info);
	fprintf(info, "-----------------------\n");
	//	printf(" %d ",pilote.tailleChemin);
	pilote.vPossible=vitessePossibles(pilote.shortPath,pilote.tailleChemin);

	direction(pilote.mapD,pilote.map,pilote.shortPath,pilote.vPossible,pilote.tailleChemin,pilote.tx,pilote.ty);

	/*	for(int i=0;i<pilote.ty;i++){
		for(int j=0;j<pilote.tx;j++){
		if(pilote.mapD[i][j].vx==0 && pilote.mapD[i][j].vy==0)
		printf("0");

		else printf("x",pilote.mapD[i][j].vy);
		}
		puts(" ");

		}*/
	Action action1[200];
	int taille = shortCut(pilote,action1);
	for(int i = 0; i < taille+1; i++){
		fprintf(info,"%d %d\n", action1[i].vx, action1[i].vy); 
	}

	int tour = 0;
	int posTab = 0;
	Position suivante;
	Vitesse vCourante;
	vCourante.vx = 0;
	vCourante.vy = 0;

	char action[14]=""; 

	while(!feof(stdin)){
		tour++;

		fprintf(info,"\n === Tour %d === \n", tour);
		//Lecture des positions.
		if(!flagPosDepartSet){
			fscanf(stdin,"%d %d\t%d %d\t%d %d",&px, &py, &pv1x, &pv1y, &pv3x, &pv3y);
			fflush(stdin);
		}else{
			flagPosDepartSet = 0;
		}
		//while(getchar() != '\n');	
		fprintf(info,"position recuperees : %d %d\t%d %d\t%d %d\n",px, py, pv1x, pv1y, pv3x, pv3y);
		fflush(info);
		//on positionne les concurrents en murs
		suivante.x = px + action1[posTab].vx + vCourante.vx;
		suivante.y = py + action1[posTab].vy + vCourante.vy;

		/*	if((suivante.x == pv1x && suivante.y == pv1y)
			|| (suivante.x == pv3x && suivante.y == pv3y)){
			fprintf(info, "---------RECALCUL------------");
			pilote.map[pv1y][pv1x] = 1000;
			pilote.map[pv3y][pv3x] = 1000;
			pilote.shortPath=dijkstra(tabPoids,tabAntecedents,pilote,py*pilote.tx+px,arrive,&pilote.tailleChemin);
			pilote.vPossible=vitessePossibles(pilote.shortPath,pilote.tailleChemin);

			direction(pilote.mapD,pilote.map,pilote.shortPath,pilote.vPossible,pilote.tailleChemin,pilote.tx,pilote.ty);
			taille = shortCut(pilote,action1);
			posTab = 0;
			pilote.map[pv1y][pv1x] = ROUTE;
			pilote.map[pv3y][pv3x] = ROUTE;
			}*/

		fprintf(info,"\n === Action === \n");
		//Écriture synchrone de l'accélération.
		fflush(stdout);
		printf("%d %d\n",action1[posTab].vx,action1[posTab].vy);
		fflush(stdout);
		vCourante.vx += action1[posTab].vx;
		vCourante.vy += action1[posTab].vy;
		fprintf(info, "%s", action);
		fflush(info);

		posTab++;
	}

	/*for(int i=0;i<taille;i++){
	  fprintf(info,"%d %d\n", action1[i].vx,action1[i].vy);
	  fprintf(stdout, "%d %d\n", action1[i].vx,action1[i].vy);
	  }*/

	return EXIT_SUCCESS;
}
