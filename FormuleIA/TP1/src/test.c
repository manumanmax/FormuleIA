#include <stdio.h>
#include <stdlib.h>
#include "file.h"

int main(int argc, char** argv){
	
	File* f = creerFile();
	File* f1 = creerFile();

	enfiler(5,f);
	enfiler(6,f);
	enfiler(7,f);
	
	enfiler(9,f1);
	enfiler(9,f1);
	enfiler(9,f1);

	printf("%d\n", defiler(f));
	
	afficher(f);
	afficher(f1);
	
	printf("%d\n", defiler(f));
	printf("%d\n", defiler(f));
	printf("%d\n", defiler(f));

	concatener(f,f1);
	
	afficher(f);



	return EXIT_SUCCESS;
}
