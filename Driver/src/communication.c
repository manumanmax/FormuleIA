#include "../include/communication.h"


int calculBecauseCollision(Circuit pilote,Carte map,Position current,Vitesse vCurrent,Action *action1, Position pilote1,int *posTab,int *nbBoost){

	int taille=0;
	map.map[pilote1.y][pilote1.x] = '.';
	taille = shortCutF(pilote,map,current,vCurrent,action1, nbBoost);

	map.map[pilote1.y][pilote1.x] = map.mapCopie[pilote1.y][pilote1.x];
	if(taille>=1)
		*posTab=0;

return taille;
}

void displayMap(Carte map,FILE *f){

	for(int i = 0; i < map.ty; i++){
		for(int j = 0; j < map.tx; j++){
			fprintf(f, "%c", map.map[i][j]);
		}
		fprintf(f, "\n");
	}

}

void displayAction(Action *action,FILE *f,int taille){

	for(int i = 0; i < taille; i++){
				fprintf(f,"%d %d\n", action[i].vx, action[i].vy); 
			}

}
