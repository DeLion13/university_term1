#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <progbase.h>
#include <progbase/console.h>
#include <progbase/canvas.h>
#include <assert.h>

struct Vec2D {
    float x;
    float y;
};

struct Color {
    int red;
    int green;
    int blue;
};

struct Pulsar {
    struct Vec2D loc;
    struct Vec2D msector;
    float puls_rad;
    float maxrad;
    float minrad;
    struct Color puls_c;

    float deltar;
};

struct Ball {
    struct Vec2D loc;
    struct Vec2D sector;
    float rad;
    struct Color strokeColor;

    float rotRad;
    float rotAlpha;
    float rotDeltaAlpha;
};

struct Vec2D getCanvasCentre();

float length(struct Vec2D v);
struct Vec2D negative(struct Vec2D v); 
struct Vec2D add(struct Vec2D a, struct Vec2D b);
struct Vec2D mult(struct Vec2D v, float n);
struct Vec2D norm(struct Vec2D v);
struct Vec2D rotate(struct Vec2D v, float angle);
struct Vec2D create(float x, float y);
float distance(struct Vec2D a, struct Vec2D b);
float angle(struct Vec2D v);
struct Vec2D fromPolar(float angle, float length);
int equals(struct Vec2D a, struct Vec2D b);

struct Ball createBall(int canvasWidth, int canvasHeight, int i, int nBalls);
struct Ball updateBall(struct Ball b, float dt, int i, int nBalls);
struct Pulsar createPulsar(int canvasWidth, int canvasHeight);
struct Pulsar updatePulsar(struct Pulsar p);
void drawBall(struct Ball b, int i);
void drawPulsar(struct Pulsar p);
void drawSector(struct Ball b, struct Pulsar p);

int intRand(int max, int min);
float floatRand(float max, float min);

int mainTest();

int main(int argc, char const * argv[argc]) {

    if (strcmp(argv[1], "-n") == 0) {
        
        int nBalls = atoi(argv[2]);

        Console_clear();
        srand(time(0));
        struct ConsoleSize cs = Console_size();
        int w = cs.columns;
        int h = cs.rows * 2;

        Canvas_setSize(w, h);
        Canvas_invertYOrientation();

        struct Ball balls[nBalls];
        struct Pulsar cen_pulsar;

        cen_pulsar = createPulsar(w, h);


        for (int i = 0; i < nBalls; i++) {
            balls[i] = createBall(w, h, i, nBalls);
        }

        const int oneFrameTime = 5;

        while (1) {
            float dt = oneFrameTime / 1000.0;

            for (int i = 0; i < nBalls; i++) {
                balls[i] = updateBall(balls[i], dt, i, nBalls);
            }

            cen_pulsar = updatePulsar(cen_pulsar);

            Canvas_beginDraw();
            
            for (int i = 0; i < nBalls; i++) {
                struct Ball ball = balls[i];
                drawBall(ball, i);
                drawPulsar(cen_pulsar);
                drawSector(ball, cen_pulsar);
            }

            Canvas_endDraw();

            usleep(oneFrameTime);
        }

        return 0;
    } else if (strcmp(argv[1], "-t") == 0) {
        mainTest();
        return 0;
    }

}

// rand functions

int intRand(int max, int min) {
    int rand_x = rand() % (max - min + 1) + min;

    return rand_x;
}

float floatRand(float max, float min) {
    float rand_x = (rand() / (float) RAND_MAX);

    return min + rand_x * (max - min);
}

// another functions

struct Vec2D getCanvasCentre() {
    struct ConsoleSize cd = Console_size();
    int w = cd.columns;
    int h = cd.rows * 2;
    struct Vec2D cen_d = {w / 2, h / 2};
    return cen_d;
}

float length(struct Vec2D v) {
    float length = 0;

    length = sqrt(v.x * v.x + v.y * v.y);

    return length;
}

struct Vec2D negative(struct Vec2D v) {

    v.x = -v.x;
    v.y = -v.y;

    return v;
}

struct Vec2D norm(struct Vec2D v) {

    float len = 0;

    len = length(v);

    v.x = v.x / len;
    v.y = v.y / len;

    return v;
}

struct Vec2D rotate(struct Vec2D v, float angle) {

    float len = length(v);

    v.x = len * cos(angle);
    v.y = len * sin(angle);

    return v;
}

float distance(struct Vec2D a, struct Vec2D b) {
    float dist = 0;

    dist = sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));

    return dist;
}

float angle(struct Vec2D v) {
    float alpha = 0;

    alpha = atan(v.y/v.x);

    return alpha;
}

int equals(struct Vec2D a, struct Vec2D b) {
    if (a.x == b.x && a.y == b.y) {
        return 0;
    }
    else {
        return 1;
    }
}

struct Vec2D mult(struct Vec2D v, float n) {
    v.x = v.x * n;
    v.y = v.y * n;

    return v;
}

struct Vec2D create(float x, float y) {
   struct Vec2D v = {x, y};
   return v;
}

// !!!

struct Vec2D add(struct Vec2D a, struct Vec2D b) {
    struct Vec2D complex;

    complex.x = a.x + b.x;
    complex.y = a.y + b.y;

    return complex;
}

struct Vec2D fromPolar(float angle, float length) {
    struct Vec2D new_v;

    new_v.x =  length * cos(angle);
    new_v.y = length * sin(angle);

    return new_v;
}

// !!!


// ball and pulsar functions

struct Pulsar createPulsar(int canvasWidth, int canvasHeight) {
    Canvas_setSize(canvasWidth, canvasHeight);

    struct Pulsar cen_pulsar = {
        {canvasWidth / 2, canvasHeight / 2},
    };

    cen_pulsar.puls_c.red = intRand(255, 0);
    cen_pulsar.puls_c.green = intRand(255, 0);
    cen_pulsar.puls_c.blue = intRand(255, 0);
    cen_pulsar.maxrad = intRand(60, 30);
    cen_pulsar.minrad = 5;
    cen_pulsar.puls_rad = cen_pulsar.minrad + 1;
    cen_pulsar.deltar = 0.5;

    return cen_pulsar;
}

struct Ball createBall(int canvasWidth, int canvasHeight, int i, int nBalls) {
    float pi = 3.14159;
    struct Ball ball;

    int r = intRand(15, 10);
    ball.rad = r;

    ball.strokeColor.red = intRand(255, 0);
    ball.strokeColor.green = intRand(255, 0);
    ball.strokeColor.blue = intRand(255, 0);

    ball.rotRad = intRand(50, 15);
    ball.rotAlpha = floatRand(pi, -pi);
    ball.rotDeltaAlpha = 1;

    ball.loc = fromPolar(ball.rotAlpha, ball.rotRad);
    ball.loc = add(getCanvasCentre(), ball.loc);

    return ball;
}

struct Ball updateBall(struct Ball b, float dt, int i, int nBalls) {

    float pi = 3.14159;
    struct Vec2D new_v;
    struct ConsoleSize cs = Console_size();
    int w = cs.columns;
    int h = cs.rows * 2;

    struct Vec2D center = {
        w / 2,
        h / 2,
    };

    new_v = fromPolar(b.rotAlpha + i * 2 * pi / nBalls, b.rotRad);
    b.loc = add(center, new_v);
    b.rotAlpha += b.rotDeltaAlpha * dt;
    
    return b;
}

struct Pulsar updatePulsar(struct Pulsar p) {
    if (p.puls_rad >= p.minrad && p.puls_rad <= p.maxrad) {
        p.puls_rad += p.deltar;
    }

    if (p.puls_rad == p.maxrad || p.puls_rad == p.minrad) {
        p.deltar = - p.deltar;
    }

    if (p.puls_rad == p.minrad) {
        p.maxrad = intRand(60, 30);
    }

    return p;
}

void drawBall(struct Ball b, int i) {
    Canvas_setColorRGB(b.strokeColor.red, b.strokeColor.blue, b.strokeColor.green);
    Canvas_strokeCircle(b.loc.x, b.loc.y, b.rad);
}

void drawPulsar(struct Pulsar p) {
    Canvas_setColorRGB(p.puls_c.red, p.puls_c.blue, p.puls_c.green);
    Canvas_strokeCircle(p.loc.x, p.loc.y, p.puls_rad);
}

void drawSector(struct Ball b, struct Pulsar p) {
    Canvas_setColorRGB(255, 255, 255);

    for (b.sector.x = b.loc.x - b.rad + 1; b.sector.x <= b.loc.x + b.rad - 1; b.sector.x++) {
        for (b.sector.y = b.loc.y - b.rad + 1; b.sector.y <= b.loc.y + b.rad - 1; b.sector.y++) {
            if (pow(b.sector.x - p.loc.x, 2) + pow(b.sector.y - p.loc.y, 2) < pow(p.puls_rad, 2) && pow(b.sector.x - b.loc.x, 2) + pow(b.sector.y  - b.loc.y, 2) < pow(b.rad, 2)) {
                Canvas_putPixel(b.sector.x, b.sector.y);
            }
        }
    }
}

int mainTest() {

    const float pi = 3.14159;
    int dist = 0;
    float alpha = 0;

    struct Vec2D test1 = create(1, 1);
    struct Vec2D test2 = create(-1, -1);
    struct Vec2D test3 = create(2, 2);
    struct Vec2D test4 = create(1, 0);
    struct Vec2D test5 = create(3, 0);
    struct Vec2D test51 = create(0, 3);
    struct Vec2D test6 = create(0, 0);
    struct Vec2D test7 = create(3, 0);
    
    assert(length(test1) < 1.5);
    
    test1 = negative(test1);

    assert(test1.x == test2.x && test1.y == test2.y);

    test1 = negative(test1);
    test1 = add(test1, test2);

    assert(test1.x == 0 && test1.y == 0);

    test3 = norm(test3);

    assert(test3.x < 0.8 && test3.x < 0.8);

    test2 = negative(test2);
    test2 = mult(test2, 3);

    assert(test2.x == 3 && test2.y == 3);

    test4 = rotate(test4, pi / 2);

    assert((int)test4.x == 0 && (int)test4.y == 1);

    dist = distance(test5, test2);

    assert(dist == 3);

    alpha = angle(test5);

    assert((int)alpha == 0);

    alpha = angle(test51);
    assert((int)alpha == pi/2);

    test6 = fromPolar(0, 3);

    assert((int)test6.x == 3 && (int)test6.y == 0);
    assert(equals(test6, test7) == 0);

    printf("Programm works correct!\n");

    return 0;
}
