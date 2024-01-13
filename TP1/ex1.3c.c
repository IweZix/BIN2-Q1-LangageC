#include <stdio.h>
#include <limits.h>

int main () {
    int n;
    printf("Entrez un nombre entier positif: ");
    scanf("%d", &n);

    float fact = 1;
    for (int i=2; i<=n; i++) {
        fact *= i;
    }

    printf("%d! = %.0f\n", n, fact);
}

/*

La factorielle de 13 est correcte puisque nous ne sommes plus limités par le codage du type int.

*/