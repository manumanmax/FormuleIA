#include <stdio.h>
#include <stdlib.h>
#include "../include/file.h"


FileF *creerFileF()
{
	FileF *file=malloc(sizeof(FileF));

	file->head=NULL;
	file->tail=NULL;
	file->taille=0;
	return file;
}

void enfilerF(FileF *file,ElementFile val)
{
	if(videFileF(file))
	{

		CelluleF *cell=malloc(sizeof(CelluleF));
		cell->val=val;

		cell->suivant=NULL;
		file->tail=cell;
		file->head=file->tail;
		file->taille++;
		return;
	}

		file->taille++;
	CelluleF *cell=malloc(sizeof(CelluleF));
	cell->val=val;
cell->suivant=NULL;
	file->tail->suivant=cell;
	file->tail=cell;


}

ElementFile defilerF(FileF *file)
{
ElementFile e;

	if(videFileF(file))
		return e;
	
	CelluleF *cell=file->head;
	e=file->head->val;
	file->head=cell->suivant;
	free(cell);
	file->taille--;
	cell=NULL;
	if(file->head==NULL)
		file->tail=NULL;
	return e;

}



int videFileF(FileF *file)
{
	if(file==NULL){
		return 1;
	}


	if(file->head==NULL){
		return 1;
	}

	if(file->tail==NULL){
		return 1;
	}
	
	if(file->taille==0)
		return 1;

	return 0;

}


void detruireFileF(FileF *file)
{
	if(videFileF(file))
			return;

	while(!videFileF(file))
	{
		defilerF(file);
	}
	free(file);
}

