#include <stdio.h>

int main () {
    int a,b;
    printf("Entrez un nombre entier: ");
    scanf("%d", &a);
    printf("Entrez un second nombre entier: ");
    scanf("%d", &b);
    printf("%d * %d = %d\n", a, b, a*b);
}
