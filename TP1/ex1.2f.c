#include <stdio.h>

int main () {
    int a,b;
    printf("Entrez deux nombres entiers positifs: ");
    scanf("%d%d", &a, &b);
    while (a <= 0 || b <= 0) {
        printf("Entrez deux nombres entiers strictement positifs: ");
        scanf("%d%d", &a, &b);
    }

    if (b > a) {
        int tmp = a;
        a = b;
        b = tmp;
    }

    int q=0;
    int somme=0;
    while (somme+b <= a) {
    	somme+=b;
        q++;
    }
    printf("%d / %d = %d ; reste = %d\n", a, b, q, a-somme);
}
