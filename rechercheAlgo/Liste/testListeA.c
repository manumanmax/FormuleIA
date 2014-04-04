#include <stdlib.h>
#include <stdio.h>
#include "listeA.h"

int main(void)
{
ListeA *l= creerListe(5);
ajouter(l,0,1,4);
ajouter(l,0,2,4);

ajouter(l,1,2,5);
affichage(l);

return EXIT_SUCCESS;
}
