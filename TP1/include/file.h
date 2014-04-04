#ifndef MAIN_H
#define MAIN_H

typedef int Element;

typedef struct Cellule 
{
	struct Cellule* suivant;
	Element contenu;

} Cellule;



typedef struct {

	Cellule* tete;
	Cellule* queue;

} File;


File* creerFile();
unsigned short testVide(File* file);
int enfiler(Element e, File* file);
int defiler(File* file);
void concatener(File* f1, File* f2);
void afficher(File* file);

#endif
