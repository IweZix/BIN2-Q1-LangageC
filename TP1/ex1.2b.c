#include <stdio.h>

int main () {
    float x,y;
    printf("Entrez un nombre réel: ");
    scanf("%f", &x);
    printf("Entrez un second nombre réel: ");
    scanf("%f", &y);
    printf("%f * %f = %f\n", x, y, x*y);
}
