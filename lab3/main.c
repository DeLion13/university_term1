#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <progbase.h>
#include <progbase/console.h>

void drawLine(int x0, int y0, int x1, int y1, char ch);

int main() {
    Console_clear();
    // borders
    int cx0 = 2;
    int cy0 = 2;
    int cw = 80;
    int ch = 40;
    int cx = 0;
    int cy = 0;
    // rectangle
    int ax0 = 5;
    int ay0 = 5;
    int aw = 20;
    int ah = 10;
    int ax = 0;
    int ay = 0;
    int s_step = 1;
    // line
    int bx0 = 40;
    int by0 = 20;
    float ba = 1;
    float a_step = 0.075;

    do {
        // calculating of line function arguments
        float k = tan(ba);
        float b = by0 - k * bx0;

        // coordinates of cross
        int zx1 = (cy0- b) / k;
        int zy1 = cy0;
        int zx2 = (ch + cy0 - b) / k;
        int zy2 = ch + cy0;
        int zx3 = cx0;
        int zy3 = b;
        int zx4 = cw + cx0;
        int zy4 = (cw + cx0) * k + b;
        int zx_1 = 0;
        int zy_1 = 0;
        int zx_2 = 0;
        int zy_2 = 0;

        // filtering of crosslines
        if (zx1 >= cx0 && zx1 <= (cx0 + cw) && zy1 >= cy0 && zy1 <= (cy0 + ch)) {
            if (zx2 >= cx0 && zx2 <= (cx0 + cw) && zy2 >= cy0 && zy2 <= (cy0 + ch)) {
                zx_1 = zx1;
                zy_1 = zy1;
                zx_2 = zx2;
                zy_2 = zy2;
            }
            else if (zx3 >= cx0 && zx3 <= (cx0 + cw) && zy3 >= cy0 && zy3 <= (cy0 + ch)) {
                zx_1 = zx1;
                zy_1 = zy1;
                zx_2 = zx3;
                zy_2 = zy3;
            }
            else {
                zx_1 = zx1;
                zy_1 = zy1;
                zx_2 = zx4;
                zy_2 = zy4;
            }
        }
        else if (zx2 >= cx0 && zx2 <= (cx0 + cw) && zy2 >= cy0 && zy2 <= (cy0 + ch)) {
            if (zx3 >= cx0 && zx3 <= (cx0 + cw) && zy3 >= cy0 && zy3 <= (cy0 + ch)) {
                zx_1 = zx2;
                zy_1 = zy2;
                zx_2 = zx3;
                zy_2 = zy3;
            }
            else {
                zx_1 = zx2;
                zy_1 = zy2;
                zx_2 = zx4;
                zy_2 = zy4;
            }
        }
        else {
            zx_1 = zx3;
            zy_1 = zy3;
            zx_2 = zx4;
            zy_2 = zy4;
        }
        // draw borders
        for (cx = cx0; cx <= (cx0 + cw); cx += 1) {
            cy = cy0;
            Console_setCursorPosition(cy, cx);
            printf(":");
            cy = cy0 + ch;
            Console_setCursorPosition(cy, cx);
            printf(":");
        }
        for (cy = cy0; cy <= cy0 + ch; cy += 1) {
            cx = cx0;
            Console_setCursorPosition(cy, cx);
            printf(":");
            cx = cx0 + cw;
            Console_setCursorPosition(cy, cx);
            printf(":");
        }

        // draw rectangle
        for (ay = ay0; ay <= (ay0 + ah); ay++) {
            for (ax = ax0; ax <= (ax0 + aw); ax++) {
                if (ay < k * ax + b) {
                    Console_setCursorAttribute(BG_INTENSITY_CYAN);
                }
                else {
                    Console_setCursorAttribute(BG_INTENSITY_YELLOW);
                }
                    Console_setCursorPosition(ay, ax);
                    printf(" ");
                    Console_reset();
            }
        }
        // draw line
        drawLine(zx_1, zy_1, zx_2, zy_2, '*');

        int key = Console_getChar();
        Console_clear();

        if (key != 32) {
            switch(key) {
                case 'w': {
                    if (ay0 > cy0 + 1) {
                        ay0 -= s_step;
                        break;
                    }
                    else {
                        break;
                    }
                }
                case 's': {
                    if (ay0 + ah < cy0 + ch - 1) {
                        ay0 += s_step;
                        break;
                    }
                    else {
                        break;
                    }
                }
                case 'a': {
                    if (ax0 > cx0 + 1) {
                        ax0 -= s_step;
                        break;
                    }
                    else {
                        break;
                    }
                }
                case 'd': {
                    if (ax0 + aw < cx0 + cw - 1) {
                        ax0 += s_step;
                        break;
                    }
                    else {
                        break;
                    }
                }
                case 'u': {
                    ba -= a_step;
                    break;
                }
                case 'o': {
                    ba += a_step;
                    break;
                }
            }
        }
        else {
            break;
        }
    } while(1);

    Console_reset();
    printf("\n");
    return 0;
}

void drawLine(int x0, int y0, int x1, int y1, char ch) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x1 >= x0 ? 1 : -1;
    int sy = y1 >= y0 ? 1 : -1;

    if (x0 > 0 && y0 > 0) {
        Console_setCursorPosition(y0, x0);
        putchar(ch);
    }

    if (dy <= dx) {
        int d = (dy << 1) - dx;
        int d1 = dy << 1;
        int d2 = (dy - dx) << 1;
        for(int x = x0 + sx, y = y0, i = 1; i <= dx; i++, x += sx) {
            if ( d > 0) {
                d += d2;
                y += sy;
            }
            else {
                d += d1;
            }
            // draw point
            if (y > 0 && x > 0) {
                Console_setCursorPosition(y, x);
                putchar(ch);
            }
        }
    }
    else {
        int d = (dx << 1) - dy;
        int d1 = dx << 1;
        int d2 = (dx - dy) << 1;
        for(int y = y0 + sy, x = x0, i = 1; i <= dy; i++, y += sy) {
            if ( d > 0) {
                d += d2;
                x += sx;
            }
            else {
                d += d1;
            }
            // draw point
            if (x > 0 && y > 0) {
                Console_setCursorPosition(y, x);
                putchar(ch);
            }
        }
    }
}