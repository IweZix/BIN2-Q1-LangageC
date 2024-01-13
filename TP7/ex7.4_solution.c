#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char** copierArgs (char** tab, int n, int* ncp);
void trier (char** tab, int n);
void afficher (char** tab, int n);


int main (int argc, char* argv[]) {
   // Copie profonde des arguments du programme
   int taille;
   char** copie = copierArgs(argv+1, argc-1, &taille);
   if (copie == NULL) {
	   printf("Erreur de copie d'argv\n");
	   exit(1);
   }
   
   // Affichage du tableau
   printf("Arguments non triés:\n");
   afficher(copie, taille);

   // Tri du tableau
   trier(copie, taille);
   
   // Affichage du tableau trié
   printf("Arguments triés:\n");
   afficher(copie, taille);

   // Libération de la mémoire dynamique
   for (int i=0; i<taille; i++)
      free(copie[i]);
   free(copie);
}

/**
 * PRE: tab: tableau de n chaînes de caractères
 * POST: *ncp: nombre de chaînes dans le tableau renvoyé
 * RES: renvoie un tableau contenant les chaînes de tab sans doublon
 *      (taille logique = taille physique); NULL si une erreur s'est produite
 */
char** copierArgs (char** tab, int n, int* ncp) {
   // Allocation du tableau dynamique de chaînes
   char** res = (char**)malloc(n*sizeof(char*));
   if (res == NULL) {
      printf("copierArgs: Erreur d'allocation mémoire du tableau res\n");
      return NULL;
   }

   // Copie des chaînes de tab
   *ncp = 0;
   bool trouve;
   for (int i = 0; i < n; i++) {
      // Recherche de la chaîne tab[i] dans res
      int j = 0;
      trouve = false;
      while (j < *ncp && !trouve) {
         // Chaîne tab[i] déjà présente
         if (strcmp(res[j], tab[i]) == 0) {
            trouve = true;
         }
         j++;
      }
      // Chaine tab[i] absente --> ajout de la chaîne tab[i] au tableau res
      if (!trouve) {
         int nbChar = strlen(tab[i]) + 1;
         res[*ncp] = (char*)malloc(nbChar*sizeof(char));
         if (res[*ncp] == NULL) {
            printf("copierArgs: Erreur d'allocation mémoire de la chaîne %d\n",*ncp);
            return NULL;
         }
         strcpy(res[*ncp], tab[i]);  // copie profonde!
         (*ncp)++;
      }
   }
   
   // Réajustement de la taille du tableau res
   if (*ncp < n) {
      res = (char**)realloc(res, *ncp * sizeof(char*));
      if (res == NULL)
         printf("copierArgs: Erreur de réallocation mémoire du tableau res\n");
   }
   return res;
}

/**
 * PRE: tab: tableau de n chaînes de caractères
 * POST: les n chaînes de tab sont triées par ordre alphabétique
 *       (algorithme: tri par sélection)
 */
void trier (char** tab, int n) {
   int min; 
   char* tmp; 
   for (int i = 0; i < n-1; i++) {
      min = i;       
      for (int j = i+1; j < n; j++)
         if (strcmp(tab[j],tab[min])<0)
			 min = j;
      if (min != i) {
		  tmp = tab[i];
		  tab[i] = tab[min];
		  tab[min] = tmp;
      }
   }
}

/**
 * PRE: tab: tableau de n chaînes de caractères
 * POST: affiche les chaînes de tab (à raison d'une par ligne,
 *       précédée par leur numéro)
 */
void afficher (char** tab, int n) {
   for (int i = 0; i < n; i++)
      printf("\t%d - '%s'\n", i+1, tab[i]);
}
