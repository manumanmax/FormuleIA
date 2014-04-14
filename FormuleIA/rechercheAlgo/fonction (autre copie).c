#include "fonction.h"
#include "Liste/listeA.h"
#include "pile/pile.h"
#include "struct.h"


void autourPosition(Position current,Vitesse vit,int taillex,int tailley, char map[MAX][MAX],int boost,Position autour[6][6],int valeur[6][6])
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
			if((sx>=0 && sx<taillex) && (sy>=0 && sy<tailley)){
				autour[i][j].x=sx;
				autour[i][j].y=sy;
				valeur[i][j]=map[sy][sx];
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


int shortCutF(Circuit pilote, Position depart,Vitesse vDepart, Action action[200]){
	Action possible[9]={{0,0}};
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			possible[8-i*3-j].vx=-1+i;
			possible[8-i*3-j].vy=-1+j;

		}
	}

	//	for(int i=0;i<9;i++)
	//		printf("%d %d\n",possible[i].vx,possible[i].vy);

	short view[MAX][MAX]={{0,0}};
	Vitesse vView[MAX][MAX]={{{0,0}}};
	Vitesse vCurrent=vDepart;
	Position current=depart;
	//	current=pilote.depart;
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
	Position futur={0,0};
	int gen=0;

	while(pilote.map[current.y][current.x]!='='){

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

		autourPosition(current,vCurrent,pilote.tx,pilote.ty,pilote.map,0,autour,poids);
		view[current.y][current.x]=1;
		//	vView[current.y][current.x]=vCurrent;

		//	printf("Current %d %d\n",current.x,current.y);

		//	if( (current.x==3 && current.y==0))break;
		//		printf("k: %d\n",k);	
		int i=0;
		int j=0;
		int nombreCasesEnfiles=0;
		k++;
		for(i=0;i<9;i++){

			Vitesse vFutur={0,0};
			vFutur.vx=possible[i].vx+vCurrent.vx;
			vFutur.vy=possible[i].vy+vCurrent.vy;
			futur.x=vFutur.vx+current.x;
			futur.y=vFutur.vy+current.y;
			int norme=(vFutur.vx)*(vFutur.vx) +(vFutur.vy)*(vFutur.vy);
			/*	printf(" Possible %d %d\n",possible[i].vx,possible[i].vy);
				printf(" vFutur %d %d\n",vFutur.vx,vFutur.vy);
				printf(" Futur %d %d\n",futur.x,futur.y);
				printf(" Tableau %d %d\n",vView[futur.y][futur.x].vx,vView[futur.y][futur.x].vy);
				printf(" i %d\n\n",i);*/
			

			if( futur.x < pilote.tx
					&&  futur.y< pilote.ty
					&& futur.x>=0
					&& futur.y>=0
					&& (vView[futur.y][futur.x].vx!=vFutur.vx || vView[futur.y][futur.x].vy!=vFutur.vy)
					&& autour[possible[i].vy+1][possible[i].vx+1].x!=-1
					&& poids[possible[i].vy+1][possible[i].vx+1]!=46
					&& norme <=25){

				if(view[futur.y][futur.x]==0){
					ElementFile a;
					a.action=possible[i];
					a.preced=futur;
					a.vitesse=vFutur;
					a.generation=k+i;
					a.generationP=gen;
					vView[futur.y][futur.x]=vFutur;
					enfilerF(fi,a);
					nombreCasesEnfiles++;
					if(pilote.map[futur.y][futur.x]==1) {
						fini=1;
						current=futur;
						empiler(pileSauvegarde,a);
						/*	puts("**********Enfiler*********");
							printf("Futur %d %d \t%d %d\n",futur.x,futur.y,vFutur.vx,vFutur.vy);
							puts("**********Enfiler*********");*/

						break;
					}
					/*	puts("**********Enfiler*********");
						printf("Futur %d %d \t%d %d\n",futur.x,futur.y,vFutur.vx,vFutur.vy);
						puts("**********Enfiler*********");*/


				}
				else j++;
			}


		}
		//	printf("nombreCasesEnfiles %d\n",nombreCasesEnfiles);

		//On ne marque pas si on ne prend qu'une case
		if(nombreCasesEnfiles<1 && j<1){
			vView[futur.y][futur.x].vx=0;
			vView[futur.y][futur.x].vy=0;
			view[current.y][current.x]=0;

		}
		k+=i;
		if(fini){
			break;

		}


	}
	//	printf("Current %d %d\n",current.x,current.y);

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

int isArrived(Position *posArrived,short *alreadyArrived,char map[][MAX],Position pilot1,Position pilot2,int taille) {

	for(int i=0;i<taille;i++){
		if(posArrived[i].x==pilot1.x && posArrived[i].y==pilot1.y && !alreadyArrived){
			alreadyArrived[i]=1;
			map[posArrived[i].y][posArrived[i].x]='.';
			return 1;
		}
		if(posArrived[i].x==pilot2.x && posArrived[i].y==pilot2.y && !alreadyArrived){
			alreadyArrived[i]=1;
			map[posArrived[i].y][posArrived[i].x]='.';

			return 1;
		}

	}
	return 0;
}

