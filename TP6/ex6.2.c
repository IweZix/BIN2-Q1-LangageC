#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>  // parfois inclus dans stdlib.h, selon le compilateur
#include <string.h>
#include <stdbool.h>

#define INVIT_SIZE 60
#define MAX_LONG 27


void impTable (char** chaines, int n);
bool rechercher (char** chaines, int n, char* mot);
int litEtValideChaine (char* inv, char* s, int sz);


int main (int argc, char* argv[]) {
   // tableau des arguments sans le premier élément, le nom du programme
   int nbMots = argc - 1;
   char** tabMot = argv + 1;

   // affichage du tableau des arguments
   printf("Arguments:\n");
   impTable(tabMot, nbMots);

   // recherche de mots lus au clavier
   int nbrAbsent = 0;
   char invite[INVIT_SIZE];
   sprintf(invite, "\nIntroduire des mots d'au plus %i lettres a rechercher :\n", MAX_LONG);
   char ligne[MAX_LONG+2];
   int taille;
   while ((taille = litEtValideChaine(invite, ligne, MAX_LONG+2)) != -1) {
      printf("  '%s'  longueur = %d\n",ligne, taille);

      if (rechercher(tabMot, nbMots, ligne)) {
         printf("  '%s' est present dans la table\n", ligne);
      } else {
         printf("  '%s' est absent de la table\n", ligne);
         nbrAbsent++;
      }
   }

   // affichage des résultats
   printf("\n%d mots ont ete lus et n'etaient pas dans la table\n",nbrAbsent);
}


/**
 * PRE: chaines : tableau de chaînes de caractères de taille n ne contenant pas de chaînes nulles.
 * POST: Les chaînes de caractères de chaines sont affichées sur stdout dans l’ordre
 *       des indices à raison d’une chaine par ligne, précédée du numéro de ligne.
 */
void impTable (char** chaines, int n) {
   for (int i=0; i<n; i++){
      printf("   %d: '%s'\n", i+1, chaines[i]);
   }   
}

/**
 * PRE: chaines: tableau de chaînes de caractères de taille n ne contenant pas de chaînes nulles 
 *      mot: chaîne de caractères non nulle
 * POST: Renvoie vrai si mot se trouve dans le tableau chaines ; faux sinon.
 */
bool rechercher (char** chaines, int n, char* mot) {
   for (int i=0; i<n; i++) {
      if (!strcmp(mot, chaines[i])){
         return true;
      }
   }
   return false;
}

/**
 * PRE: inv : chaine de caracteres
 *      s : tableau de char de taille sz
 * POST: La fonction a affiche le message d'invitation inv sur stdout,
 *       ensuite elle a lu sur stdin une chaine de caracteres d'au plus sz-1 caracteres,
 *       a verifie qu'elle n'est ni vide, ni trop longue et repete▒l'operation
 *       tant qu'une chaine valide n'est pas introduite, puis il a remplace le '\n' par '\0'.
 *       La chaine valide a ete placee dans s.
 * RES: renvoie le nombre de caracteres de la derniere chaine lue ;
 *      -1 si fin de fichier [Ctrl-D] atteinte
 */

 // VERSION 1

int litEtValideChaine (char* inv, char* s, int sz) {
   // affichage de l'invite de lecture
   printf("%s", inv);

   while (fgets(s, sz, stdin) != NULL) {
      // traitement d'une ligne vide
      if (strlen(s) == 1) {
         printf("Chaine vide. Recommencez.\n");
         continue;
      }

      // traitement d'une ligne trop longue
      if (s[strlen(s)-1] != '\n') {
         printf("Ligne trop longue. Recommencez.\n");
         // vidage du buffer de lecture bloc par bloc
         while (fgets(s, sz, stdin) && s[strlen(s)-1] != '\n') ;
         // OU vidage du buffer de lecture caractere par caractere
         //while (getchar() != '\n');
         continue;
      }

      // chaine valide: suppression de '\n' et renvoi du nombre de caracteres de la chaine
      s[strlen(s)-1] = '\0';
      return strlen(s);
   }

   // traitement de EOF
   return -1;
}

// VERSION 2: traitement du cas de base plus clair
/*
int litEtValideChaine (char* inv, char* s, int sz) {
   // affichage de l'invite de lecture
   printf("%s", inv);

   while (true) {
      if (!fgets(s, sz, stdin))
         // traitement de EOF
         return -1;

      if (strlen(s) == 1) {
         // traitement d'une ligne vide
         printf("Chaine vide. Recommencez.\n");
         continue;
      }

      if (s[strlen(s)-1] != '\n') {
         // traitement d'une ligne trop longue
         printf("Ligne trop longue. Recommencez.\n");
         // vidage du buffer de lecture bloc par bloc
         while (fgets(s, sz, stdin) && s[strlen(s)-1] != '\n') ;
         // OU vidage du buffer de lecture caractere par caractere
         //while (getchar() != '\n');
         continue;
      }

      // chaine valide: suppression de '\n' et 
      // renvoi du nombre de caracteres de la chaine
      s[strlen(s)-1] = '\0';
      return strlen(s);
   }
}
*/