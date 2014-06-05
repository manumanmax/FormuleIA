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

FileF* creerFileF();
void detruireFileF(FileF *file);
int videFileF(FileF* f);
void enfilerF(FileF *f,ElementFile val);
ElementFile defilerF(FileF *f);
void concatenerF(FileF *f1, FileF *f2);
void affichageFileF(FileF *f);
FileF *copieF(FileF *file);
#endif
