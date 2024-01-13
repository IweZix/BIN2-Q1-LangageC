#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>   // compiler avec le flag -lm
#include <time.h>

int main() {
    int choix, n, m, nBits, maxVal, newN, newM;
    bool continuer = true;
    int** image = NULL;
    int* histo;

    srand((unsigned) time(NULL));  // voir explications dans solution de TP2 - exo 4
    
    while (continuer) {
        printf("\nMENU:\n" \
                "\t1) Création d’image avec valeurs aléatoires\n" \
                "\t2) Création d’une image avec valeurs prédéfinies\n" \
                "\t3) Affichage de l’image\n" \
                "\t4) Changement de la taille de l’image\n" \
                "\t5) Affichage de l’histogramme de l’image\n" \
                "\t6) Suppression de l’image\n" \
                "\t7) Quitter le programme\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);
        
        switch (choix) {
        case 1: case 2:
            if (image != NULL) {
                printf("Erreur: l'image courante doit être supprimée avant d'en créer une nouvelle\n");
                continue;
            }
            printf("Entrez les dimensions de l'image (nombre de lignes puis de colonnes): ");
            scanf("%d%d", &n, &m);
            printf("Entrez la profondeur de bits de l'image: ");
            scanf("%d", &nBits);
            maxVal = pow(2,nBits);
            
            printf("Création d'une image (%d,%d) de profondeur de bits %d " \
                   "avec des valeurs %s pour les pixels\n", 
                   n, m, nBits, (choix==1) ? "aléatoires" : "prédéfinies");
            
            image = (int**) malloc(n * sizeof(int*));
            if (image == NULL) {
                perror("Erreur: malloc impossible\n");
                exit(1);
            }
            for (int i=0; i<n; i++) {
                image[i] = (int*) malloc(m * sizeof(int));
                if (image[i] == NULL) {
                    perror("Erreur: malloc impossible\n");
                    exit(1);                        
                }
            }
            
            for (int i=0; i<n; i++) {
                for (int j=0; j<m; j++) {
                    if (choix == 1) 
                        image[i][j] = rand() % maxVal;  
                    else  // choix 2
                        image[i][j] = (i+1) % maxVal;
                }
            }
                
            break;
            
        case 3:
            if (image == NULL) {
                printf("Image vide\n");
                continue;
            }
            printf("Affichage de l'image:\n");
            // Parcours par pointeurs
            for (int** lig=image; lig-image<n; lig++) {
                for (int* col=*lig; col-*lig<m; col++) {
                    printf("%5d", *col);
                }
                printf("\n");
            }
            // Parcours par indices
            /*
            for (int i=0; i<n; i++) {
                for (int j=0; j<m; j++) {
                    printf("%5d", image[i][j]);
                }
                printf("\n");
            } */
            break;
            
        case 4:
            if (image == NULL) {
                printf("Aucune image courante\n");
                continue;
            }
            printf("Entrez les nouvelles dimenions de l'image (nombre de lignes puis de colonnes): ");
            scanf("%d%d", &newN, &newM);
            if ((newN >= n && newM <= m) || (newN <= n && newM >= m)) {
                printf("Dimensions non valides\n");
                continue;
            }
            
            if (newN < n) {
                // decoupage (crop)
                for (int i=newN; i<n; i++) {
                    free(image[i]);
                }
                image = realloc(image, newN * sizeof(int*));
                if (image == NULL) {
                    perror("Erreur: malloc impossible\n");
                    exit(1);
                }
                for (int i=0; i<newN; i++) {
                    image[i] = realloc(image[i], newM * sizeof(int));
                    if (image[i] == NULL) {
                        perror("Erreur: malloc impossible\n");
                        exit(1);                        
                    }
                }
            } else {
                // agrandissement
                image = (int**) realloc(image, newN * sizeof(int*));
                if (image == NULL) {
                    perror("Erreur: malloc impossible\n");
                    exit(1);
                }
                for (int i=0; i<n; i++) {
                    image[i] = realloc(image[i], newM * sizeof(int));
                    if (image[i] == NULL) {
                        perror("Erreur: malloc impossible\n");
                        exit(1);                        
                    }
                    for (int j=m; j<newM; j++) {
                        image[i][j] = 0;
                    }
                }
                for (int i=n; i<newN; i++) {
                    image[i] = (int*) calloc(newM, sizeof(int));  // ou malloc avec boucle d'initialisation des pixels à 0
                    if (image[i] == NULL) {
                        perror("Erreur: malloc impossible\n");
                        exit(1);                        
                    }
                }
            }
            n = newN;
            m = newM;
            break;
            
        case 5:
            if (image == NULL) {
                printf("Aucune image courante\n");
                continue;
            }
            histo = calloc(maxVal, sizeof(int));  // ou malloc avec boucle d'initialisation des compteurs à 0
            if (histo == NULL) {
                perror("Erreur: malloc impossible\n");
                exit(1);
            }
            for (int i=0; i<n; i++)
                for (int j=0; j<m; j++)
                    histo[image[i][j]]++;
                
            printf("Histogramme:\n");
            int count = 0;
            for (int i=0; i<maxVal; i++) {
                if (histo[i] != 0) {
                    printf("\t#pixels de valeur %d: %d\n", i, histo[i]);
                    count += histo[i];
                }
            }
            if (count != n*m) printf("Erreur: il manque des pixels dans l'histogramme\n");
            printf("Nombre de pixels dans l'image: %d\n", n*m);
            
            free(histo);
            break;
            
        case 7:
            printf("Sortie du programme\n");
            continuer = false;
            // pas de break pour exécuter l'opération 6 (libération de la mémoire de l'image)
        
        case 6: 
            if (image == NULL) {
                printf("Aucune image à libérer\n");
            } else {
                printf("Libération de la mémoire dynamique\n");
                for (int i=0; i<n; i++)
                    free(image[i]);
                free(image);
                image = NULL;
            }
            break;
            
        default:
            printf("Erreur: opération non définie\n");
        }
    }
}
