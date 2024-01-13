#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main() {
    // Definition des dimensions de la grille
    int nLignes, nCol;
    printf("H = ? ");
    scanf("%d", &nLignes);
    printf("L = ? ");
    scanf("%d", &nCol);
    printf("\n");

    // Allocation de la matrice et du tableau de positions des jetons
    char** cases = (char **)malloc(nLignes*sizeof(char *));
    int* remplissageCol = (int *)malloc(nCol*sizeof(int));
    if (cases == NULL || remplissageCol == NULL){
        perror("Probleme memoire!\n");
        exit(1);
    }
    for (int i = 0; i < nLignes; i++){
        cases[i] = (char *)malloc(nCol*sizeof(char));
        if (cases[i] == NULL){
            perror("Probleme memoire!\n");
            exit(1);
        }
    }

    // Initialisation de la matrice
    for (int i = 0; i< nLignes; i++){
        for (int j = 0; j < nCol; j++){
            cases[i][j] = '.';
        }
    }
    for (int j = 0; j < nCol; j++)
        remplissageCol[j] = nLignes-1;

    // Jeu
    char pionJoueur = 'X';
    char pionJouePas = 'O';
    int colJoueur;
    do {
        // Permutation des joueurs
        char temp = pionJoueur;
        pionJoueur = pionJouePas;
        pionJouePas = temp;

        // Affichage tableau
        for (int i = 0; i < nLignes; i++){
            for (int j = 0; j< nCol; j++){
                printf("%2c", cases[i][j]);
            }
            printf("\n");
        }

        // Lecture de la colonne a jouer
        printf("\nColonne joueur %c ? ", pionJoueur);
        scanf("%d", &colJoueur);

        // Cas de la colonne pleine
        if (colJoueur>0 && colJoueur<=nCol && remplissageCol[colJoueur-1] < 0){
            printf("Colonne pleine! Tu passes ton tour!\n");
            continue;
        }

        // Cas de placement d'un pion
        if (colJoueur>0 && colJoueur<=nCol){
            cases[remplissageCol[colJoueur-1]][colJoueur-1] = pionJoueur;
            remplissageCol[colJoueur-1]--;
        }

        // Cas du rajout de colonnes
        else if (colJoueur>nCol){
            for (int i = 0; i < nLignes; i++){
                cases[i] = (char*) realloc(cases[i], colJoueur*sizeof(char));
                if (cases[i] == NULL){
                    perror("Probleme memoire!\n");
                    exit(1);
                }
                for (int j = nCol; j < colJoueur; j++){
                    cases[i][j] = '.';
                }
            }
            remplissageCol = (int*) realloc(remplissageCol, colJoueur*sizeof(int));
            if (remplissageCol == NULL){
                perror("Probleme memoire!\n");
                exit(1);
            }
            for (int j = nCol; j < colJoueur; j++){
                remplissageCol[j] = nLignes-1;
            }
            nCol = colJoueur;
        }

        // Cas de la suppression de colonnes
        else if (colJoueur<0 && -colJoueur<nCol){
            nCol = -colJoueur;
            // On decale toutes les colonnes vers la gauche
            for (int i = 0; i < nLignes; i++){
                cases[i] = (char*) realloc(cases[i], nCol*sizeof(char));
                if (cases[i] == NULL){
                    perror("Probleme memoire!\n");
                    exit(1);
                }
            }
            remplissageCol = (int*) realloc(remplissageCol, nCol*sizeof(int));
            if (remplissageCol == NULL){
                perror("Probleme memoire!\n");
                exit(1);
            }
        } else if (colJoueur == 0){
            nCol = 0;
        }

    } while (nCol != 0);

    printf("\nFin de partie!\n");

    // Liberation de la memoire dynamique
    for (int i = 0; i < nLignes; i++)
        free(cases[i]);
    free(cases);
    free(remplissageCol);
}
