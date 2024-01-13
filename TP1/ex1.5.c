#include <stdio.h>
#include <limits.h>

int main () {
	int car1,car2,c; // int et pas char car comparaison avec EOF=-1 renvoyé par getchar()
    
    printf("Enter integer values n (0<=n<100), one per line:\n");

	while ((car1 = getchar()) != EOF) {   // lecture du premier caractère de la ligne
		// vérifier si la ligne est vide
		if (car1 == '\n') {
			printf("Error: empty line\n");
			continue;
		}

		// vérifier si le premier caractère lu est un chiffre
		if (car1 < '0' || car1 > '9') {
			printf("Error: invalid character\n");
			// vider le buffer
			while (getchar() != '\n');  // lecture de tous les caractères restants de la ligne
			continue; 
		}
		
		// récupération de la valeur entière
		int nbre = car1 - '0';  
		
		if ((car2 = getchar()) != '\n') {
			// vérifier si la ligne est trop longue
			if ((c = getchar()) != '\n') {
				printf("Error: too many characters\n");
				// vider le buffer
				while (getchar() != '\n');  // lecture de tous les caractères restants de la ligne
				continue;
			}

			// vérifier si le second caractère lu est un chiffre
			if (car2 < '0' || car2 > '9') {
				printf("Error: invalid character\n");
				continue; 
			}

			// récupération de la valeur entière
			nbre = nbre*10 + car2 - '0';  
		}
		
		// calculer la factorielle de nbre
		int i;
		int fact = 1;
		for (i=2; i<=nbre; i++) {
			if (fact>INT_MAX/i) {
				printf("Error: integer overflow\n");
				break;
			}
			fact *= i;
		}
		if (i>nbre)
			printf("%d! = %d\n", nbre, fact);
	}
}
