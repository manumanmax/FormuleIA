#ifndef ELEMENT_FILE_H
#define ELEMENT_FILE_H

#include "vitesse.h"
#include "action.h"
#include "position.h"

typedef struct _ElementFile
{
	Action action;
	Position preced;
	Vitesse vitesse;
	int generation;
	int generationP;
	int niveau;

}ElementFile;

#endif
