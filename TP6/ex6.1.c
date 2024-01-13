#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

bool isPrime(int n);
int* prime_numbers (int n, int* sz);
bool first_prime_numbers (int* t, int sz);

/// PROGRAMME PRINCIPAL

int main() {
    // ex6.1.2
    int sz;
    int *t = prime_numbers(MAX, &sz);
    if (t == NULL) { perror("Error in prime_numbers()"); exit(1); }
    
    printf("There are %d prime numbers less than %d: \n", sz, MAX);
    for(int i = 0; i < sz; i++) {
        printf("\t[%d] %d\n", i+1, t[i]);
    }
    free(t);

    // ex6.1.3
    printf("The fisrt %d prime numbers are: \n", MAX);
    int pn[MAX];
    bool success = first_prime_numbers (pn, MAX);
    if (!success) { perror("Error in first_prime_numbers()"); exit(1); }
    
    for(int i = 0; i != MAX; i++) {
        printf("\t[%d] %d\n", i+1, pn[i]);
    }
}

/// FONCTIONS

/**
* PRE : n : nombre entier positif
* RES : vrai si n est premier ; faux sinon
*/
bool isPrime (int n) {
    if (n<2)
        return false;
    for (int i=2; i<n/2+1; i++) 
        if (n%i == 0)
            return false;
    return true;
}

/** 
* PRE: n >= 2
* POST: sz est égal à la taille (physique et logique) du tableau renvoyé
* RES: un tableau trié contenant tous les nombres premiers plus petits 
*      que n ; NULL si un erreur est survenue
*/
int* prime_numbers (int n, int* sz) {
    int *primes = malloc(n * sizeof(int));
    if (primes == NULL) {
        return NULL;
    }

    *sz = 0;
    for (int i=2; i<=n; i++) {
        if (isPrime(i)) {
            primes[*sz] = i;
            (*sz)++;
        }
    }

    primes = realloc(primes, *sz * sizeof(int));
    return primes;
}

/**
* PRE: t: tableau de longueur sz
* POST: t représente un tableau trié contenant les sz premiers nombres premiers.
* RES: vrai en cas de succès ; faux sinon
*/
bool first_prime_numbers (int* t, int sz) {
    int n = 2; 
    int szr; 
    int* pn = prime_numbers(n, &szr); 

    while (pn != NULL && szr < sz) { 
        n = n * 2;
        free(pn);
        pn = prime_numbers(n, &szr); 
    } 

    if (pn == NULL) 
        return false;

    for(int i = 0; i < sz; i++) {
        t[i] = pn[i];
    }
    free(pn);
    return true;
}
