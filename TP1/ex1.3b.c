#include <stdio.h>
#include <limits.h>

int main () {
    int n;
    printf("Entrez un nombre entier positif: ");
    scanf("%d", &n);

    int fact = 1;
    for (int i=2; i<=n; i++) {
        fact *= i;
    }

    printf("%d! = %d\n", n, fact);
    printf("INT_MAX = %d\n", INT_MAX);
}

/*

12! =   479.001.600  --> correct, cette valeur est inférieure à INT_MAX = 2.147.483.647
13! = 1.932.053.504  --> faux! car la factorielle de 13 vaut en réalité 6.227.020.800 mais cette valeur est supérieure à INT_MAX

*/
