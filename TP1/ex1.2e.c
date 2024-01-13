#include <stdio.h>

int main () {
    int a;
    printf("Entrez un nombre entier strictement positif: ");
    scanf("%d", &a);
    while (a <= 0) {
        printf("Entrez un nombre entier strictement positif: ");
        scanf("%d", &a);
    }

    printf("  1");
    for (int i=2; i<=a/2; i++) {
        if (a%i == 0)
            printf("  %d", i);
    }
    printf("\n");
}
