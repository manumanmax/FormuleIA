#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/path.h"
#include "../include/communication.h"



int main(int argc, char** argv){

	Circuit pilote;
	Carte carte;

	FILE *info = fopen("testlog.log","w");
	if(info==NULL) perror("probleme: ");


	short nombreArrivees=0;
	char c;
	int nbBoost = NBBOOST;
//	int carburant=0	;

	fscanf(stdin,"%hd %hd",&carte.tx,&carte.ty/*,&carburant*/);

	fprintf(info,"taille %d x %d\n\n", carte.tx, carte.ty);
	int **tab=(int **)malloc(sizeof(int *)*carte.ty);
	for(int i=0;i<carte.ty;i++)
		tab[i]=malloc(sizeof(int)*carte.tx);

	carte.map=tab;


	int **tabC=(int **)malloc(sizeof(int *)*carte.ty);
	for(int i=0;i<carte.ty;i++)
		tabC[i]=malloc(sizeof(int)*carte.tx);

	carte.mapCopie=tabC;

	for(int i=0; i < carte.ty; i++){
		for(int j = 0; j <carte.tx; j++) {
			c=getc(stdin);
			if(c=='\n')
				c=getc(stdin);


			carte.map[i][j]=c;
			carte.mapCopie[i][j]=c;
			if(c=='='){
				nombreArrivees++;
			}

		}
	}
	fflush(stdin);

	Position *posArrived=malloc(sizeof(Position)*nombreArrivees);
	short *alreadyArrived=malloc(sizeof(short)*nombreArrivees);
	int k=0;
	for(int i = 0; i < carte.ty; i++){
		for(int j = 0; j < carte.tx; j++){
			if(carte.map[i][j]=='='){
				alreadyArrived[k]=0;
				posArrived[k].x=j;
				posArrived[k].y=i;
				k++;

			}

		}
	}
	displayMap(carte,info);

	//fflush(info);
	fprintf(info,"\n === Debut Course === \n");

	//fflush(info);
	int px;
	int py;
	int pv1x, pv1y;
	int pv3x, pv3y;

	int flagPosDepartSet = 1;
	fscanf(stdin,"%d %d\t%d %d\t%d %d",&px, &py, &pv1x, &pv1y, &pv3x, &pv3y);
	fflush(stdin);
	//fprintf(info,"position de depart : %d %d\n", px, py);	
	pilote.depart.x = px;
	pilote.depart.y = py;



	Position pilot1;
	Position pilot2;

	Action *action1=malloc(sizeof(Action)*500);
	Vitesse vDepart={0,0};
	int taille = shortCutF(pilote,carte,pilote.depart,vDepart,action1,&nbBoost);
	displayAction(action1,info,taille);

	int tour = 0;
	int posTab = 0;
	Position suivante;
	Vitesse vCourante={0,0};
	Position preced={px,py};
	Position s={0,0};
	Vitesse vVerif={0,0};
	int collision1=0;
	int collision2=0;


	while(!feof(stdin)){
		tour++;
		preced.x=px;
		preced.y=py;
		collision1=0;
		collision2=0;
		fprintf(info,"\n === Tour %d === \n", tour);
		if(!flagPosDepartSet){
			fscanf(stdin,"%d %d\t%d %d\t%d %d",&px, &py, &pv1x, &pv1y, &pv3x, &pv3y);
			fflush(stdin);
		}else{
			flagPosDepartSet = 0;
		}
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
				|| (vCourante.vx==0 && vCourante.vy==0)) {


			taille=shortCutF(pilote,carte,current,vCourante,action1,&nbBoost);

			if(taille>=1)
				posTab=0;

			displayAction(action1,info,taille);
			vVerif=vCourante;



		}



		if(suivante.x == pv1x && suivante.y == pv1y && isPossible(current,vCourante,&carte,0)){
			fprintf(info, "---------RECALCUL1------------\n");
			taille=calculBecauseCollision(pilote,carte,current,vCourante,action1,pilot1,&posTab,&nbBoost);
			displayAction(action1,info,taille);

			collision1=1;
		}
		if(suivante.x == pv3x && suivante.y == pv3y && isPossible(current,vCourante,&carte,0)){
			fprintf(info, "---------RECALCUL2------------\n");
			taille=calculBecauseCollision(pilote,carte,current,vCourante,action1,pilot2,&posTab,&nbBoost);
			displayAction(action1,info,taille);

			collision2=1;

		}



		fprintf(info,"Vitesse %d %d\n",vCourante.vx,vCourante.vy);



		if(isArrived(posArrived,alreadyArrived,carte.map,pilot1,pilot2,nombreArrivees)
				&& isPossible(current,vCourante,&carte,0)){

			if(collision1) carte.map[pilot1.y][pilot1.x]='.';
			if(collision2) carte.map[pilot2.y][pilot2.x]='.';


			fprintf(info, "---------Calcul car arrivée bouchée------------");

			taille = shortCutF(pilote,carte,current,vCourante,action1,&nbBoost);
			displayAction(action1,info,taille);

			if(carte.mapCopie[pilot1.y][pilot1.x]!='=')
				carte.map[pilot1.y][pilot1.x]=carte.mapCopie[pilot1.y][pilot1.x];

			if(carte.mapCopie[pilot2.y][pilot2.x]!='=')
				carte.map[pilot2.y][pilot2.x]=carte.mapCopie[pilot2.y][pilot2.x];



			if(taille>=1)
				posTab=0;

		}

		if(action1[posTab].vx == 2 || action1[posTab].vy == 2 ||
				action1[posTab].vx == -2 || action1[posTab].vy == -2){
			nbBoost--;
			fprintf(info,"Boost %d\n",nbBoost);
		}

		fprintf(info,"\n === Action === \n");
		fflush(stdout);

		//Écriture synchrone de l'accélération.
		printf("%d %d\n",action1[posTab].vx,action1[posTab].vy);
		fflush(stdout);
		vVerif.vx += action1[posTab].vx;
		vVerif.vy += action1[posTab].vy;
		fprintf(info, "%d %d\n", action1[posTab].vx,action1[posTab].vy);
		//fflush(info);
		posTab++;
	}

	//fclose(info);



	return EXIT_SUCCESS;
}
