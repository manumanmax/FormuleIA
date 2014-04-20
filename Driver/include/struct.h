#ifndef STRUCT_H
#define STRUCT_H

typedef struct _Action
{
	char vx;
	char vy;
}Action;
typedef Action Vitesse;

typedef struct _Position
{
	unsigned char x;
	unsigned char y;

}Position;


typedef struct _Act
{
	Action action;
	int position;
	Position preced;
}Act;

typedef struct _ElementFile
{
	Action action;
	Position preced;
	Vitesse vitesse;
	int generation;
	int generationP;

}ElementFile;

#endif
