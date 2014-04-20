#include <stdio.h>
#include <stdlib.h>
#include "../include/file.h"


FileF *creerFileF()
{
	FileF *file=malloc(sizeof(FileF));

	file->head=NULL;
	file->tail=NULL;
	return file;
}

void enfilerF(FileF *file,ElementFile val)
{
	if(videFileF(file))
	{

		CelluleF *cell=malloc(sizeof(CelluleF));
		cell->val=val;

		file->tail=cell;
		cell->suivant=file->head;
		file->head=cell;
		return;
	}


	CelluleF *cell=malloc(sizeof(CelluleF));
	cell->val=val;
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
	cell=NULL;
//	if(file->head->suivant==NULL)
//		file->tail=NULL;
	return e;

}


void affichageFileF(FileF *file)
{
	if(videFileF(file))
		return;

	CelluleF *cell=file->head;
	do
	{
		printf("%d->",cell->val);
		cell=cell->suivant;

	}while(cell!=NULL);
	puts("NULL");


}

int videFileF(FileF *file)
{
	if(file==NULL){
		puts("File non allouée");
		return 1;
	}


	if(file->head==NULL){
		//puts("Tete nulle");
		return 1;
	}

	if(file->tail==NULL){
		puts("tail vide");
		return 1;
	}

	return 0;

}

void concatenerF(FileF *f1, FileF *f2)
{
	if(videFileF(f2))
		return;

	if(videFileF(f1))
	{f1=f2;}

	f1->tail->suivant=f2->head;
	f1->tail=f2->head;
	f2->head=NULL;
	f2->tail=NULL;


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

FileF *copieF(FileF *f)
{
	if(videFileF(f))
		return NULL;

	FileF *file=creerFileF();
	CelluleF *tmp=f->head;

	do
	{

		enfilerF(file,tmp->val);
		tmp=tmp->suivant;

	}while(tmp!=NULL);


	return file;
}
