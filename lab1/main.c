#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    float x = 0;
    printf("Print x: ");
    scanf("%f", &x);
    float y = 0;
    printf("Print y: ");
    scanf("%f", &y);
    float z = 0;
    printf("Print z: ");
    scanf("%f", &z);
    float a = 0;
    float a0 = 0;
    float a1 = 0;
    float a2 = 0;

    a0 = pow(x, y + 1)/pow(x - y, 1 / z);
    a1 = (5 * y) + (z / x);
    a2 = pow(3 + sin(y), cos(x) / (z + fabs(x - y)));
    a = a0 + a1 + a2;

    printf("x = %.3f\n", x);
    printf("y = %.3f\n", y);
    printf("z = %.3f\n", z);
    printf("a0 = %.3f\n", a0);
    printf("a1 = %.3f\n", a1);
    printf("a2 = %.3f\n", a2);
    printf("a = %.3f\n", a);

    return 0;
}