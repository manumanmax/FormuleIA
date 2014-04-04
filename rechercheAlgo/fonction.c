#include "fonction.h"
#include "Liste/listeA.h"
#include "pile/pile.h"
#include "struct.h"

void poidsDistance(Circuit *pilote)
{
	short val;
	for(int i=0; i < pilote->ty; i++)
		for(int j = 0; j < pilote->tx ; j++){
			val = pilote->map[i][j];
			if(val=='#'){
				pilote->map[i][j]=ROUTE;
			}

			if(val == '.'){
				//pilote->tab[i*pilote->tx+j] = 1000;

				pilote->map[i][j]=1000;
			}
			if(val == '='){
				//pilote->tab[i*pilote->tx+j] = ARRIVE;

				pilote->map[i][j]=ARRIVE;
				pilote->arrivee.y=i;
				pilote->arrivee.x=j;
			}
			if(val == '~'){
				pilote->tab[i*pilote->tx+j] = SABLE;
				pilote->map[i][j]=SABLE;

			}
		}
			/*if( val == '2') {
				pilote->tab[i*pilote->tx+j] = DEPART;
				pilote->map[i][j]=DEPART;

				pilote->depart.y=i;
				pilote->depart.x=j;
			}
		}
	//	printf("Avant: %d %d",pilote->arrivee.x,pilote->arrivee.y);
	pilote->tab[pilote->depart.y*pilote->tx+pilote->depart.x]=0;
	pilote->map[pilote->depart.y][pilote->depart.x]=0;*/
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

ListeA *creerListeA(Circuit pilote)
{
	ListeA *l=creerListe(pilote.tx*pilote.ty);

	for(int i=0; i < pilote.ty; i++){
		for(int j=0;j< pilote.tx;j++){

			if(pilote.map[i][j] != 1000){
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
					if(pilote.map[pos[k].y][pos[k].x] != 1000 && pilote.map[pos[k].y][pos[k].x]!=0)
						ajouter(l,i*pilote.tx+j,pos[k].y*pilote.tx+pos[k].x,pilote.map[pos[k].y][pos[k].x]);
			}
		}
	}

	return l;

}

int shortCut(Circuit pilote, Action action1[200])
{
	//Action *action1=malloc(sizeof(Action)*200);
	Action action2[200];
	Action possible[9];
	possible[0].vx=1;
	possible[0].vy=1;

	possible[1].vx=1;
	possible[1].vy=0;

	possible[2].vx=0;
	possible[2].vy=1;

	possible[3].vx=0;
	possible[3].vy=-1;

	possible[4].vx=0;
	possible[4].vy=0;

	possible[5].vx=-1;
	possible[5].vy=-1;

	possible[6].vx=-1;
	possible[6].vy=1;

	possible[7].vx=-1;
	possible[7].vy=1;

	possible[8].vx=-1;
	possible[8].vy=0;

	//	possible[3].vx=0;
	//	possible[3].vy=0;
	Position autour[6][6];
	int poids[6][6]={{-1,-1}};

	Position current=pilote.depart;
	Vitesse vCurrent;
	vCurrent.vx=0;
	vCurrent.vy=0;
	vCurrent.vy=0;
	Pile *pileA=creerPile();
	int j=0;
	int i=0;
	int trouver=0;
	int k=0;
	int fin=0;
	int arriveP=0;
	int vitesseNulle=0;
	int nombreEmpiler=0;
	int arrive=1000;


	do{
		vitesseNulle=0;
		autourPosition(current,vCurrent,pilote.tx,pilote.ty,pilote.map,0,autour,poids);


	/*	puts("------------Avant------------------\n");
		printf(" (%d %d)\n",current.x,current.y);
		printf("Vitesse: %d %d\n",vCurrent.vx,vCurrent.vy);
		printf("k: %d\n",k);
		printf("Arrive %d %d\t depart %d %d \n",pilote.arrivee.x,pilote.arrivee.y,pilote.depart.x,pilote.depart.y);
		printf("Flag: %d\n\n",trouver);*/

	//	puts("-------------Avant-----------------\n");
		if(trouver)j=0;
		trouver=0;
	//	puts("************Recherche*************");
		for(i=j+1;i<9;i++){

			vitesseNulle=0;
			Vitesse vFutur;
			Position futur;
			vFutur.vx=possible[i].vx+vCurrent.vx;
			vFutur.vy=possible[i].vy+vCurrent.vy;
			futur.x=vFutur.vx+current.x;
			futur.y=vFutur.vy+current.y;


			if((vCurrent.vx+possible[i].vx)==0 && (vCurrent.vy+possible[i].vy)==0 && k!=0) vitesseNulle=1;
			//if(possible[i].vx==0 && possible[i].vy ==0 && vCurrent.vx==0 && vCurrent.vy==0 && i<8) i++;

			if( futur.x < pilote.tx
					&&  futur.y< pilote.ty
					&& autour[possible[i].vy+1][possible[i].vx+1].x!=-1
					&& !vitesseNulle
					&& (poids[possible[i].vy+1][possible[i].vx+1]!=1000 && poids[possible[i].vy+1][possible[i].vx+1]!=4)
					&& ((vFutur.vx)*(vFutur.vx) +(vFutur.vy)*(vFutur.vy)) <=25
					&&  (verifD(vFutur,pilote.mapD,autour[possible[i].vy+1][possible[i].vx+1],pilote.tx,pilote.ty) || isJumping(vFutur,futur,pilote.map))) {
				trouver=1;
			//	printf("Jump");
				break;

			}
			//		printf("i: %d\t||",i);


		}
		j=i;
	//	puts(" ");
	//	puts("************Recherche*************");

		Act act;

		if (trouver && pilote.map[current.y+vCurrent.vy+possible[j].vy][current.x+vCurrent.vx+possible[j].vx]==1){

			act.action=possible[j];
			vCurrent.vx+=act.action.vx;
			vCurrent.vy+=act.action.vy;
			//	puts("Choisi:");

			//	printf(" (%d %d)\n",current.x,current.y);
			//	printf("Vitesse: %d %d\n",vCurrent.vx,vCurrent.vy);
			//	current=autour[possible[j].vy+1][possible[j].vx+1];
			act.position=j;
			act.preced=current;
			empiler(pileA,act);
			action1[k]=act.action;

			current.y+=vCurrent.vy;
			current.x+=vCurrent.vx;

		//	puts("yop");
			nombreEmpiler++;
			arriveP=1;
			k++;
			//	break;
			if(k<arrive){
				//printf("Le nombre est de %d et avant %d\n",k,arrive);
				arrive=k;
				for(int i=0;i<200;i++){
				action2[i].vx=0;action2[i].vy=0;}
				
				for(int i=0;i<k;i++){
					action2[i]=action1[i];
				}
			}

			for(int i=0;i<nombreEmpiler+1;i++){
				act=depiler(pileA);
				current=act.preced;
				j=act.position;
				vCurrent.vx-=act.action.vx;
				vCurrent.vy-=act.action.vy;
				k--;
			}
			nombreEmpiler=0;
			trouver=0;
			continue;

		}
		//printf("k: %d\n",k);
		if(trouver){

			act.action=possible[j];
			vCurrent.vx+=act.action.vx;
			vCurrent.vy+=act.action.vy;

			//	puts("Choisi:");

			//	printf(" (%d %d)\n",current.x,current.y);
			//	printf("Vitesse: %d %d\n",vCurrent.vx,vCurrent.vy);
			//	current=autour[possible[j].vy+1][possible[j].vx+1];
			act.position=j;
			act.preced=current;
			empiler(pileA,act);
			action1[k]=act.action;
			k++;

			current.y+=vCurrent.vy;
			current.x+=vCurrent.vx;

			if(arriveP) nombreEmpiler++;
		}

		else{
			k--;	
			//	printf("Avant :%d %d\n",current.x,current.y);
			act=depiler(pileA);
			current=act.preced;
			j=act.position;
			vCurrent.vx-=act.action.vx;
			vCurrent.vy-=act.action.vy;

			if(arriveP) nombreEmpiler--;
			//	puts("Depile");
			//	printf("Après :%d %d\n",current.x,current.y);
		}
		//printf("empiler %d %d\n",nombreEmpiler,arriveP);
		/*		printf("Pos current: %d %d\n",current.x,current.y);
		//	printf("Choisi (%d %d)\n",autour[possible[j].vy+1][possible[j].vx+1].x,autour[possible[j].vy+1][possible[j].vx+1].y);
		printf("k: %d\n",k);
		printf("Arrive %d %d\t depart %d %d \n",pilote.arrivee.x,pilote.arrivee.y,pilote.depart.x,pilote.depart.y);
		printf("Vitesse: %d %d\n",vCurrent.vx,vCurrent.vy);
		printf("Flag: %d\n\n",trouver);*/


		//	if(fin==1000) break;


		fin++;


	}while(!videPile(pileA));
	if(arriveP){
		for (int i = 0; i < arrive; i++) {
			action1[i]=action2[i];
		}
	}
	return arrive;


}


int isJumping(Vitesse vCurrent,Position current,short map[MAX][MAX]){

	Position before;
	before.x=current.x-vCurrent.vx;
	before.y=current.y-vCurrent.vy;
	int nbrCasesx=(vCurrent.vx>0) ? vCurrent.vx : (-1)*vCurrent.vx;
	int nbrCasesy=(vCurrent.vy>0) ? vCurrent.vy : (-1)*vCurrent.vy;
	int nbCases=(nbrCasesy>nbrCasesx) ? nbrCasesy : nbrCasesx;
	int sensx=(vCurrent.vx>0) ? 1:-1;
	int sensy=(vCurrent.vy>0) ? 1:-1;

	for(int i=0;i<nbCases;i++){
		if(nbrCasesx>0){
			before.x+=sensx;
			if(map[before.y][before.x]==1000) return 1;
	nbrCasesx--;

		}

		if(nbrCasesy>0){
			before.y+=sensy;
			if(map[before.y][before.x]==1000) return 1;
nbrCasesy--;

		}


	}
	return 0;

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
	for(int i=0;i<taille-1;i++)
	{
		Vitesse v1;
		v1.vx=(shortP[i+1].x-shortP[i].x);
		v1.vy=(shortP[i+1].y-shortP[i].y);

		//	printf(" (%d & %d) (%d & %d)\n",v1.vx,v1.vy,shortP[i].x,shortP[i].y);


		vPos[i].vx=v1.vx;
		vPos[i].vy=v1.vy;

		//	k++;

	}
	/*	for(int i=0;i<taille-2;i++)
		printf("%d (%d & %d) \n",i,vPos[i].vx,vPos[i].vy);
		puts(" ");*/

	return vPos;

}

void direction(Vitesse mapD[][MAX],short map[][MAX],Position *shortP,Vitesse *vPos,int taille,int taillex,int tailley){
	Position temp;

	for(int i=0;i<MAX;i++)
		for(int j=0;j<MAX;j++){
			mapD[i][j].vx=0;
			mapD[i][j].vy=0;

		}

	for(int c=0;c<taille;c++){

		int decx=9;
		int decy=9;
		int debutx=0;
		int debuty=0;

		Position current=shortP[c];
		Vitesse vCurrent=vPos[c];

		Position pos[]={

			position_hautGauche(current,taillex,tailley),
			position_hautDroite(current,taillex,tailley),
			position_basDroite(current,taillex,tailley),
			position_basGauche(current,taillex,tailley),
			position_gauche(current,taillex),
			position_droite(current,taillex),
			position_haut(current,tailley),
			position_bas(current,tailley)
		};

		if(map[pos[4].y][pos[4].x]==1000) {debutx=decx/2;decx=3*decx;}

		if(map[pos[5].y][pos[5].x]==1000) {debutx=-decx;decx=0;}

		if(map[pos[6].y][pos[6].x]==1000) {debuty=decy/2;decy=3*decy;}

		if(map[pos[7].y][pos[7].x]==1000) {debuty=-decy;decy=0;}
		if((map[pos[4].y][pos[4].x]==1000 && map[pos[5].y][pos[5].x]==1000) 
				||(map[pos[6].y][pos[6].x]==1000 && map[pos[7].y][pos[7].x]==1000)){
			mapD[current.y][current.x]=vCurrent;
			continue;
		}

		/*	printf("deb %d\n",debut);
			printf("%d\n",map[pos[4].y][pos[4].x]);*/

		if(current.x-decx<0) decx=current.x;
		if(current.y-decy<0) decy=current.y;

		if(current.x+decx>taillex) decx=taillex-current.x;
		if(current.y+decy>tailley) {decy=tailley-current.y;}


		int x=current.x-decx/3;
		int y=current.y-decy/3;

		//	printf("%d %d ->%d %d\n\n",current.x,current.y,decx,decy);

		for(int i=debuty;i<decy;i++){
			for(int j=debutx;j<decx;j++){
				temp.x=x+j;
				temp.y=y+i;


				mapD[temp.y][temp.x]=vCurrent;

				//	printf("%d & %d ",temp.x,temp.y);

			}


		}
	}

}



int samePos(Position *shortP,Position current,int taille){

	for(int i=0;i<taille;i++){
		if(shortP[i].x==current.x && shortP[i].y==current.y)
			return 1;

	}

	return 0;

}

int verifD(Vitesse current,Vitesse mapD[][MAX],Position pos,int taillex,int tailley){


	if(pos.x > taillex || pos.y>tailley) return 0;
	//	printf("Pos: %d %d\n",pos.x,pos.y);
	Vitesse ref=mapD[pos.y][pos.x];
	//	printf("Ref: %d %d\n",ref.vx,ref.vy);

	if(ref.vx==0 && ref.vy==0) return 1;
	if(current.vx==0 && current.vy==0) return 1;

	float angleMax=0.6;

	if((ref.vx ==0 && ref.vy !=0) ||(ref.vx!=0 && ref.vy==0)) angleMax=0.9;

	float ps=current.vx*ref.vx+current.vy*ref.vy;
	float normePs=(current.vx*current.vx+current.vy*current.vy)*(ref.vx*ref.vx+ref.vy*ref.vy);

	float x=ps*ps/normePs;

	/*	printf(" %d %d\n",ref.vx,ref.vy);
		printf(" %d %d\n",current.vx,current.vy);
		printf(" ps:%f\n",ps);
		printf(" norme: %f\n",normePs);*/

	if(ps<0) return 0;
	if(x==1 && ps>0) return 1;
	if(x>=angleMax && ps >0) return 1;

	return 0;

}
