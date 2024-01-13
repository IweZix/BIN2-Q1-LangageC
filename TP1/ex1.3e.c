#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main () {
    int n;
    printf("Entrez un nombre entier positif: ");
    scanf("%d", &n);

    // initialisation
    int fact = 1;
    int i = 2; 
    // condition
    while (i <= n) {  
        if (fact > INT_MAX/i) {
            printf("Error: integer overflow\n");
            exit(EXIT_FAILURE);
        }

        fact *= i;
        // adaptation
        i++;
    }

    printf("%d! = %d\n", n, fact);
    exit(EXIT_SUCCESS);
}