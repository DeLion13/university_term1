#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <progbase.h>
#include <progbase/console.h>

void menu1();
void menu2();
void menu1_functional();
void menu2_functional();
void menu3_functional();
int getColor(char colorCode);

float float_rand( float min, float max ) {
    float scale = rand() / (float) RAND_MAX;
    return min + scale * ( max - min );
}

int main(void) {
    Console_clear();

    while (1) {
        Console_clear();
        printf("1. Array\n2. Matrix\n3. Secret image(for quit press 'q')\n4. Quit\n");
        int key_1 = Console_getChar();

        if(key_1 != '4') {
            switch(key_1) {
                case '1': {
                    menu1_functional();
                    break;
                }
                case '2': {
                    menu2_functional();
                    break;
                }
                case '3': {
                    menu3_functional();
                    break;
                }
                default: {
                    printf("Print number of menu please!\n");
                    Console_clear();
                }
            }
        }
        else {
            break;
        }

    }

    Console_clear();
    return 0;
}

void menu1() {
    printf("1. Random numbers from L to H.\n");
    printf("2. Assign for all element number NULL.\n");
    printf("3. Find maximal element of massive and his number.\n");
    printf("4. Output sum of positive elements.\n");
    printf("5. Change maximal and minimal elements` position.\n");
    printf("6. Increase all elements on your number.\n");
    printf("7. Go to main menu.\n");
    // waiting for answer
}

void menu2() {
    printf("1. Random numbers from L to H.\n");
    printf("2. Assign for all element number NULL.\n");
    printf("3. Find minimal element of massive and his number.\n");
    printf("4. Sum of line by index.\n");
    printf("5. Change maximal and minimal elements` position.\n");
    printf("6. Find element by coordinates and add to him your number.\n");
    printf("7. Go to main menu.\n");
    // waiting for answer
}

void menu1_functional() {
    Console_clear();
    int n = 0;
    while(n <= 0) {
        printf("Print quantity of elements in massive: ");
        scanf("%d", &n);
        if (n > 0) {
            break;
        }
        else {
            Console_clear();
            printf("Incorrect number!\n");
            continue;
        }
    }
    float arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = 0;
    }
    int key_2 = 0;
    float sum = 0;
    int q = 0;
    float maximal = 0;
    int maximal_i = 0;
    float minimal = 0;
    int minimal_i = 0;
    do {
        if (q > 0) {
            key_2 = Console_getChar();

            if (key_2 != '7') {
                switch(key_2) {
                    case '1': {
                        float min = 0;
                        float max = 0;
                        printf("Input lowest number for massive: ");
                        scanf("%f", &min);
                        printf("Input highest number for massive: ");
                        scanf("%f", &max);
                        while(min > max) {
                            Console_clear();
                            printf("Min cannot to be biger than max!\n");
                            printf("Input lowest number for massive: ");
                            scanf("%f", &min);
                            printf("Input highest number for massive: ");
                            scanf("%f", &max);
                        }
                        srand(time(NULL));

                        for (int i = 0; i < n; i++) {
                            arr[i] = float_rand(min, max);
                        }
                        
                        break;
                    }
                    case '2': {
                        for (int i = 0; i < n; i++) {
                            arr[i] = 0;
                        }

                        break;
                    }
                    case '3': {
                        maximal = arr[0];
                        
                        for (int i = 0; i < n; i++) {
                            if (maximal <= arr[i]) {
                                maximal = arr[i];
                                maximal_i = i;
                            }
                        }
                        break;
                    }
                    case '4': {
                        for (int i = 0; i < n; i++) {
                            if (arr[i] > 0) {
                                sum = sum + arr[i];
                            }
                        }
                        break;
                    }
                    case '5': {
                        maximal = arr[0];
                        
                        for (int i = 0; i < n; i++) {
                            if (maximal <= arr[i]) {
                                maximal = arr[i];
                                maximal_i = i;
                            }
                        }
                        
                        minimal = arr[0];

                        for (int i = 0; i < n; i++) {
                            if (minimal >= arr[i]) {
                                minimal = arr[i];
                                minimal_i = i;
                            }
                        }

                        float temp = maximal;
                        arr[maximal_i] = minimal;
                        arr[minimal_i] = temp;
                        break;
                    }
                    case '6': {
                        float delta = 0;
                        printf("Print a number for increase all elements on him: ");
                        scanf("%f", &delta);
                        for (int i = 0; i < n; i++) {
                            arr[i] = arr[i] + delta;
                        }
                        
                        break;
                    }
                }
            }
            else {
                break;
            }
        }

        printf("\n");
        Console_clear();

        menu1();
        printf("\n");
        for (int i = 0; i < n; i++) {
            printf("%2.2f ", arr[i]);
        }
        printf("\n");

        if (key_2 == '4') {
            printf("\nSum is: %.2f\n", sum);
            sum = 0;
        }
        else if (key_2 == '3') {
            printf("\nMaximal element is: %.2f. His index: %d\n", maximal, maximal_i);
        }
        
        q++;

    } while(1);
}

void menu2_functional() {
    Console_clear();
    int key_3 = 0;
    int n = 0;
    int m = 0;

    while(n <= 0 || m <= 0) {
        printf("Input number of lines in your matrix: ");
        scanf("%d", &n);
        printf("Input number of colomns in your matrix: ");
        scanf("%d", &m);

        if (n > 0 && m > 0) {
            break;
        }
        else {
            Console_clear();
            printf("Incorrect number(-s)!\n");
            continue;
        }
    }

    int matrix[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = 0;
        }
    }
    int q = 0;
    int maximal = 0;
    int maximal_i = 0;
    int maximal_j = 0;
    int minimal = 0;
    int minimal_i = 0;
    int minimal_j = 0;
    int sum = 0;
    int line = 0;
    int column = 0;
    int number = 0;
    do {
        if (q > 0) {
            key_3 = Console_getChar();
            if (key_3 != '7') {
                switch(key_3) {
                    case '1': {
                        float min = 0;
                        float max = 0;
                        printf("Input lowest number for massive: ");
                        scanf("%f", &min);
                        printf("Input highest number for massive: ");
                        scanf("%f", &max);
                        while(min > max) {
                            Console_clear();
                            printf("Min cannot to be biger than max!\n");
                            printf("Input lowest number for massive: ");
                            scanf("%f", &min);
                            printf("Input highest number for massive: ");
                            scanf("%f", &max);
                        }
                        srand(time(NULL));

                        for (int i = 0; i < n; i++) {
                            for (int j = 0; j < m; j++) {
                                matrix[i][j] = float_rand(min, max);
                            }
                        }

                        break;
                    }
                    case '2': {
                        for (int i = 0; i < n; i++) {
                            for (int j = 0; j < m; j++) {
                                matrix[i][j] = 0;
                            }
                        }

                        break;
                    }
                    case '3': {
                        minimal = matrix[0][0];
                        for (int i = 0; i < n; i++) {
                            for (int j = 0; j < m; j++) {
                                if (minimal >= matrix[i][j]) {
                                    minimal = matrix[i][j];
                                    minimal_i = i;
                                    minimal_j = j;
                                }
                            }
                        }
                        
                        break;
                    }
                    case '4': {
                        printf("Input index of line (number - 1): ");
                        scanf("%d", &line);
                        while (line < 0 || line >= n) {
                            Console_clear();
                            printf("Incorrect index!\n");
                            printf("Input index of line (number - 1): ");
                            scanf("%d", &line);
                        }
                        for (int i = 0; i < m; i++) {
                            sum = matrix[line][i] + sum;
                        }
                        break;
                    }
                    case '5': {
                        minimal = matrix[0][0];

                        for (int i = 0; i < n; i++) {
                            for (int j = 0; j < m; j++) {
                                if (minimal >= matrix[i][j]) {
                                    minimal = matrix[i][j];
                                    minimal_i = i;
                                    minimal_j = j;
                                }
                            }
                        }

                        maximal = matrix[0][0];

                        for (int i = 0; i < n; i++) {
                            for (int j = 0; j < m; j++) {
                                if (maximal <= matrix[i][j]) {
                                    maximal = matrix[i][j];
                                    maximal_i = i;
                                    maximal_j = j;
                                }
                            }
                        }

                        int temp = minimal;
                        matrix[minimal_i][minimal_j] = maximal;
                        matrix[maximal_i][maximal_j] = temp;
                        
                        break;
                    }
                    case '6': {
                        printf("Input index of line: ");
                        scanf("%d", &line);
                        printf("Input index of column: ");
                        scanf("%d", &column);
                        printf("Input your number: ");
                        scanf("%d", &number);

                        while (line < 0 || line >= n || column < 0 || column >= m) {
                            Console_clear();
                            printf("Incorrect index(-es)!\n");
                            printf("Input index of line: ");
                            scanf("%d", &line);
                            printf("Input index of column: ");
                            scanf("%d", &column);
                            printf("Input your number: ");
                            scanf("%d", &number);
                        }

                        matrix[line][column] = number;

                        break;
                    }
                }
            }
            else {
                break;
            }
        }
        Console_clear();

        menu2();
        printf("\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%8d ", matrix[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        if (key_3 == '3') {
            printf("Minimal element is: %d. His coordinates [%d][%d]\n", minimal, minimal_i, minimal_j);
        }
        else if (key_3 == '4') {
            printf("Sum of line with index %d: %d\n", line, sum);
            sum = 0;
        }

        q++;
    } while (1);
}

int getColor(char colorCode) {
    // colors encoding table (hex code -> console color)
    const char colorsTable[16][2] = {
        {0x0, BG_BLACK},
        {0x1, BG_INTENSITY_BLACK},
        {0x2, BG_RED},
        {0x3, BG_INTENSITY_RED},
        {0x4, BG_GREEN},
        {0x5, BG_INTENSITY_GREEN},
        {0x6, BG_YELLOW},
        {0x7, BG_INTENSITY_YELLOW},
        {0x8, BG_BLUE},
        {0x9, BG_INTENSITY_BLUE},
        {0xa, BG_MAGENTA},
        {0xb, BG_INTENSITY_MAGENTA},
        {0xc, BG_CYAN},
        {0xd, BG_INTENSITY_CYAN},
        {0xe, BG_WHITE},
        {0xf, BG_INTENSITY_WHITE}
    };
    const int tableLength = sizeof(colorsTable) / sizeof(colorsTable[0]);
    for (int i = 0; i < tableLength; i++) 
    {
        char colorPairCode = colorsTable[i][0];
        char colorPairColor = colorsTable[i][1];
        if (colorCode == colorPairCode) 
        {
            return colorPairColor;  // we have found our color
        }
    }
    return 0;  // it's an error
}

void menu3_functional() {
    int key_4 = 0;
    do {
        const char image[28][28] = {
            {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1},
            {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1},
            {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1},
            {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1},
            {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1},
            {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1},
            {0xD,0xD,0xD,0xD,0xD,0xD,0x1,0x1,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0x1,0x1,0xD,0xD,0xD,0xD,0xD,0xD},
            {0xD,0xD,0xD,0xD,0x1,0x1,0x7,0x7,0x1,0x1,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0x1,0x1,0x7,0x7,0x1,0x1,0xD,0xD,0xD,0xD},
            {0xD,0xD,0xD,0xD,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0xD,0xD,0xD,0xD},
            {0xD,0xD,0xD,0xD,0x1,0x1,0x1,0x1,0x0,0x0,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0,0x0,0x1,0x1,0x1,0x1,0xD,0xD,0xD,0xD},
            {0xD,0xD,0xD,0xD,0x1,0x1,0x1,0x1,0x0,0x0,0x1,0x1,0xF,0xF,0xF,0xF,0x1,0x1,0x0,0x0,0x1,0x1,0x1,0x1,0xD,0xD,0xD,0xD},
            {0xD,0xD,0x0,0x0,0x1,0x1,0x1,0x1,0x0,0x0,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0x0,0x0,0x1,0x1,0x1,0x1,0x0,0x0,0xD,0xD},
            {0xD,0xD,0xD,0xD,0x1,0x1,0xF,0xF,0xF,0xF,0xF,0xF,0x3,0x3,0x3,0x3,0xF,0xF,0xF,0xF,0xF,0xF,0x1,0x1,0xD,0xD,0xD,0xD},
            {0xD,0xD,0x0,0x0,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0x3,0x3,0x3,0x3,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0xF,0x0,0x0,0xD,0xD},
            {0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0x4,0x4,0x6,0x6,0x4,0x4,0x4,0x4,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD},
            {0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD},
            {0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0x1,0x1,0xF,0xF,0xF,0xF,0x1,0x1,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD},
            {0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0x1,0x1,0xF,0xF,0xF,0xF,0x1,0x1,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD},
            {0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0x1,0x1,0x1,0x1,0xF,0xF,0xF,0xF,0x1,0x1,0x1,0x1,0xD,0xD,0xD,0xD,0xF,0xF,0xD,0xD},
            {0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0x1,0x1,0x1,0x1,0xF,0xF,0xF,0xF,0x1,0x1,0x1,0x1,0xD,0xD,0xD,0x1,0x1,0xD,0xD,0xD},
            {0xD,0xD,0xD,0xD,0xD,0xD,0xD,0xD,0x1,0x1,0x1,0x1,0xB,0xB,0xB,0xB,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0xD,0xD,0xD,0xD},
            {0xD,0xD,0xD,0xD,0xD,0xD,0xF,0xF,0x1,0x1,0xF,0xF,0xB,0xB,0xB,0xB,0xF,0xF,0xA,0x1,0xB,0xB,0xD,0xD,0xD,0xD,0xD,0xD},
            {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1},
            {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1},
            {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1},
            {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1},
            {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1},
            {0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1}
        };
        Console_clear();

        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                int color = getColor(image[i][j]);
                Console_setCursorAttribute(color);
                printf("  ");
                Console_reset();
            }
            printf("\n");
        }

        key_4 = Console_getChar();  
    } while(key_4 != 'q');
}