#ifndef STRUCT_H
#define STRUCT_H

typedef struct _Action
{
	short vx;
	short vy;
}Action;
typedef Action Vitesse;

typedef struct _Position
{
	short x;
	short y;

}Position;


typedef struct _Act
{
	Action action;
	int position;
	Position preced;
}Act;



#endif
