#include <stdio.h>

int main () {
    int a,b;
    printf("Entrez un nombre entier a: ");
    scanf("%d", &a);
    printf("Entrez un nombre entier b: ");
    scanf("%d", &b);

    printf("\navant permutation: a=%d ; b=%d\n", a, b);
    int tmp = a;
    a = b;
    b = tmp;
    printf("après permutation: a=%d ; b=%d\n", a, b);
}
