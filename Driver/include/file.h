/**
  *\file file.h
  */

#ifndef FILE_H
#define FILE_H
#include "elementFile.h"


typedef struct _Cellule
{
	struct _Cellule* suivant;
	ElementFile val;
}CelluleF;


typedef struct _File
{
	CelluleF *head;
	CelluleF *tail;
	int taille;


}FileF;

/**
  *\fn FileF* creerFileF();
  *\brief permet de créer la file
  *\return la file
  */
FileF* creerFileF();
/**
  *\fn void detruireFileF(FileF *file);
  *\brief permet de détruire la file
  *\param la file à détruire
  *\return void
  */
void detruireFileF(FileF *file);
/**
  *\fn int videFileF(FileF* f);
  *\brief permet de savoir si une file est vide
  *\param la file
  *\return 1 si vide, 0 sinon
  */
int videFileF(FileF* f);
/**
  *\fn void enfilerF(FileF *f,ElementFile val);
  *\brief permet d'enfiler un élément dans la file
  *\param la file et l'élément à enfiler
  *\return void
  */

void enfilerF(FileF *f,ElementFile val);
/**
  *\fn ElementFile defilerF(FileF *f);
  *\brief Permet de défiler un élément de  la file
  *\param la file
  *\return l'élément défilé
  */

ElementFile defilerF(FileF *f);
#endif
