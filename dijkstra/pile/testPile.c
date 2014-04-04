#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

int main(void)
{
Pile *pile=creerPile();
empiler(pile,5);
empiler(pile,6);
empiler(pile,4);
printf("Dans tete: %d",pile->head->pos);
printf(" %d ",depiler(pile));

return EXIT_SUCCESS;
}
