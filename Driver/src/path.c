#include "../include/path.h"
#include "../include/pile.h"



int autourPosition(Position current,Vitesse vit,Carte *carte,int boost,Position autour[SIZEBIDIMTABLE][SIZEBIDIMTABLE],int valeur[SIZEBIDIMTABLE][SIZEBIDIMTABLE]){
 
	//	puts("Autour pos");
	int b;
	b=(boost)? 2:1;
	Position suivant;
	suivant.x=current.x+vit.vx;
	suivant.y=current.y+vit.vy;
	int max=(boost)?SIZEBIDIMTABLE:3;
	int possible=0;


	for(int i=0;i<max;i++){
		for(int j=0;j<max;j++){
			int sx=suivant.x-b+j;
			int sy=suivant.y-b+i;
			if((sx>=0 && sx<carte->tx) && (sy>=0 && sy<carte->ty)){
				autour[i][j].x=sx;
				autour[i][j].y=sy;
				valeur[i][j]=carte->map[sy][sx];
				if(valeur[i][j]=='#' || valeur[i][j]=='=' || valeur[i][j]=='~')
					possible=1;
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
	return possible;
}


int shortCutF(Circuit pilote,Carte carte, Position depart,Vitesse vDepart, Action *action, int* nBoost){


	if(!isPossible(depart,vDepart,&carte,0)) {
		return 0;
	}
	int nbBoost = *nBoost;
//	FILE* f = fopen("log.txt","a");
//	fprintf(f,"nombre de boosts : %d\n",nbBoost);
//	fflush(f);
	Action possible[SIZEBOOST]={{0,0}};

	for(int i=0;i<SIZEBIDIMTABLE;i++){
		for(int j=0;j<SIZEBIDIMTABLE;j++){
			possible[(SIZEBOOST-1)-i*SIZEBIDIMTABLE-j].vx=-2+i;
			possible[(SIZEBOOST-1)-i*SIZEBIDIMTABLE-j].vy=-2+j;
		}
	}

//	fprintf(f,"initialisation du tableau\n");

	char ****view=(char ****)calloc(carte.ty,sizeof(char***));
	for(int i=0;i<carte.ty;i++){
		view[i]=(char***)calloc(carte.tx,sizeof(char**));
		for(int j=0;j<carte.tx;j++){
			view[i][j]=(char **)calloc(11,sizeof(char*));
			for(int k=0;k<11;k++)
				view[i][j][k]=calloc(11,sizeof(char));
		}

	}

//	fprintf(f,"initialisation du tableau view\n");

	char vViewx[MAX][MAX][SIZEBOOST];
	char vViewy[MAX][MAX][SIZEBOOST];

	for(int i=0;i<MAX;i++)
		for(int j=0;j<MAX;j++)
			for(int k=0;k<SIZEBOOST;k++){
				vViewx[i][j][k]=50;
				vViewy[i][j][k]=50;
			}

//	fprintf(f,"initialisation du tableau vView\n");
//	fflush(f);
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
	int maxSpeed=ROUTE;
	int niveau = 0;
	int offset=1;
	
	while(carte.map[current.y][current.x]!='='){
		ElementFile a;
		offset=1;
		if(!videFileF(fi)){
			a=defilerF(fi);
			if(a.niveau != niveau && nbBoost > 0){
				nbBoost = nbBoost - 1;
//				fprintf(f,"reduction des boosts a %d\n",nbBoost);
			//	fflush(f);
				niveau++;
			}
		}
		else {

			destruction(view,carte.tx,carte.ty);

			return 0;
		}

		empiler(pileSauvegarde,a);

		current.x=a.preced.x;
		current.y=a.preced.y;
		vCurrent=a.vitesse;
		gen=a.generation;

		if(carte.map[current.y][current.x]=='~') maxSpeed=SAND;
		else maxSpeed=ROUTE;
		int p;
		if(nbBoost >= 1){
			p=autourPosition(current,vCurrent,&carte,1,autour,poids);
			offset=2;
		}
		else{
			p=autourPosition(current,vCurrent,&carte,0,autour,poids);
			offset=1;
		}
		view[current.y][current.x][vCurrent.vx+5][vCurrent.vy+5]=1;
		if(!p) continue;
		int i=0;
		int nombreCasesEnfiles=0;
		k++;

		for(i=0;i<SIZEBOOST;i++){
			if((possible[i].vx > 1 || possible[i].vx < -1
						|| possible[i].vy > 1 || possible[i].vy < -1)
					&& nbBoost < 1){
				//fprintf(f,"on saute l'acceleration %d - %d\n",possible[i].vx,possible[i].vy);
				continue;
			} //passe la position possible si c'est un boost et qu'il n'en reste plus

			if(possible[i].vx > 1 || possible[i].vx < -1
					|| possible[i].vy > 1 || possible[i].vy < -1) offset=2;
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
					&& (vViewx[futur.y][futur.x][i]!=vFutur.vx || vViewy[futur.y][futur.x][i]!=vFutur.vy)
					&& autour[possible[i].vy+offset][possible[i].vx+offset].x!=-1
					&& poids[possible[i].vy+offset][possible[i].vx+offset]!='.'
					&& norme <=maxSpeed){

				if(view[futur.y][futur.x][vFutur.vx+5][vFutur.vy+5]==0){
					a.action=possible[i];
					a.preced=futur;
					a.vitesse=vFutur;
					a.generation=k+i;
					a.generationP=gen;
					a.niveau = niveau + 1;
					vViewx[futur.y][futur.x][i]=vFutur.vx;
					vViewy[futur.y][futur.x][i]=vFutur.vy;


					view[futur.y][futur.x][vFutur.vx+5][vFutur.vy+5]=1;
					//fprintf(f,"acceleration %d ajoutee\n",a.generation);
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



	destruction(view,carte.tx,carte.ty);

	int taille = retrouverChemin(pileSauvegarde,action,gen,k);

	//	fprintf(f,"taille du tableau : %d\n",taille);

	//	for(int i = 0; i < taille; i++){
	//		fprintf(f,"%d - %d\n",action[i].vx, action[i].vy);
	//	}
	//	fflush(f);
	return taille;
	//return retrouverChemin(pileSauvegarde,action,gen,k);
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

void destruction(char ****tab,int tx,int ty){

	for(int i=0;i<ty;i++){
		for(int j=0;j<tx;j++){ 
			for(int k=0;k<11;k++){
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
	b=(boost)? 2:1;
	Position suivant;
	suivant.x=current.x+vCurrent.vx;
	suivant.y=current.y+vCurrent.vy;
	int max=(boost)? 5:3;

	for(int i=0;i<max;i++){
		for(int j=0;j<max;j++){
			int sx=suivant.x-b+j;
			int sy=suivant.y-b+i;
			if((sx>=0 && sx<carte->tx) && (sy>=0 && sy<carte->ty)){
				if(carte->map[sy][sx]!='.') return 1;
				//	printf("map %d\n",map[sy][sx]);
			}
		}
	}
	return 0;

}
