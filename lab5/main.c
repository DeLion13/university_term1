#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <progbase.h>
#include <progbase/console.h>

void menu1();
void menu2();
void menu1_functional();
void menu2_functional();
void menu3_functional();

void clear() {
    while (getchar() != '\n');
}

int conReadLine(char str[], int maxBufLen) {
    fgets(str, maxBufLen, stdin);
    int bufLength = strlen(str);
    if (str[bufLength - 1] == '\n') {
        str[bufLength - 1] = '\0';
        bufLength -= 1;
    }
    else {
        for (char ch; (ch = getchar()) != '\n';) {
        }
    }
    return bufLength;
}

int main(void) {
    Console_clear();

    while (1) {
        Console_clear();
        printf("1. Characters\n2. String\n3. Text\n4. Quit");
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
    printf("1. Alphanumeric\n");
    printf("2. Alphabetic (lowercase)\n");
    printf("3. Alphabetic (uppercase)\n");
    printf("4. Alphabetic (all)\n");
    printf("5. Decimal digit\n");
    printf("6. Hexadecimal digit\n");
    printf("7. Punctuation\n");
    printf("0. < Back\n");
}

void menu2() {
    printf("1. Fill in the string symbols from console\n");
    printf("2. Clear string (length = 0)\n");
    printf("3. Output understring from your position and with your length\n");
    printf("4. Output understring that divide by your symbol\n");
    printf("5. The biggest word\n");
    printf("6. Output all integer numbers\n");
    printf("7. Output sum of all float numbers\n");
    printf("0. < Back\n");
}

void menu1_functional() {
    Console_clear();
    int key_2 = 0;
    int q = 0;
    do {
        Console_clear();
        menu1();
        if (q > 0) {
            if (key_2 != '0') {
                switch(key_2) {
                    case '1': {
                        for (int i = 33; i <= 126; i++) {
                            if (isalnum(i)) {
                                printf("%c ", i);
                            }
                        }

                        break;
                    }
                    case '2': {
                        for (int i = 97; i <= 122; i++) {
                                printf("%c ", i);
                        }

                        break;
                    }
                    case '3': {
                        for (int i = 65; i <= 90; i++) {
                                printf("%c ", i);
                        }

                        break;
                    }
                    case '4': {
                        for (int i = 65; i <= 122; i++) {
                            if (isalpha(i)) {
                                printf("%c ", i);
                            }
                        }

                        break;
                    }
                    case '5': {
                        for (int i = 48; i <= 57; i++) {
                            printf("%c ", i);
                        }

                        break;
                    }
                    case '6': {
                        for (int i = 33; i <= 126; i++) {
                            if (isxdigit(i)) {
                                printf("%c ", i);
                            }
                        }

                        break;
                    }
                    case '7': {
                        for (int i = 33; i <= 126; i++) {
                            if (ispunct(i)) {
                                printf("%c ", i);
                            }
                        }
                        break;
                    }
                }
            }
            else {
                break;
            }
        }
        key_2 = Console_getChar();
        
        q++;
    } while(1);
}

void menu2_functional() {
    srand(time(0));
    Console_clear();
    int key_3 = 0;
    int q = 0;
    int random = 0;
    printf("Enter maximal quantity of elements: ");
    int bufLen = 0;
    scanf("%d", &bufLen);
    while(bufLen < 0) {
        Console_clear();
        printf("Incorrect number!\n");
        printf("Enter maximal quantity of elements: ");
        scanf("%d", &bufLen);
        if (bufLen > 0) {
            break;
        }
    }
        
    char buf[bufLen];
    char buf2[bufLen];
    clear();
    for (int i = 0; i <= bufLen; i++) {
        if (i < bufLen) {
                random = rand() % ((126 - 33 + 1) + 33);
                if (isgraph(random)) {
                    buf[i] = random;
                }
                else {
                    i = i - 1;
                } 
        }
        else {
            buf[i] = '\0';
        }
    }
    for (int i = 0; i <= bufLen; i++) {
        if (i < bufLen) {
                random = rand() % ((126 - 33 + 1) + 33);
                if (isgraph(random)) {
                    buf2[i] = random;
                }
                else {
                    i = i - 1;
                } 
        }
        else {
            buf2[i] = '\0';
        }
    }

    do {
        Console_clear();
        menu2();
    
        if (q > 0) {
            if (key_3 != '0') {
                switch(key_3) {
                    case '1': {
                        if (bufLen == 0 || buf[0] == '\0') {
                            printf("Your quantity is 0. Enter maximal quantity of elements: ");
                            scanf("%d", &bufLen);
                            while(bufLen <= 0) {
                                Console_clear();
                                printf("Incorrect number!\n");
                                printf("Your quantity is 0. Enter maximal quantity of elements: ");
                                scanf("%d", &bufLen);
                                if (bufLen > 0) {
                                    menu2();
                                    break;
                                }
                            }
                            clear();
                            printf("Enter string: ");
                            int strLen = conReadLine(buf, bufLen + 1);
                            printf("Entered (%d): \"%s\"", strLen, buf);
                            puts("\n");
                        }
                        else {
                            printf("Enter string: ");
                            int strLen = conReadLine(buf, bufLen + 1);
                            printf("Entered (%d): \"%s\"", strLen, buf);
                            puts("\n");
                        }

                        break;
                    }
                    case '2': {
                        buf[0] = '\0';
                        bufLen = strlen(buf);
                        printf("Entered (%d): \"%s\"", bufLen, buf);
                        puts("\n");

                        break;
                    }
                    case '3': {
                        // incorrect
                        int pos = 0;
                        int len = 0;
                        printf("Input your position: ");
                        scanf("%d", &pos);
                        printf("and length: ");
                        scanf("%d", &len);
                        char temp_string[len + 1];
                        temp_string[len] = '\0';

                        strncpy(temp_string, buf + pos, len);
                        
                        if (pos + len <= strlen(buf) && pos >= 0 && pos <= strlen(buf) && len >= 0) {
                            strncpy(temp_string, buf + pos, len);
                            printf("Your string: \"%s\"", temp_string);
                        }
                        else {
                            printf("Incorrect position or length!");
                        }

                        clear();
                        break;
                    }
                    case '4': {
                        printf("Input your symbol: ");
                        char cut = 0;
                        scanf("%c", &cut);
                        clear();
                        int tmpI = 0;
                        char tmpStr[bufLen];

                        for (int i = 0; ; i++) {
                            char ch = buf[i];
                            if (ch == cut || ch == '\0') {
                                if (tmpI != 0) {
                                    tmpStr[tmpI] = '\0';
                                    printf("Understring: '%s'\n", tmpStr);
                                    tmpI = 0;
                                }
                                if (ch == '\0') {
                                    break;
                                }
                            }
                            else {
                                tmpStr[tmpI] = ch;
                                tmpI += 1;
                            }
                        }
                        
                        break;
                    }
                    case '5': {
                        int tmpI2 = 0;
                        char tmpStr2[bufLen];
                        char max_str[bufLen];
                        int max_len = 0;


                        for (int i = 0; i < strlen(buf); i++) {
                            if (isalpha(buf[i]) && buf[i] != '\0') {
                                tmpStr2[tmpI2] = buf[i];
                                tmpI2++;
                            }
                            else {
                                tmpStr2[tmpI2] = '\0';
                                if (strlen(tmpStr2) > max_len) {
                                    strcpy(max_str, tmpStr2);
                                    max_len = strlen(tmpStr2);
                                }
                                tmpI2 = 0;
                            }
                        }

                        printf("Your biggest word is: '%s'", max_str);

                        break;
                    }
                    case '6': {
                        int tmpI3 = 0;
                        char tmpStr3[bufLen];

                        for (int i = 0; ; i++) {
                            char ch = buf[i];
                            if (isdigit(ch)) {
                                tmpStr3[tmpI3] = ch;
                                tmpI3 += 1;
                            }
                            else {
                                if (tmpI3 != 0) {
                                    tmpStr3[tmpI3] = '\0';
                                    printf("Integer: '%s'\n", tmpStr3);
                                    tmpI3 = 0;
                                }
                                if (ch == '\0') {
                                    break;
                                }
                            }
                        }

                        break;
                    }
                    case '7': {
                        int tmpI4 = 0;
                        char tmpStr4[bufLen];
                        double sum = 0;

                        for (int i = 0; ; i++) {
                            char ch = buf[i];

                            if (isdigit(ch)) {
                                tmpStr4[tmpI4] = ch;
                                tmpI4 += 1;
                            }
                            else if (ch == '.' && strchr(tmpStr4, '.') - &tmpStr4[0] < 0) {
                                tmpStr4[tmpI4] = ch;
                                tmpI4 += 1;
                            }
                            else {
                                tmpStr4[tmpI4] = '\0';

                                if (tmpI4 > 0 && strchr(tmpStr4, '.') - &tmpStr4[0] >= 0) {
                                    if (tmpStr4[0] != '.' && tmpStr4[strlen(tmpStr4)] != '.') {
                                        sum += atof(tmpStr4);
                                    }
                                    else if (tmpStr4[0] == '.') {
                                        char tmpStr4_2[strlen(tmpStr4) + 2];

                                        for (int i = strlen(tmpStr4) + 1; i >= 1; i--) {
                                            tmpStr4_2[i] = tmpStr4[i - 1];
                                        }
                                        
                                        tmpStr4_2[0] = '0';
                                        tmpStr4_2[strlen(tmpStr4_2)] = '\0';
                                        sum += atof(tmpStr4_2);
                                    }
                                    if (buf[i] == '.') {
                                        i--;
                                    }
                                }
                                tmpI4 = 0;
                                tmpStr4[0] = '\0'; 

                                if (ch == '\0') {
                                    break;
                                }
                            }
                        }

                        printf("\nSum = %.2f", sum);
                        sum = 0;

                        break;
                    }
                }
            }
            else {
                break;
            }
        }
        
        printf("\nString in memory: ");
        puts(buf);
        key_3 = Console_getChar();
        q++;
    } while(1);
}

void menu3_functional() {
    Console_clear();
    char text[] = {"Anyone who reads Old and Middle English literary texts will be familiar with the mid-brown volumes of the EETS, with the symbol of Alfred's jewel embossed on the front cover. Most of the works attributed to King Alfred or to Aelfric, along with some of those by bishop Wulfstan and much anonymous prose and verse from the pre-Conquest period, are to be found within the Society's three series; all of the surviving medieval drama, most of the Middle English romances, much religious and secular prose and verse including the English works of John Gower, Thomas Hoccleve and most of Caxton's prints all find their place in the publications. Without EETS editions, study of medieval English texts would hardly be possible."};
    char temp_text[100];
    int q = 1;
    strncpy(temp_text, text, 100);

    while(1) {
        Console_clear();
        for (int i = 0; i < 100; i++) {
            printf("%c", temp_text[i]);
        }
        printf("\n");
        if (q == 1) {
            printf("%d -> %d 'd'\n", q, q + 1);
        }
        else if (q == 8) {
            printf("'a' %d <- %d\n", q - 1, q);
        }
        else {
            printf("'a' %d <- %d -> %d 'd'\n", q - 1, q, q + 1);
        }
        printf("For out press 'q'.\n");
        int page = Console_getChar();

        if(page != 'q') {
            switch(page) {
                case 'a': {
                    if (q > 1) {
                        temp_text[0] = '\0';
                        q--;
                        strncpy(temp_text, text + (q - 1) * 100, 100);
                    }
                    break;
                }
                case 'd': {
                    if (q < 8) {
                        temp_text[0] = '\0';
                        q++;
                        strncpy(temp_text, text + (q - 1) * 100, 100);
                    }
                    break;
                }
                default: {
                    break;
                }
            }
        }
        else {
            Console_clear();
            break;
        }
    }
}