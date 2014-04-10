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
	FileF *fileSauvegarde=creerFileF();
	int poids[6][6]={{1000}};
	Position autour[6][6]={{{-1,-1}}};

	Action act={0,0};
	ElementFile e={{0,0},{0,0},{0,0},0};
	e.preced=current;
	e.vitesse=vCurrent;
	e.action=act;
	e.generationP=0;
	enfilerF(fi,e);
	view[current.y][current.x]=1;
	vView[current.y][current.x]=vCurrent;
	int vitesseNulle=0;
	int k=0;
	int fini=0;
	Position futur={0,0};
	int gen=0;

	while(pilote.map[current.y][current.x]!=1){

		if(videFileF(fi)){
			puts("File vide");
			return 0;

		}
		ElementFile a=defilerF(fi);
		enfilerF(fileSauvegarde,a);
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

			vitesseNulle=0;
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
					&& poids[possible[i].vy+1][possible[i].vx+1]!=1000 
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
						enfilerF(fileSauvegarde,a);
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

	return retrouverChemin(fileSauvegarde,action,current,pilote.depart,k);

}


int retrouverChemin(FileF *fileBackUp,Action action[200],Position final,Position depart,int taille){

	ElementFile *tab=malloc(sizeof(ElementFile)*taille+5);
	int i=0;
	while(!videFileF(fileBackUp)){

		tab[i]=defilerF(fileBackUp);
		i++;
	}
/*	for(int j=0;j<i;j++){
		printf("preced %d %d\n",tab[j].preced.x,tab[j].preced.y);
		printf("vitesse %d %d\n",tab[j].vitesse.vx,tab[j].vitesse.vy);
		printf("g %d %d\n\n",tab[j].generation,tab[j].generationP);

	}*/
//	return 0;
//	Position preced=final;
	//	printf(" Position final %d %d\t Position depart %d %d\n",final.x,final.y,depart.x,depart.y);
	action[0]=tab[i-1].action;
//	printf("action %d %d\n",action[0].vx,action[0].vy);
	Vitesse vFinale=tab[i-1].vitesse;
	int genF=tab[i-1].generation;
	Vitesse vPreced=vFinale;
	int gen=tab[i-1].generationP;
	i=1;
	int index=0;
	while(1){
		index=recherchePos(tab,gen,taille+1);
		//	printf("index %d",index);

		if(index!=-1) {

			gen=tab[index].generationP;

			action[i]=tab[index].action;
		//	printf("i %d\t action %d %d\n",i,action[i].vx,action[i].vy);
		//	printf("preced %d %d\n",preced.x,preced.y);
		//	printf("vitesse %d %d\n",vPreced.vx,vPreced.vy);
		//	printf("G GP %d %d\n",tab[index].generation,tab[index].generationP);


			i++;
		}
		if(gen==0) break;

	}

//	for(int k=0;k<i;k++)
//		printf("%d %d\n",action[k].vx,action[k].vy);


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

