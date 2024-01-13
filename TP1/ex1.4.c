#include <stdlib.h>
#include <stdio.h>

int main () {
	int c1,c2;  // int et pas char car comparaison avec EOF=-1 renvoyé par getchar()

    printf("Enter integer values n (0<=n<10), one per line:\n");

	while ((c1 = getchar()) != EOF) {  // lecture du premier caractère de la ligne
        //printf("caractere lu '%c' - code ascii %d\n", c1, c1);

		// vérifier si la ligne est vide
		if (c1 == '\n') {
			printf("Error: empty line\n");
			continue;
		}
				
		// vérifier si la ligne est trop longue
		if ((c2 = getchar()) != '\n') {   // lecture du second caractère de la ligne
			printf("Error: too many characters\n");
			// vider le buffer
			while (getchar() != '\n');   // lecture de tous les caractères restants de la ligne
			continue;
		}
				
		// vérifier si le caractère lu est un chiffre
		if (c1 < '0' || c1 > '9') {
			printf("Error: invalid character\n");
			continue; 
		}

		// calculer la factorielle
		int nbre = c1 - '0';  // récupération de la valeur entière
		int fact = 1;
		for (int i=2; i<=nbre; i++)
			fact *= i;
		printf("%d! = %d\n", nbre, fact);
	}
}
