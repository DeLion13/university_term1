#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
    float x = 0;
    float y = 0;
    const float xmin = -10;
    const float xmax = 10;
    const float delta = 0.5;
    x = xmin;

    while (x <= xmax) {
        if (x > -3 && x <= 3 && x != 0) {
            y = 0.4 * (1/tan(x)) - 2;
            printf("y(%f) = %f\n", x, y);
        }
        else if (x == 0) {
            printf("y(%f) = ERROR\n", x);
        }
        else {
            y = 3 * sin(2 * x) - (2 / x);
            printf("y(%f) = %f\n", x, y);
        }
        x = x + delta;
    }

    return 0;
}