#include "fonction.h"
#include "Liste/listeA.h"
#include "pile/pile.h"
#include "struct.h"

void poidsDistance(Circuit *pilote)
{
	short val;
	for(int i=0; i < pilote->ty; i++)
		for(int j = 0; j < pilote->tx ; j++){
			val = pilote->tab[i*pilote->tx+j];
			if(val=='#'){
				pilote->tab[i*pilote->tx+j] = ROUTE;
				pilote->map[i][j]=ROUTE;
			}

			if(val == '.'){
				pilote->tab[i*pilote->tx+j] = 1000;

				pilote->map[i][j]=1000;
			}
			if(val == '='){
				pilote->tab[i*pilote->tx+j] = ARRIVE;

				pilote->map[i][j]=ARRIVE;
				pilote->arrivee.y=i;
				pilote->arrivee.x=j;
			}
			if(val == '~'){
				pilote->tab[i*pilote->tx+j] = SABLE;
				pilote->map[i][j]=SABLE;

			}
			if( val == '2') {
				pilote->tab[i*pilote->tx+j] = DEPART;
				pilote->map[i][j]=DEPART;

				pilote->depart.y=i;
				pilote->depart.x=j;
			}
		}
	//	printf("Avant: %d %d",pilote->arrivee.x,pilote->arrivee.y);
	pilote->tab[pilote->depart.y*pilote->tx+pilote->depart.x]=0;
	pilote->map[pilote->depart.y][pilote->depart.x]=0;
}


int positionG(Circuit pilote, int pos)
{
	if(pos-1 < 0)
		return -1;

	return pos-1;
}


int positionD(Circuit pilote, int pos)
{

	if(pos +1 >= pilote.taille)
		return -1;

	return pos+1;
}

int positionH(Circuit pilote, int pos)
{

	if(pos-pilote.tx < 0)
		return -1;

	return pos-pilote.tx;
}

int positionB(Circuit pilote, int pos)
{

	if(pos+pilote.tx >= pilote.taille)
		return -1;

	return pos+pilote.tx;
}
int positionGH(Circuit pilote, int pos)
{

	if(pos-pilote.tx -1 <0)
		return -1;

	return pos-pilote.tx-1;
}
int positionGB(Circuit pilote, int pos)
{

	if(pos+pilote.tx-1 >= pilote.taille)
		return -1;

	return pos+pilote.tx -1;
}
int positionDH(Circuit pilote, int pos)
{

	if(pos -pilote.tx+1 < 0)
		return -1;

	return pos-pilote.tx +1;
}

int positionDB(Circuit pilote, int pos)
{

	if(pos+pilote.tx+1 >= pilote.taille)
		return -1;

	return pos+pilote.tx+1;
}

int verif(Position tab[], Position pos)
{
	for(int i=0;i<50;i++)
		if(tab[i].x==pos.x && tab[i].y ==pos.y) return 1;
	return 0;
}

void autourPosition(Position current,Vitesse vit,int taillex,int tailley, short map[MAX][MAX],int boost,Position autour[6][6],int valeur[6][6])
{
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
			}
			else {
				autour[i][j].x=-1;
				autour[i][j].y=-1;
				valeur[i][j]=1000;

			}
		}
	}
	for(int i=0;i<3;i++){
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
	}
}

ListeA *creerListeA(Circuit pilote)
{
	ListeA *l=creerListe(pilote.tx*pilote.ty);

	for(int i=0; i < pilote.ty; i++){
		for(int j=0;j< pilote.tx;j++){

			if(pilote.map[i][j] != INFINITY){
				ajouter(l,i*pilote.tx+j,i*pilote.tx+j,pilote.map[i][j]);

			}

			Position current;
			current.x=j;
			current.y=i;
			Position pos[]={

				position_hautGauche(current,pilote.tx,pilote.ty),
				position_hautDroite(current,pilote.tx,pilote.ty),
				position_basDroite(current,pilote.tx,pilote.ty),
				position_basGauche(current,pilote.tx,pilote.ty),
				position_gauche(current,pilote.tx),
				position_droite(current,pilote.tx),
				position_haut(current,pilote.ty),
				position_bas(current,pilote.ty)
			};
			for(int k = 0; k < 8; k++){ 
				if(testPosition(pos[k]))
					if(pilote.map[pos[k].y][pos[k].x] != INFINITY && pilote.map[pos[k].y][pos[k].x]!=0)
						ajouter(l,i*pilote.tx+j,pos[k].y*pilote.tx+pos[k].x,pilote.map[pos[k].y][pos[k].x]);
			}
		}
	}

	return l;

}

Action *shortCut(Circuit pilote)
{
	Action *action1=malloc(sizeof(Action)*200);
	Action *action2=malloc(sizeof(Action)*200);
	Action possible[8];
	possible[0].vx=1;
	possible[0].vy=1;

	possible[1].vx=1;
	possible[1].vy=0;

	possible[2].vx=0;
	possible[2].vy=1;

	possible[3].vx=1;
	possible[3].vy=-1;

	possible[4].vx=-1;
	possible[4].vy=1;

	possible[5].vx=0;
	possible[5].vy=-1;

	possible[6].vx=-1;
	possible[6].vy=0;

	possible[7].vx=-1;
	possible[7].vy=-1;
	Position autour[6][6];
	int poids[6][6]={{-1,-1}};

	Position current=pilote.depart;
	Vitesse vCurrent;
	vCurrent.vx=0;
	vCurrent.vy=0;
	vCurrent.vy=0;
	Pile *pileA=creerPile();
	int i=0;
	int flag=0;
	int k=0;
	int fin=0;
	while(1){
		autourPosition(current,vCurrent,pilote.tx,pilote.ty,pilote.map,0,autour,poids);

		if(!flag)i=0;
		flag=0;
		while(autour[possible[i].vy+1][possible[i].vx+1].x ==-1 ||
				poids[possible[i].vy+1][possible[i].vx+1]==INFINITY || 
				((vCurrent.vx+possible[i].vy)*(vCurrent.vx+possible[i].vx) +(vCurrent.vy+possible[i].vy)*(vCurrent.vy+possible[i].vy)) >25
				|| vCurrent.vx+possible[i].vx<0
				|| vCurrent.vy +possible[i].vy<0){
			if(i>7 ) {flag=1;break;}
			printf("i: %d\n",i);

			i++;

		}

		printf("Choisi (%d %d)\n",autour[possible[i].vy+1][possible[i].vx+1].x,autour[possible[i].vy+1][possible[i].vx+1].y);
		printf("k: %d\n",k);
		printf("Arrive %d %d\t depart %d %d \n",pilote.arrivee.x,pilote.arrivee.y,pilote.depart.x,pilote.depart.y);
		printf("Vitesse: %d %d\n",vCurrent.vx,vCurrent.vy);
		printf("Flag: %d\n",flag);

		Act act;
		if(flag) {
			act=depiler(pileA);
			current=act.preced;
			i=act.position;
			vCurrent.vx-=act.action.vx;
			vCurrent.vy-=act.action.vy;

			k--;
			continue;
		}
		current=autour[possible[i].vy+1][possible[i].vx+1];
		act.action=possible[i];
		act.position=i;
		act.preced=current;
		vCurrent.vx+=act.action.vx;
		vCurrent.vy+=act.action.vy;
		empiler(pileA,act);
		action1[k]=act.action;
		k++;

		if ((current.x == pilote.arrivee.x) && (current.y == pilote.arrivee.y)) break;
		else {fin=1;
			//	break;
			//	puts("yopi");
		}

		printf("Pos: %d %d\n",current.x,current.y);


	}
	for(int i=0;i<k;i++)
		printf(" (%d & %d) ",action1[i].vx,action1[i].vy);

	return action1;


}




void circuitCopie(short from[][MAX], short to[][MAX])
{
	for(int i=0; i < MAX; i++)
		for(int j = 0; j < MAX ; j++){
			to[i][j]=from[i][j];
		}
}

Position position_droite(Position pos, int taille)
{
	Position nouvellePosition;
	if(pos.x>=0 && pos.x<taille-1)
	{
		nouvellePosition.x=pos.x+1;
		nouvellePosition.y=pos.y;
		return nouvellePosition;
	}
	nouvellePosition.x=-1;
	nouvellePosition.y=-1;
	return nouvellePosition;
}


Position position_haut(Position pos, int tailley)
{
	Position nouvellePosition;
	if(pos.y>0 && pos.y<tailley)
	{
		nouvellePosition.x=pos.x;
		nouvellePosition.y=pos.y-1;
		return nouvellePosition;
	}
	nouvellePosition.x=-1;
	nouvellePosition.y=-1;
	return nouvellePosition;
}
Position position_bas(Position pos, int tailley)
{
	Position nouvellePosition;
	if(pos.y>=0 && pos.y<tailley-1)
	{
		nouvellePosition.x=pos.x;
		nouvellePosition.y=pos.y+1;
		return nouvellePosition;
	}
	nouvellePosition.x=-1;
	nouvellePosition.y=-1;
	return nouvellePosition;
}

Position position_gauche(Position pos, int taillex)
{
	Position nouvellePosition;
	if(pos.x>0 && pos.x<taillex)
	{
		nouvellePosition.x=pos.x-1;
		nouvellePosition.y=pos.y;
		return nouvellePosition;
	}
	nouvellePosition.x=-1;
	nouvellePosition.y=-1;
	return nouvellePosition;
}
Position position_hautDroite(Position pos, int taillex,int tailley)
{
	Position nouvellePosition;
	if(pos.x>=0 && pos.x<taillex-1 && pos.y >0 && pos.y <tailley)
	{
		nouvellePosition.x=pos.x+1;
		nouvellePosition.y=pos.y-1;
		return nouvellePosition;
	}
	nouvellePosition.x=-1;
	nouvellePosition.y=-1;
	return nouvellePosition;
}
Position position_hautGauche(Position pos, int taillex,int tailley)
{
	Position nouvellePosition;
	if(pos.x>0 && pos.x<taillex && pos.y>0 && pos.y<tailley)
	{
		nouvellePosition.x=pos.x-1;
		nouvellePosition.y=pos.y-1;
		return nouvellePosition;
	}
	nouvellePosition.x=-1;
	nouvellePosition.y=-1;
	return nouvellePosition;
}
Position position_basDroite(Position pos, int taillex,int tailley)
{
	Position nouvellePosition;
	if(pos.x>=0 && pos.x<taillex-1 && pos.y>=0 && pos.y<tailley-1)
	{
		nouvellePosition.x=pos.x+1;
		nouvellePosition.y=pos.y+1;
		return nouvellePosition;
	}
	nouvellePosition.x=-1;
	nouvellePosition.y=-1;
	return nouvellePosition;
}
Position position_basGauche(Position pos, int taillex,int tailley)
{
	Position nouvellePosition;
	if(pos.x>=0 && pos.x<taillex-1 && pos.y>=0 && pos.y <=tailley-1)
	{
		nouvellePosition.x=pos.x-1;
		nouvellePosition.y=pos.y+1;
		return nouvellePosition;
	}
	nouvellePosition.x=-1;
	nouvellePosition.y=-1;
	return nouvellePosition;
}
int testPosition(Position pos)
{
	if(pos.x==-1 && pos.y==-1)
		return 0;

	else return 1;
}

Vitesse *vitessePossibles(Position *shortP,int taille)
{
	Vitesse *vPos=malloc(sizeof(Vitesse)*taille);
	int k=0;
	int x,y;
	for(int i=0;i<taille-2;i++)
	{
		Vitesse v1;
		v1.vx=(shortP[i+1].x-shortP[i].x);
		v1.vy=(shortP[i+1].y-shortP[i].y);

	/*	Vitesse v2;
		v2.vx=(shortP[i+1].x-shortP[i+2].x)*-1;
		v2.vy=(shortP[i+1].y-shortP[i+2].y)*-1;

	//	printf(" (%d & %d) (%d & %d)\t(%d %d)\n(%d & %d)\n\n",v1.vx,v1.vy,v2.vx,v2.vy,x,y,shortP[i].x,shortP[i].y);

		x=v2.vx-v1.vx;

	//	if(v2.vy!=v1.vy)
		y=v2.vy-v1.vy;
		
		if(v2.vx==v1.vx)x=v1.vx;
		if(v2.vy==v1.vy)y=v1.vy;*/

			vPos[i].vx=v1.vx;
			vPos[i].vy=v1.vy;

			k++;

	}
	for(int i=0;i<taille;i++)
	printf("%d (%d & %d) \n",i,vPos[i].vx,vPos[i].vy);
	puts(" ");

	return vPos;

}

/*********************fonctions en marge pour la gestion du pilotage********************************/

Vitesse direction(Position *shortP, int index){

	Vitesse v;
	v.vx = shortP[index+1].x - shortP[index].x;
	v.vy = shortP[index+1].y - shortP[index].y;

	return v;
}

void initDirection(short map[MAX][MAX], Vitesse mapD[MAX][MAX], Position *shortP, int taille){
	int indexD = 0;
	int x = 0, y = 0;
	int variationX, variationY;
	Vitesse dtn;
	Vitesse dS, dP;
	Position posC;
	//initialisation des directions
	for(;indexD < taille-1;indexD++){
		mapD[shortP[indexD].x][shortP[indexD].y] = direction(shortP, indexD);
	}
	posC.x = shortP[indexD].x;
	posC.y = shortP[indexD].y;

	for(indexD = 1; indexD < taille - 2; indexD++){
		posC.x = shortP[indexD].x;
		posC.y = shortP[indexD].y;

		//x = shortP[
		if(dtn.vx != 0 && dtn.vy != 0){
			printf("%d->[%d,%d]\n",indexD,dtn.vx,dtn.vy);
		}
	}
}








