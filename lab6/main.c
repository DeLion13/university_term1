#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <progbase.h>
#include <progbase/console.h>
#include <progbase/canvas.h>

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

int main() {
    Console_clear();
    srand(time(0));
    const float pi = 3.14159;
    struct ConsoleSize cs = Console_size();
    int w = cs.columns;
    int h = cs.rows * 2;

    struct Vec2D center = {
        w / 2,
        h / 2,
    };

    Canvas_setSize(w, h);
    Canvas_invertYOrientation();

    const int nBalls = 5;
    struct Ball balls[nBalls];
    struct Pulsar cen_pulsar = {
        {w / 2, h / 2},
    };

    cen_pulsar.puls_c.red = rand() % (255 - 0 + 1) + 0;
    cen_pulsar.puls_c.green = rand() % (255 - 0 + 1) + 0;
    cen_pulsar.puls_c.blue = rand() % (255 - 0 + 1) + 0;
    cen_pulsar.maxrad = rand() % (60 - (30) + 1) + (30);
    cen_pulsar.minrad = 5;
    cen_pulsar.puls_rad = cen_pulsar.minrad + 1;
    cen_pulsar.deltar = 0.5;


    for (int i = 0; i < nBalls; i++) {
        int r = rand() % (15 - 10 + 1) + (10);
        balls[i].rad = r;

        balls[i].strokeColor.red = rand() % (255 - 10 + 1) + 10;
        balls[i].strokeColor.green = rand() % (255 - 10 + 1) + 10;
        balls[i].strokeColor.blue = rand() % (255 - 10 + 1) + 10;

        balls[i].rotRad = rand() % (50 - (15) + 1) + (15);
        balls[i].rotAlpha = (rand() / RAND_MAX) * 2 * pi + (- pi);
        balls[i].rotDeltaAlpha = 1;
    }

    const int oneFrameTime = 5;

    while (1) {
        float dt = oneFrameTime / 1000.0;

        for (int i = 0; i < nBalls; i++) {
            balls[i].loc.x = center.x + balls[i].rotRad * cos(balls[i].rotAlpha + i * 2 * pi / nBalls);
            balls[i].loc.y = center.y + balls[i].rotRad * sin(balls[i].rotAlpha + i * 2 * pi / nBalls);
            balls[i].rotAlpha += balls[i].rotDeltaAlpha * dt;
        }

        if (cen_pulsar.puls_rad >= cen_pulsar.minrad && cen_pulsar.puls_rad <= cen_pulsar.maxrad) {
            cen_pulsar.puls_rad += cen_pulsar.deltar;
        }

        if (cen_pulsar.puls_rad == cen_pulsar.maxrad || cen_pulsar.puls_rad == cen_pulsar.minrad) {
            cen_pulsar.deltar = - cen_pulsar.deltar;
        }

        if (cen_pulsar.puls_rad == cen_pulsar.minrad) {
            cen_pulsar.maxrad = rand() % (60 - (30) + 1) + (30);
        }


        Canvas_beginDraw();
        
        for (int i = 0; i < nBalls; i++) {
            struct Ball ball = balls[i];
            Canvas_setColorRGB(ball.strokeColor.red, ball.strokeColor.blue, ball.strokeColor.green);
            Canvas_strokeCircle(ball.loc.x, ball.loc.y, ball.rad);
            Canvas_setColorRGB(cen_pulsar.puls_c.red, cen_pulsar.puls_c.blue, cen_pulsar.puls_c.green);
            Canvas_strokeCircle(cen_pulsar.loc.x, cen_pulsar.loc.y, cen_pulsar.puls_rad);

            Canvas_setColorRGB(255, 255, 255);

            for (ball.sector.x = ball.loc.x - ball.rad + 1; ball.sector.x <= ball.loc.x + ball.rad - 1; ball.sector.x++) {
                for (ball.sector.y = ball.loc.y - ball.rad + 1; ball.sector.y <= ball.loc.y + ball.rad - 1; ball.sector.y++) {
                    if (pow(ball.sector.x - cen_pulsar.loc.x, 2) + pow(ball.sector.y - cen_pulsar.loc.y, 2) < pow(cen_pulsar.puls_rad, 2) && pow(ball.sector.x - ball.loc.x, 2) + pow(ball.sector.y  - ball.loc.y, 2) < pow(ball.rad, 2)) {
                        Canvas_putPixel(ball.sector.x, ball.sector.y);
                    }
                }
            }
        }

        Canvas_endDraw();

        usleep(oneFrameTime);
    }

    return 0;
}