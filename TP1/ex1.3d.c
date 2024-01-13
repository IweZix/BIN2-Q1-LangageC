#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main () {
    int n;
    printf("Entrez un nombre entier positif: ");
    scanf("%d", &n);

    int fact = 1;
    for (int i=2; i<=n; i++) {
        // tester le dépassement de capacité i*fact > INT_MAX
        // sans effectuer ce calcul en int
        if (fact > INT_MAX/i) {    // (pas une règle absolue car division entière!)
            printf("Error: integer overflow\n");
            exit(EXIT_FAILURE);   // exit(1)
        }

        fact *= i;
    }

    printf("%d! = %d\n", n, fact);
    exit(EXIT_SUCCESS);   // exit(0)
}
