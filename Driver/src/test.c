#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/fonction.h"




int main(int argc, char** argv){

	Circuit pilote;
	Carte carte;
	int nbBoost = NBBOOST;
	
	FILE *info = fopen("log.txt","w");
	fprintf(info,"nbBoost main : %d\n", nbBoost);
	fflush(info);
	fclose(info);
	Position *posArrived=malloc(sizeof(Position)*20);
	short *alreadyArrived=malloc(sizeof(int)*20);
	short nombreArrivees=0;
	char c;
	fscanf(stdin,"%hd %hd",&carte.tx,&carte.ty);

	//fprintf(info,"taille %d x %d\n\n", carte.tx, carte.ty);
	int **tab=(int **)malloc(sizeof(int *)*carte.ty);
	for(int i=0;i<carte.ty;i++)
		tab[i]=malloc(sizeof(int)*carte.tx);

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
			//fprintf(info, "%c", carte.map[i][j]);
		}
		//fprintf(info, "\n");
	}



	//fflush(info);
	//fprintf(info,"\n === Debut Course === \n");

	//fflush(info);
	int px;
	int py;
	int pv1x, pv1y;
	int pv3x, pv3y;

	int flagPosDepartSet = 1;
	//fscanf(stdin,"%d %d\n",&px,&py);
	fscanf(stdin,"%d %d\t%d %d\t%d %d",&px, &py, &pv1x, &pv1y, &pv3x, &pv3y);
	fflush(stdin);
	//fprintf(info,"position de depart : %d %d\n", px, py);	
	pilote.depart.x = px;
	pilote.depart.y = py;

	carte.map[pilote.depart.y][pilote.depart.x]=0;
	//poidsDistance(&pilote);


	//fprintf(info,"--------------------------------\n");	
	//fflush(info);

	Position pilot1;
	Position pilot2;


	Action *action1=malloc(sizeof(Action)*200);
	Vitesse vDepart;
	vDepart.vx=0;
	vDepart.vy=0;
	int taille = shortCutF(pilote,carte,pilote.depart,vDepart,action1,&nbBoost);
		//fprintf(info,"\n--------\n"); 
		//fprintf(info,"---tableau d'actions\n--------"); 
	for(int i = 0; i < taille; i++){
		//fprintf(info,"%d %d\n", action1[i].vx, action1[i].vy); 
	}

	int tour = 0;
	int posTab = 0;
	Position suivante;
	Vitesse vCourante;
	vCourante.vx = 0;
	vCourante.vy = 0;
	int blockedBy1=0;
	int blockedBy2=0;
	Position preced;
	preced.x=px;
	preced.y=py;
	Position s;
	s.x=0;
	s.y=0;
	Vitesse vVerif;
	vVerif.vx=0;
	vVerif.vy=0;
	int arrived=0;


	while(!feof(stdin)){
		tour++;
		int testS=0;
		blockedBy1=0;
		blockedBy2=0;
		preced.x=px;
		preced.y=py;
		//fprintf(info,"\n === Tour %d === \n", tour);
		//Lecture des positions.
		if(!flagPosDepartSet){
			fscanf(stdin,"%d %d\t%d %d\t%d %d",&px, &py, &pv1x, &pv1y, &pv3x, &pv3y);
			//fprintf(info,"fscanf %d\n",testS);
			//fflush(stdin);
		}else{
			flagPosDepartSet = 0;
		}
		//while(getchar() != '\n');	
		//fprintf(info,"position recuperees : %d %d\t%d %d\t%d %d\n",px, py, pv1x, pv1y, pv3x, pv3y);

		s.x=px;
		s.y=py;

		vCourante.vx=s.x-preced.x;
		vCourante.vy=s.y-preced.y;


		//fflush(info);
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
		if(((taille==0 
			|| posTab>=taille 
			|| (vVerif.vx!=vCourante.vx && vVerif.vy!=vCourante.vy))
			&& (isPossible(current,vCourante,&carte,0))) 
			|| (vCourante.vx==0 && vCourante.vy==0)) 
		{

			//fprintf(info,"yop\n");
			taille=shortCutF(pilote,carte,current,vCourante,action1,&nbBoost);
			posTab=0;

			for(int i = 0; i < taille; i++){
				//fprintf(info,"%d %d\n", action1[i].vx, action1[i].vy); 
			}
			vVerif=vCourante;

		}


		if(((suivante.x == pv3x && suivante.y == pv3y)
					&& (suivante.x == pv1x && suivante.y == pv1y)) && isPossible(current,vCourante,&carte,0)){
			//fprintf(info, "---------RECALCUL3------------\n");
			carte.map[pv3y][pv3x] = '.';
			carte.map[pv1y][pv1x] = '.';


			taille = shortCutF(pilote,carte,current,vCourante,action1,&nbBoost);
			for(int i = 0; i < taille; i++){
				//fprintf(info,"%d %d\n", action1[i].vx, action1[i].vy); 
			}
			carte.map[pv3y][pv3x] = '#';
			carte.map[pv1y][pv1x] = '#';
			posTab=0;

			//fprintf(info,"taille %d\n",taille);


			blockedBy1=1;
			blockedBy2=1;

		}

		if(suivante.x == pv1x && suivante.y == pv1y && isPossible(current,vCourante,&carte,0) && !blockedBy1){
			//fprintf(info, "---------RECALCUL1------------\n");
			carte.map[pv1y][pv1x] = '.';
			taille = shortCutF(pilote,carte,current,vCourante,action1, &nbBoost);
			for(int i = 0; i < taille; i++){
				//fprintf(info,"%d %d\n", action1[i].vx, action1[i].vy); 
			}
			carte.map[pv1y][pv1x] = '#';
			blockedBy1=1;
			posTab=0;

		}
		if(suivante.x == pv3x && suivante.y == pv3y && isPossible(current,vCourante,&carte,0) && !blockedBy1){
			//fprintf(info, "---------RECALCUL2------------\n");
			carte.map[pv3y][pv3x] = '.';
			taille = shortCutF(pilote,carte,current,vCourante,action1, &nbBoost);
			for(int i = 0; i < taille; i++){
				//fprintf(info,"%d %d\n", action1[i].vx, action1[i].vy); 
			}
			carte.map[pv3y][pv3x] = '#';
			blockedBy2=1;
			//fprintf(info,"taille %d\n",taille);
			posTab=0;
		}

		//fprintf(info,"Vitesse %d %d\n",vCourante.vx,vCourante.vy);

		if(arrived==0)
			arrived =isArrived(posArrived,alreadyArrived,carte.map,pilot1,pilot2,nombreArrivees);

		if(arrived  && isPossible(current,vCourante,&carte,0)){
			//fprintf(info, "---------Calcul car arrivée bouchée------------");

			taille = shortCutF(pilote,carte,current,vCourante,action1, &nbBoost);
			//fprintf(info,"taille %d\n",taille);

			for(int i=0;i<taille;i++){
				//fprintf(info,"%d %d\n", action1[i].vx, action1[i].vy); 

			}
			posTab=0;
			vVerif=vCourante;
			arrived=0;

		}
		//fprintf(info,"taille %d\n",taille);


		//fprintf(info,"\n === Action === \n");
		//Écriture synchrone de l'accélération.
		//	fflush(stdout);
		printf("%d %d\n",action1[posTab].vx,action1[posTab].vy);
		fflush(stdout);
		vVerif.vx += action1[posTab].vx;
		vVerif.vy += action1[posTab].vy;
		//fprintf(info, "%d %d", action1[posTab].vx,action1[posTab].vy);
		//fflush(info);
		//fprintf(info,"posTab %d\n",posTab);
		posTab++;
	}

	//	fclose(info);



	return EXIT_SUCCESS;
}
