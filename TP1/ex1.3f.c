#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main () {
    int n;
    printf("Entrez un nombre entier positif: ");
    scanf("%d", &n);

    int fact = 1;
    int i = 2; 
    while (i <= n && fact <= INT_MAX/i) {
        fact *= i;
        i++;
    }
    
    if (i <= n) {
        printf("Error: integer overflow\n");
        exit(EXIT_FAILURE);
    }

    printf("%d! = %d\n", n, fact);
    exit(EXIT_SUCCESS);
}
