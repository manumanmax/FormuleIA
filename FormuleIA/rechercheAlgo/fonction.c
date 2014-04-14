#include "fonction.h"
#include "Liste/listeA.h"
#include "pile/pile.h"
#include "struct.h"


void autourPosition(Position current,Vitesse vit,Carte *carte,int boost,Position autour[6][6],int valeur[6][6])
{
	//	puts("Autour pos");
	int b;
	b=(boost)? 2:1;
	Position suivant;
	suivant.x=current.x+vit.vx;
	suivant.y=current.y+vit.vy;
	int max=3*b;

	for(int i=0;i<max;i++){
		for(int j=0;j<max;j++){
			int sx=suivant.x-b+j;
			int sy=suivant.y-b+i;
			if((sx>=0 && sx<carte->tx) && (sy>=0 && sy<carte->ty)){
				autour[i][j].x=sx;
				autour[i][j].y=sy;
				valeur[i][j]=carte->map[sy][sx];
				//	printf("map %d\n",map[sy][sx]);
			}
			else {
				autour[i][j].x=-1;
				autour[i][j].y=-1;
				valeur[i][j]='.';
			}
		}
	}
	/*	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
		printf("(%d %d)",autour[i][j].x,autour[i][j].y);
		}
		puts(" ");
		}

		for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
		printf("(%d)",valeur[i][j]);
		}
		puts(" ");
		}*/
}


int shortCutF(Circuit pilote,Carte carte, Position depart,Vitesse vDepart, Action action[200]){
	Action possible[9]={{0,0}};
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			possible[8-i*3-j].vx=-1+i;
			possible[8-i*3-j].vy=-1+j;

		}
	}


	int ****view=(int ****)calloc(MAX,sizeof(int***));
	for(int i=0;i<MAX;i++){
		view[i]=(int***)calloc(MAX,sizeof(int**));
		for(int j=0;j<MAX;j++){
			view[i][j]=(int **)calloc(11,sizeof(int*));
			for(int k=0;k<11;k++)
				view[i][j][k]=calloc(11,sizeof(int));
		}

	}


	Vitesse vView[MAX][MAX][9];
	for(int i=0;i<MAX;i++)
		for(int j=0;j<MAX;j++)
			for(int k=0;k<9;k++){
				vView[i][j][k].vx=-10;
				vView[i][j][k].vy=-10;

			}

	Vitesse vCurrent=vDepart;
	Position current=depart;
	FileF *fi=creerFileF();
	Pile *pileSauvegarde=creerPile();
	int poids[6][6]={{'.'}};
	Position autour[6][6]={{{-1,-1}}};

	Action act={0,0};
	ElementFile e={{0,0},{0,0},{0,0},0};
	e.preced=current;
	e.vitesse=vCurrent;
	e.action=act;
	e.generationP=0;
	enfilerF(fi,e);
	int k=0;
	int fini=0;
	int gen=0;

	while(carte.map[current.y][current.x]!='='){

		if(videFileF(fi)){
			puts("File vide");
			return 0;

		}
		ElementFile a=defilerF(fi);

		empiler(pileSauvegarde,a);

		current.x=a.preced.x;
		current.y=a.preced.y;
		vCurrent=a.vitesse;
		gen=a.generation;

		autourPosition(current,vCurrent,&carte,0,autour,poids);
		view[current.y][current.x][vCurrent.vy+5][vCurrent.vx+5]=1;
		int i=0;
		int j=0;
		int nombreCasesEnfiles=0;
		k++;
		for(i=0;i<9;i++){

			Position futur={0,0};

			Vitesse vFutur={0,0};
			vFutur.vx=possible[i].vx+vCurrent.vx;
			vFutur.vy=possible[i].vy+vCurrent.vy;
			futur.x=vFutur.vx+current.x;
			futur.y=vFutur.vy+current.y;
			int norme=(vFutur.vx)*(vFutur.vx) +(vFutur.vy)*(vFutur.vy);


			if( futur.x < carte.tx
					&&  futur.y< carte.ty
					&& futur.x>=0
					&& futur.y>=0
					&& (vView[futur.y][futur.x][i].vx!=vFutur.vx || vView[futur.y][futur.x][i].vy!=vFutur.vy)
					&& autour[possible[i].vy+1][possible[i].vx+1].x!=-1
					&& poids[possible[i].vy+1][possible[i].vx+1]!=46
					&& norme <=25){

				if(view[futur.y][futur.x][vFutur.vy+5][vFutur.vx+5]==0){
					ElementFile a;
					a.action=possible[i];
					a.preced=futur;
					a.vitesse=vFutur;
					a.generation=k+i;
					a.generationP=gen;
					vView[futur.y][futur.x][i]=vFutur;
					view[futur.y][futur.x][vFutur.vy+5][vFutur.vx+5]=1;
					enfilerF(fi,a);
					nombreCasesEnfiles++;
					if(carte.map[futur.y][futur.x]=='=') {
						fini=1;
						gen=k+i;
						empiler(pileSauvegarde,a);

						break;
					}


				}
			}


		}
		k+=i;
		if(fini){
			break;

		}


	}

	return retrouverChemin(pileSauvegarde,action,gen,k);

}

int retrouverChemin(Pile *pileBackUp,Action action[300],int gen,int taille){

	int i=0;
	int generation=gen;
	while(generation!=0){
		ElementFile tmp=depiler(pileBackUp);

		if(tmp.generation==generation){
			generation=tmp.generationP;
			action[i]=tmp.action;
			i++;

		}

	}
	Action temp;
	for(int k=0;k<(i/2);k++) {
		temp=action[k];
		action[k]=action[i-k-1];
		action[i-k-1]=temp;

	}
	return i;
}


int recherchePos(ElementFile *tab,int generation,int taille){
	for(int i=0;i<taille;i++){
		if(tab[i].generation==generation){
			return i;

		}

	}
	return -1;

}

int isArrived(Position *posArrived,short *alreadyArrived,int **map,Position pilot1,Position pilot2,int taille) {

	for(int i=0;i<taille;i++){
		if(posArrived[i].x==pilot1.x && posArrived[i].y==pilot1.y && !alreadyArrived[i]){
			alreadyArrived[i]=1;
			map[posArrived[i].y][posArrived[i].x]='.';
			return 1;
		}
		if(posArrived[i].x==pilot2.x && posArrived[i].y==pilot2.y && !alreadyArrived[i]){
			alreadyArrived[i]=1;
			map[posArrived[i].y][posArrived[i].x]='.';

			return 1;
		}

	}
	return 0;
}

