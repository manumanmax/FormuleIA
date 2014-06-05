#ifndef ACT_H
#define ACT_H
#include "action.h"
#include "position.h"

typedef struct _Act
{
	Action action;
	int position;
	Position preced;
}Act;


#endif
