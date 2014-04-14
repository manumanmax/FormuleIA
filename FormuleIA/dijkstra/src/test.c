#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../rechercheAlgo/fonction.h"
#include "../../TP1/include/file.h"




int main(int argc, char** argv){

	Circuit pilote;
	Carte carte;

	int pv1x, pv1y;
	int pv3x, pv3y;
	FILE *info = fopen("testlog.log","w");
	Position *posArrived=malloc(sizeof(Position)*20);
	short *alreadyArrived=malloc(sizeof(int)*20);
	short nombreArrivees=0;
	char c;
	fscanf(stdin,"%hd %hd",&carte.tx,&carte.ty);

	fprintf(info,"taille %d x %d\n\n", carte.tx, carte.ty);
	int **tab=(int **)malloc(sizeof(int *)*MAX);
	for(int i=0;i<MAX;i++)
		tab[i]=malloc(sizeof(int)*MAX);

	carte.map=tab;

	for(int i=0; i < carte.ty; i++){
		for(int j = 0; j <carte.tx; j++) {
			c=getc(stdin);
			if(c=='\n')
				c=getc(stdin);

			if(c=='~')
				carte.map[i][j]='.';

			else  {
				carte.map[i][j]=c;
				if(c=='='){
					alreadyArrived[nombreArrivees]=0;
					posArrived[nombreArrivees].x=j;
					posArrived[nombreArrivees].y=i;

					nombreArrivees++;
				}
			}

		}
	}
	fflush(stdin);

	for(int i = 0; i < carte.ty; i++){
		for(int j = 0; j < carte.tx; j++){
			fprintf(info, "%c", carte.map[i][j]);
		}
		fprintf(info, "\n");
	}

	fprintf(info,"NA %d",nombreArrivees);


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

	carte.map[pilote.depart.y][pilote.depart.x]=0;
	//poidsDistance(&pilote);


	fprintf(info,"--------------------------------\n");	
	fflush(info);

	Position pilot1;
	Position pilot2;


	Action action1[300];
	Vitesse vDepart;
	vDepart.vx=0;
	vDepart.vy=0;
	int taille = shortCutF(pilote,carte,pilote.depart,vDepart,action1);
	for(int i = 0; i < taille; i++){
		fprintf(info,"%d %d\n", action1[i].vx, action1[i].vy); 
	}

	int tour = 0;
	int posTab = 0;
	Position suivante;
	Vitesse vCourante;
	vCourante.vx = 0;
	vCourante.vy = 0;


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

		pilot1.x=pv1x;
		pilot1.y=pv1y;

		pilot2.x=pv3x;
		pilot2.y=pv3y;
		Position current;
		current.x=px;
		current.y=py;

		if((suivante.x == pv1x && suivante.y == pv1y)
				|| (suivante.x == pv3x && suivante.y == pv3y)){
			fprintf(info, "---------RECALCUL------------");
			carte.map[pv1y][pv1x] = '.';
			carte.map[pv3y][pv3x] = '.';
			taille = shortCutF(pilote,carte,current,vCourante,action1);
			for(int i = 0; i < taille; i++){
				fprintf(info,"%d %d\n", action1[i].vx, action1[i].vy); 
			}
			if(taille!=0)
			posTab = 0;
			carte.map[pv1y][pv1x] = '#';
			carte.map[pv3y][pv3x] = '#';
		}

		if(isArrived(posArrived,alreadyArrived,carte.map,pilot1,pilot2,nombreArrivees)){
			fprintf(info, "---------Calcul car arrivée bouchée------------");

			taille = shortCutF(pilote,carte,current,vCourante,action1);
			if(taille!=0)
			posTab = 0;
			for(int i=0;i<nombreArrivees;i++){
				fprintf(info,"%d %d\n", action1[i].vx, action1[i].vy); 

			}

		}

		fprintf(info,"\n === Action === \n");
		//Écriture synchrone de l'accélération.
		fflush(stdout);
		printf("%d %d\n",action1[posTab].vx,action1[posTab].vy);
		fflush(stdout);
		vCourante.vx += action1[posTab].vx;
		vCourante.vy += action1[posTab].vy;
		fprintf(info, "%d %d", action1[posTab].vx,action1[posTab].vy);
		fflush(info);

		posTab++;
	}



	return EXIT_SUCCESS;
}
