#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main (int argc, char* argv[]) {
    int nbMots = argc - 1;
    if (nbMots == 0) {
       printf("Usage: %s needs arguments in command line\n", argv[0]);
       exit(1);
    }

    // copie des arguments de la ligne de commande
    char** tabMots = (char**) malloc(nbMots * sizeof(char*));
    if (!tabMots) { perror("erreur d'allocation mémoire"); exit(1); }
	
    for (int i=0; i<nbMots; i++) {
        tabMots[i] = (char*) malloc((strlen(argv[i+1])+1) * sizeof(char));
        if (!tabMots[i]) { perror("erreur d'allocation mémoire"); exit(1); }

        /// Version avec strcpy (copie de chaîne)
        strcpy(tabMots[i],argv[i+1]);        
        for (int j=0; j<strlen(tabMots[i]); j++)
           if (islower((unsigned char)tabMots[i][j]))
              tabMots[i][j] = toupper((unsigned char)tabMots[i][j]);
        
        /// Version sans strcpy (copie de caractères)
        /*
        for (int j=0; j<strlen(argv[i+1])+1; j++)   // '\0' doit également être copié
              tabMots[i][j] = toupper((unsigned char)argv[i+1][j]);
        */

        // Attention! Contrairement à la fonction strcpy() qui réalise une copie profonde
        // ('deep copy') dans le bloc de mémoire alloué dynamiquement, l'instruction
        //     tabMot[i] = argv[i+1];
        // réalise une copie superficielle ('shallow copy' --> deux variables partagent
        // le même bloc de mémoire), ce qui doit être évité. De plus, elle provoque
        // une fuite mémoire (perte de l'adresse du bloc alloué via malloc).
    }

    // affichage du tableau des mots en majuscules
    for (int i=0; i<nbMots; i++){
        printf("%s ", tabMots[i]);
    }
    printf("\n");
    
    // affichage du tableau des arguments
    for (int i=0; i<nbMots; i++){
        printf("%s ", argv[i+1]);
    }
    printf("\n");
    
    // libération de la mémoire
    for (int i=0;i<nbMots;i++)
        free(tabMots[i]);
    free(tabMots);
}
