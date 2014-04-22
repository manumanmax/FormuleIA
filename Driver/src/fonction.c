#include "../include/fonction.h"
#include "../include/pile.h"
#include "../include/struct.h"



void autourPosition(Position current,Vitesse vit,Carte *carte,int boost,Position autour[SIZEBIDIMTABLE][SIZEBIDIMTABLE],int valeur[SIZEBIDIMTABLE][SIZEBIDIMTABLE]){
	//	puts("Autour pos");
	Position suivant;
	suivant.x=current.x+vit.vx;
	suivant.y=current.y+vit.vy;
	int b;
	int max = 3;
	
	b=(boost)? 2:1;

	if(boost)
		max = SIZEBIDIMTABLE;

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


int shortCutF(Circuit pilote,Carte carte, Position depart,Vitesse vDepart, Action *action, int* nbBoost){
	//unsigned short tableSize = SIZEBOOST;
	//FILE* f = fopen("log.txt","w+");
	Action possible[SIZEBOOST]={{0,0}};
	for(int i=0;i<SIZEBIDIMTABLE;i++){
		for(int j=0;j<SIZEBIDIMTABLE;j++){
			possible[(SIZEBOOST-1)-i*SIZEBIDIMTABLE-j].vx=-2+i;
			possible[(SIZEBOOST-1)-i*SIZEBIDIMTABLE-j].vy=-2+j;
		}
	}

	//fprintf(f,"table possible set\n");

	char ****view=(char ****)calloc(MAX,sizeof(char***));
	for(int i=0;i<MAX;i++){
		view[i]=(char***)calloc(MAX,sizeof(char**));
		for(int j=0;j<MAX;j++){
			view[i][j]=(char **)calloc((SIZEBOOST+2),sizeof(char*));
			for(int k=0;k<(SIZEBOOST+2);k++)
				view[i][j][k]=calloc((SIZEBOOST+2),sizeof(char));
		}
	}
	//fprintf(f,"table view set\n");
	/*	char view[MAX][MAX][36]={{{0}}};
		for(int i=0;i<MAX;i++)
		for(int j=0;j<MAX;j++)
		for(int k=0;k<26;k++)
		view[i][j][k]=0;*/


	/*	for(int i=0;i<carte.ty;i++)
		for(int j=0;j<carte.tx;j++)
		for(int k=0;k<11;k++)
		for(int l=0;l<11;l++)
		view[i][j][k][l]=0;*/

	char vViewx[MAX][MAX][SIZEBOOST];
	char vViewy[MAX][MAX][SIZEBOOST];

	for(int i=0;i<MAX;i++)
		for(int j=0;j<MAX;j++)
			for(int k=0;k<SIZEBOOST;k++){
				vViewx[i][j][k]=50;
				vViewy[i][j][k]=50;
			}
	//fprintf(f,"table vView set\n");

	Vitesse vCurrent=vDepart;
	Position current=depart;
	FileF *fi=creerFileF();
	Pile *pileSauvegarde=creerPile();
	int poids[SIZEBIDIMTABLE][SIZEBIDIMTABLE]={{'.'}};
	Position autour[SIZEBIDIMTABLE][SIZEBIDIMTABLE]={{{-1,-1}}};

	Action act={0,0};
	ElementFile e={{0,0},{0,0},{0,0},0};
	e.preced=current;
	e.vitesse=vCurrent;
	e.action=act;
	e.generationP=0;
	enfilerF(fi,e);
	int k=0;
	int gen=0;
	int fini=0;
	
	//fprintf(f,"positioned before while\n");
	while(carte.map[current.y][current.x]!='='){
		ElementFile a;

		if(!videFileF(fi)){
			a=defilerF(fi);
		}

		else {
			destruction(view);
			return 0;
		}

		empiler(pileSauvegarde,a);

		current.x=a.preced.x;
		current.y=a.preced.y;
		vCurrent=a.vitesse;
		gen=a.generation;

		autourPosition(current,vCurrent,&carte,1,autour,poids);
		view[current.y][current.x][vCurrent.vx+5][vCurrent.vy+5]=1;
		int i=0;
		int nombreCasesEnfiles=0;
		k++;
		//TODO: definir une variable local pour boucler en fonction de si il reste des boosts
		for(i=0;i<SIZEBOOST;i++){
 
			if((possible[i].vx > 1 || possible[i].vx < -1
				|| possible[i].vy > 1 || possible[i].vy < -1)
				&& *nbBoost <= 1){
				continue;
			} //passe la position possible si c'est un boost et qu'il n'en reste plus

			Position futur={0,0};

			Vitesse vFutur={0,0};
			vFutur.vx=possible[i].vx+vCurrent.vx;
			vFutur.vy=possible[i].vy+vCurrent.vy;
			futur.x=vFutur.vx+current.x;
			futur.y=vFutur.vy+current.y;
			int norme=(vFutur.vx)*(vFutur.vx) +(vFutur.vy)*(vFutur.vy);
			//TODO: see if autour depend on for's size
			if( futur.x < carte.tx
					&&  futur.y< carte.ty
					&& futur.x>=0
					&& futur.y>=0
					&& (vViewx[futur.y][futur.x][i]!=vFutur.vx || vViewy[futur.y][futur.x][i]!=vFutur.vy)
					&& autour[possible[i].vy+1][possible[i].vx+1].x!=-1
					&& poids[possible[i].vy+1][possible[i].vx+1]!=46
					&& norme <=25){

				if(view[futur.y][futur.x][vFutur.vx+5][vFutur.vy+5]==0){
					ElementFile a;
					a.action=possible[i];
					a.preced=futur;
					a.vitesse=vFutur;
					a.generation=k+i;
					a.generationP=gen;
					vViewx[futur.y][futur.x][i]=vFutur.vx;
					vViewy[futur.y][futur.x][i]=vFutur.vy;

					view[futur.y][futur.x][vFutur.vx+5][vFutur.vy+5]=1;
					enfilerF(fi,a);
					nombreCasesEnfiles++;
					if(vFutur.vx > 1 || vFutur.vy > 1 || vFutur.vx < -1 || vFutur.vy < -1){
						*nbBoost--;
					}
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
	//fprintf(f,"after loop\n");
	destruction(view);
	//fprintf(f,"after destruction\n");

	return retrouverChemin(pileSauvegarde,action,gen,k);
}

int retrouverChemin(Pile *pileBackUp,Action *action,int gen,int taille){

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

void destruction(char ****tab){

	for(int i=0;i<MAX;i++){
		for(int j=0;j<MAX;j++){ 
			for(int k=0;k<(SIZEBOOST+2);k++){
				free(tab[i][j][k]);
			}
			free(tab[i][j]);
		}
		free(tab[i]);
	}

	free(tab);


}

char opti(Vitesse v){
	char contenant=0;
	char x=v.vx+5;
	char y=v.vy+5;

	contenant=x;
	contenant=(contenant <<4);
	contenant=(contenant | y);

	return contenant;


}


int isPossible(Position current,Vitesse vCurrent, Carte *carte,int boost){


	int b;
	Position suivant;
	suivant.x=current.x+vCurrent.vx;
	suivant.y=current.y+vCurrent.vy;
	int max = 3;

	b=(boost)? 2:1;

	if(boost)
		max = SIZEBIDIMTABLE;

	for(int i=0;i<max;i++){
		for(int j=0;j<max;j++){
			int sx=suivant.x-b+j;
			int sy=suivant.y-b+i;
			if((sx>=0 && sx<carte->tx) && (sy>=0 && sy<carte->ty)){
				if(carte->map[i][j]=='#') return 1;
				//	printf("map %d\n",map[sy][sx]);
			}
		}
	}
	return 0;

}
