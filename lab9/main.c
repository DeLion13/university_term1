#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <progbase.h>
#include <progbase/console.h>
#include <progbase/canvas.h>

enum TokenType {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_LITERAL,
    TOKEN_DELIMITER,
    TOKEN_WHITESPACE,
};

enum TOKEN_KEYWORD {
    KW_FLOAT,
    KW_IF,
};

enum TOKEN_OPERATOR {
    OP_ASSIGNMENT,
    OP_MULT,
    OP_MORE,
};

enum TOKEN_LITERAL {
    LIT_FLOAT,
    LIT_INTEGER,
    LIT_STRING,
};

enum TOKEN_DELIMITER {
    DEL_SEMICOLON,
    DEL_KOMA,
    DEL_LEFTPAR,
    DEL_RIGHTPAR,
    DEL_FIGURE_LEFTTPAR,
    DEL_FIGURE_RIGHTPAR,
};

struct TextPosition 
{ 
    int row; 
    int column;
};

struct Token
{
   char * lexeme;
   struct TextPosition loc;
   enum TokenType type;
   int subType;
};

struct TokenList
{
   struct Token * items;
   size_t capacity;
   size_t count;
};

struct StringTable
{
   char * items;
   size_t capacity;
   size_t count;
   size_t rowCapacity;
};

struct StringTable createStringTable(char *items, int cap, int rowCap);
void addString(struct StringTable * ptable, const char * str);
char *getStringAt(const struct StringTable *ptable, int index);
char *findString(const struct StringTable *ptable, const char *str);
bool containsString(const struct StringTable *ptable, const char *str);

struct TokenList createTokenTable(struct Token *array, int cap);

void printList(struct TokenList * t_list, int y, FILE * filen);
void printList_1(struct TokenList * t_list, int y);
void printNaturalCode(struct TokenList * t_list, int y);

const char * readingSpace(const char *p, char * dest);
const char * readingNumber(const char *p, char * dest);
const char * readingWord(const char * p, char * dest);
const char * readingString(const char * p, char * dest);
const char * readingOpOrDel(const char * p, char * dest);
void addToken(struct TokenList *  tlist, struct Token tok);
struct Token * getToken(struct TokenList * t_list, int index);

enum TOKEN_KEYWORD checkKey(struct Token tok);

bool slashN (const char *str);
bool dot(const char *str);
void space(int length, FILE * filen);
void space_1(int length);

int main(int argc, char const *argv[]) {
    bool ERROR = false;
    bool wasO = false;
    bool wasDot = false;
    bool wasOutFile = false;
    bool wasInFile = false;
    const char * inputFileName;
    const char * outputFileName;

    bool modeList = false;
    bool modeStand = false;

    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            if (isalnum(*argv[i]) && wasO == false && wasInFile == false) {
                for (int j = 0; j < strlen(argv[i]); j++) {
                    if (argv[i][j] == '.') {
                        wasDot = true;
                    }
                }
                if (wasDot == true && argv[i][strlen(argv[i]) - 1] == 't' &&  argv[i][strlen(argv[i]) - 2] == 'x' && argv[i][strlen(argv[i]) - 3] == 't') {
                    inputFileName = argv[i];
                } else {
                    printf("Incorrect input file name!\n");
                    ERROR = true;
                    break;
                }
                wasInFile = true;
            } else if (argv[i][0] == '-') {
                if (argv[i][1] == 'o') {
                    if (wasInFile == true) {
                        wasO = true;
                    } else {
                        ERROR = true;
                        printf("You cannot use -o! Check did you input file name!\n");
                        break;
                    }
                } else if (argv[i][1] == 'l') {
                    if (wasInFile == true) {
                        modeList = true;
                    } else {
                        ERROR = true;
                        printf("You cannot use -l! Check did you input file name!\n");
                        break;
                    }
                }
            } else if (isalnum(*argv[i]) && wasOutFile == false) {
                for (int j = 0; j < strlen(argv[i]); j++) {
                    if (argv[i][j] == '.') {
                        wasDot = true;
                    }
                }
                if (wasDot == true) {
                    outputFileName = argv[i];
                } else {
                    printf("Incorrect input file name!\n");
                    ERROR = true;
                    break;
                }
                wasOutFile = true;
            }
            if (ERROR) {
                break;
            }
        }
    } else {
        modeStand = true;
    }

    if (wasO == true && wasOutFile == false) {
        printf("Unable output file!\n");
        return 0;
    }
    if ((wasO == true && wasInFile == false) || (wasInFile == true && wasOutFile == true && wasO == false)) {
        printf("Incorrect input of arguments!\n");
        return 0;
    }
    if (ERROR) {
        return 0;
    }

    FILE * fin;
    FILE * fout;

    if (modeStand == true) {
        fin = fopen("input.txt", "r");
    } else if (wasInFile == true && wasO == false) {
        modeStand = true;
        fin = fopen(inputFileName, "r");
    } else {
        fin = fopen(inputFileName, "r");
        fout = fopen(outputFileName, "w");
    }
    //

    Console_clear();
    char ch = 0;
    int strokeLen = 100;
    int i_code = 0;
    char code[strokeLen];

    ch = fgetc(fin);
    // reading from file
    while(ch != EOF) {
        code[i_code] = ch;
        ch = fgetc(fin);
        i_code++;
    }


    fclose(fin);
    //

    const char *p = code;
    char buf[120];
    int x_loc = 1;
    int y_loc = 1;
    int y = 0;
    struct Token tokens[40];
    bool checkForDot = false;
    bool checkForSlashN = false;

    int nKey = 3;
    int RowKey = 9;
    int nId = 10;
    int RowId = 14;
    int nLit = 5;
    int RowLit = 49;
    int nDelandop = 10;
    int RowDelandop = 1;
    int nSpace = 15;
    int RowSpace = 10;

    char keywords[nKey][RowKey + 1];
    char identifires[nId][RowId + 1];
    char literals[nLit][RowLit + 1];
    char delandop[nDelandop][RowDelandop + 1];
    char whitespaces[nSpace][RowSpace + 1];

    struct StringTable keywords_l = createStringTable(&keywords[0][0], nKey, RowKey + 1);
    addString(&keywords_l, "if");
    addString(&keywords_l, "float");

    struct StringTable identifires_l = createStringTable(&identifires[0][0], nId, RowId + 1);
    addString(&identifires_l, "printf");
    
    struct StringTable literals_l = createStringTable(&literals[0][0], nLit, RowLit + 1);

    struct StringTable delandop_l = createStringTable(&delandop[0][0], nDelandop, RowDelandop + 1);
    addString(&delandop_l, "*");
    addString(&delandop_l, ";");
    addString(&delandop_l, ",");
    addString(&delandop_l, ")");
    addString(&delandop_l, "(");
    addString(&delandop_l, "}");
    addString(&delandop_l, "{");
    addString(&delandop_l, ">");
    addString(&delandop_l, "=");

    struct StringTable whitespaces_l = createStringTable(&whitespaces[0][0], nSpace, RowSpace + 1);

    struct TokenList t_list = createTokenTable(&tokens[0], 40);

    while (*p != '\0') {
        if (isspace(*p)) {
            const char * tmp_p = p;
            p = readingSpace(p, buf);
            struct Token tmp;
            addString(&whitespaces_l, buf);
            checkForSlashN = slashN(findString(&whitespaces_l, buf));

            tmp.loc.column = x_loc;
            tmp.loc.row = y_loc;
            tmp.lexeme = findString(&whitespaces_l, buf);
            tmp.type = TOKEN_WHITESPACE;

            addToken(&t_list, tmp);
            if (checkForSlashN) {
                y_loc++;
                x_loc = 0;
            }
            x_loc += p - tmp_p;
            y++;
            checkForSlashN = false;
        } else if (isalpha(*p) || *p == '_') {
            const char * tmp_p = p;
            p = readingWord(p, buf);
            struct Token tmp;
            if (containsString(&keywords_l, buf) == true) {

                tmp.loc.column = x_loc;
                tmp.loc.row = y_loc;
                tmp.lexeme = findString(&keywords_l, buf);
                tmp.type = TOKEN_KEYWORD;
                if (strcmp(tmp.lexeme, "if") == 0) {
                    tmp.subType = KW_IF;
                } else {
                    tmp.subType = KW_FLOAT;
                }
            } else if (containsString(&identifires_l, buf) == true) {

                tmp.loc.column = x_loc;
                tmp.loc.row = y_loc;
                tmp.lexeme = findString(&identifires_l, buf);
                tmp.type = TOKEN_IDENTIFIER;

            } else {
                addString(&identifires_l, buf);

                tmp.loc.column = x_loc;
                tmp.loc.row = y_loc;
                tmp.lexeme = findString(&identifires_l, buf);
                tmp.type = TOKEN_IDENTIFIER;
            }
            addToken(&t_list, tmp);
            x_loc += p - tmp_p;
            y++;
        } else if (isnumber(*p) || *p == '.') {
            const char * tmp_p = p;
            p = readingNumber(p, buf);
            struct Token tmp;
            addString(&literals_l, buf);

            tmp.loc.column = x_loc;
            tmp.loc.row = y_loc;
            tmp.lexeme = findString(&literals_l, buf);
            checkForDot = dot(findString(&literals_l, tmp.lexeme));
            tmp.type = TOKEN_LITERAL;
            if (checkForDot) {
                tmp.subType = LIT_FLOAT;
            } else {
                tmp.subType = LIT_INTEGER;
            }

            addToken(&t_list, tmp);
            x_loc += p - tmp_p;
            y++;
            checkForDot = false;
        } else if (*p == '\"') {
            const char * tmp_p = p;
            p = readingString(p, buf);
            struct Token tmp;
            addString(&literals_l, buf);

            tmp.loc.column = x_loc;
            tmp.loc.row = y_loc;
            tmp.lexeme = findString(&literals_l, buf);
            tmp.type = TOKEN_LITERAL;
            tmp.subType = LIT_STRING;

            addToken(&t_list, tmp);
            x_loc += p - tmp_p;
            y++;
        } else if (*p == '>' || *p == '*' || *p == '=' || *p == '(' || *p == ')' || *p == '{' || *p == '}' || *p == ';' || *p == ',') {
            const char * tmp_p = p;
            p = readingOpOrDel(p, buf);
            struct Token tmp;

            tmp.loc.column = x_loc;
            tmp.loc.row = y_loc;
            tmp.lexeme = findString(&delandop_l, buf);
            if (strcmp(tmp.lexeme, "=") == 0) {
                tmp.type = TOKEN_OPERATOR;
                tmp.subType = OP_ASSIGNMENT;
            } else if (strcmp(tmp.lexeme, "*") == 0) {
                tmp.type = TOKEN_OPERATOR;
                tmp.subType = OP_MULT;
            } else if (strcmp(tmp.lexeme, ">") == 0) {
                tmp.type = TOKEN_OPERATOR;
                tmp.subType = OP_MORE;
            } else if (strcmp(tmp.lexeme, ";") == 0) {
                tmp.type = TOKEN_DELIMITER;
                tmp.subType = DEL_SEMICOLON;
            } else if (strcmp(tmp.lexeme, ",") == 0) {
                tmp.type = TOKEN_DELIMITER;
                tmp.subType = DEL_KOMA;
            } else if (strcmp(tmp.lexeme, "(") == 0) {
                tmp.type = TOKEN_DELIMITER;
                tmp.subType = DEL_LEFTPAR;
            } else if (strcmp(tmp.lexeme, ")") == 0) {
                tmp.type = TOKEN_DELIMITER;
                tmp.subType = DEL_RIGHTPAR;
            } else if (strcmp(tmp.lexeme, "{") == 0) {
                tmp.type = TOKEN_DELIMITER;
                tmp.subType = DEL_FIGURE_LEFTTPAR;
            } else if (strcmp(tmp.lexeme, "}") == 0) {
                tmp.type = TOKEN_DELIMITER;
                tmp.subType = DEL_FIGURE_RIGHTPAR;
            }

            addToken(&t_list, tmp);
            x_loc += p - tmp_p;
            y++;
        }
    }

    if (modeStand == true && modeList == false) {
        printNaturalCode(&t_list, y);
        printf("\n");
    } else if (modeList == true && wasInFile == true && wasO == false) {
        printList_1(&t_list, y);
    } else if (wasO == true && modeList == false) {
        printList(&t_list, y, fout);
        fclose(fout);
    } else if (wasO == true && modeList == true) {
        printList(&t_list, y, fout);
        printList_1(&t_list, y);
        fclose(fout);
    }

    return 0;
}

bool dot (const char *str) {
    bool p = false;
    
    for(int i = 0; i < strlen(str); i++) {
        if (str[i] == '.') {
            p = true;
        }
    }

    return p;
}

bool slashN (const char *str) {
    bool p = false;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '\n') {
            p = true;
        }
    }

    return p;
}

const char * readingSpace(const char *p, char * dest) {
    
    while(isspace(*p)) {
        *dest = *p;
        p++;
        dest++;
    }
    *dest = '\0';

    return p;
}

const char * readingNumber(const char *p, char * dest) {
    while(isdigit(*p)) {
        *dest = *p;
        dest++;
        p++;
    }
    if (*p == '.') {
        *dest = *p;
        dest++;
        p++;
        while(isdigit(*p)) {
            *dest = *p;
            dest++;
            p++;
        }
    }
    *dest = '\0';

    return p;
}

const char * readingWord(const char * p, char * dest) {

    while (isalnum(*p) || *p == '_') {
        *dest = *p;
        dest++;
        p++;
    }
    *dest = '\0';

    return p;
}

const char * readingString(const char * p, char * dest) {
    p++;

    while (true) {
        *dest = *p;
        if (*p == '\"' && *(p - 1) != '\\') {
            p++;
            *dest = '\0';
            break;
        }
        dest++;
        p++;
    }

    return p;
}

const char * readingOpOrDel(const char * p, char * dest) {
    bool wasOpOrDel = false;

    while ((*p == '>' || *p == '*' || *p == '=' || *p == '(' || *p == ')' || *p == '{' || *p == '}' || *p == ';' || *p == ',') && wasOpOrDel != true) {
        wasOpOrDel = true;
        *dest = *p;
        dest++;
        p++;
    }

    *dest = '\0';

    return p;
}



void printList(struct TokenList * t_list, int y, FILE * filen) {

    char key[] = "TOKEN_KEYWORD";
    // key
    char _if[] = "KW_IF";
    char _fl[] = "KW_FLOAT";
    //
    char id[] = "TOKEN_IDENTIFIER";
    // ident
    char id_s[] = "";
    //
    char lit[] = "TOKEN_LITERAL";
    // lit
    char l_fl[] = "LIT_FLOAT";
    char l_in[] = "LIT_INTEGER";
    char l_str[] = "LIT_STRING";
    //
    char del[] = "TOKEN_DELIMITER";
    // del
    char del_f_l[] = "DEL_FIGURE_LEFTTPAR";
    char del_f_r[] = "DEL_FIGURE_RIGHTPAR";
    char del_l[] = "DEL_LEFTPAR";
    char del_r[] = "DEL_RIGHTPAR";
    char del_k[] = "DEL_KOMA";
    char del_s[] = "DEL_SEMICOLON";
    //
    char op[] = "TOKEN_OPERATOR";
    // operators
    char op_mul[] = "OP_MULT";
    char op_mor[] = "OP_MORE";
    char op_ass[] = "OP_ASSIGMENT";
    //

    for (int i = 0; i < y; i++) {
        struct Token tok;
        tok = *getToken(t_list, i);
        if (tok.type == TOKEN_KEYWORD) {
            fprintf(filen, "%s", key);
            space(strlen(key), filen);
            if (tok.subType == KW_FLOAT) {
                fprintf(filen, "%s", _fl);
                space(strlen(_fl), filen);
            } else if (tok.subType == KW_IF) {
                fprintf(filen, "%s", _if);
                space(strlen(_if), filen);
            }
        } else if (tok.type == TOKEN_IDENTIFIER) {
            fprintf(filen, "%s", id);
            space(strlen(id), filen);
            fprintf(filen, "%s", id_s);
            space(strlen(id_s), filen);
        } else if (tok.type == TOKEN_OPERATOR) {
            fprintf(filen, "%s", op);
            space(strlen(op), filen);
            if (tok.subType == OP_ASSIGNMENT) {
                fprintf(filen, "%s", op_ass);
                space(strlen(op_ass), filen);
            } else if (tok.subType == OP_MORE) {
                fprintf(filen, "%s", op_mor);
                space(strlen(op_mor), filen);
            } else if (tok.subType == OP_MULT) {
                fprintf(filen, "%s", op_mul);
                space(strlen(op_mul), filen);
            }
        } else if (tok.type == TOKEN_LITERAL) {
            fprintf(filen, "%s", lit);
            space(strlen(lit), filen);
            if (tok.subType == LIT_FLOAT) {
                fprintf(filen, "%s", l_fl);
                space(strlen(l_fl), filen);
            } else if (tok.subType == LIT_INTEGER) {
                fprintf(filen, "%s", l_in);
                space(strlen(l_in), filen);
            } else if (tok.subType == LIT_STRING) {
                fprintf(filen, "%s", l_str);
                space(strlen(l_str), filen);
            }
        } else if (tok.type == TOKEN_DELIMITER) {
            fprintf(filen, "%s", del);
            space(strlen(del), filen);
            if (tok.subType == DEL_FIGURE_LEFTTPAR) {
                fprintf(filen, "%s", del_f_l);
                space(strlen(del_f_l), filen);
            } else if (tok.subType == DEL_FIGURE_RIGHTPAR) {
                fprintf(filen, "%s", del_f_r);
                space(strlen(del_f_r), filen);
            } else if (tok.subType == DEL_KOMA) {
                fprintf(filen, "%s", del_k);
                space(strlen(del_k), filen);
            } else if (tok.subType == DEL_LEFTPAR) {
                fprintf(filen, "%s", del_l);
                space(strlen(del_l), filen);
            } else if (tok.subType == DEL_RIGHTPAR) {
                fprintf(filen, "%s", del_r);
                space(strlen(del_r), filen);
            } else if (tok.subType == DEL_SEMICOLON) {
                fprintf(filen, "%s", del_s);
                space(strlen(del_s), filen);
            }
        } else if (tok.type == TOKEN_WHITESPACE) {
            continue;
        }
        
        fprintf(filen, "|| x: %-3d y: %-3d || \"%s\"\n", tok.loc.column, tok.loc.row, tok.lexeme);
    }
}

void printList_1(struct TokenList * t_list, int y) {

    char key[] = "TOKEN_KEYWORD";
    // key
    char _if[] = "KW_IF";
    char _fl[] = "KW_FLOAT";
    //
    char id[] = "TOKEN_IDENTIFIER";
    // ident
    char id_s[] = "";
    //
    char lit[] = "TOKEN_LITERAL";
    // lit
    char l_fl[] = "LIT_FLOAT";
    char l_in[] = "LIT_INTEGER";
    char l_str[] = "LIT_STRING";
    //
    char del[] = "TOKEN_DELIMITER";
    // del
    char del_f_l[] = "DEL_FIGURE_LEFTTPAR";
    char del_f_r[] = "DEL_FIGURE_RIGHTPAR";
    char del_l[] = "DEL_LEFTPAR";
    char del_r[] = "DEL_RIGHTPAR";
    char del_k[] = "DEL_KOMA";
    char del_s[] = "DEL_SEMICOLON";
    //
    char op[] = "TOKEN_OPERATOR";
    // operators
    char op_mul[] = "OP_MULT";
    char op_mor[] = "OP_MORE";
    char op_ass[] = "OP_ASSIGMENT";
    //

    for (int i = 0; i < y; i++) {
        struct Token tok;
        tok = *getToken(t_list, i);
        if (tok.type == TOKEN_KEYWORD) {
            printf("%s", key);
            space_1(strlen(key));
            if (tok.subType == KW_FLOAT) {
                printf("%s", _fl);
                space_1(strlen(_fl));
            } else if (tok.subType == KW_IF) {
                printf("%s", _if);
                space_1(strlen(_if));
            }
        } else if (tok.type == TOKEN_IDENTIFIER) {
            printf("%s", id);
            space_1(strlen(id));
            printf("%s", id_s);
            space_1(strlen(id_s));
        } else if (tok.type == TOKEN_OPERATOR) {
            printf("%s", op);
            space_1(strlen(op));
            if (tok.subType == OP_ASSIGNMENT) {
                printf("%s", op_ass);
                space_1(strlen(op_ass));
            } else if (tok.subType == OP_MORE) {
                printf("%s", op_mor);
                space_1(strlen(op_mor));
            } else if (tok.subType == OP_MULT) {
                printf("%s", op_mul);
                space_1(strlen(op_mul));
            }
        } else if (tok.type == TOKEN_LITERAL) {
            printf("%s", lit);
            space_1(strlen(lit));
            if (tok.subType == LIT_FLOAT) {
                printf("%s", l_fl);
                space_1(strlen(l_fl));
            } else if (tok.subType == LIT_INTEGER) {
                printf("%s", l_in);
                space_1(strlen(l_in));
            } else if (tok.subType == LIT_STRING) {
                printf("%s", l_str);
                space_1(strlen(l_str));
            }
        } else if (tok.type == TOKEN_DELIMITER) {
            printf("%s", del);
            space_1(strlen(del));
            if (tok.subType == DEL_FIGURE_LEFTTPAR) {
                printf("%s", del_f_l);
                space_1(strlen(del_f_l));
            } else if (tok.subType == DEL_FIGURE_RIGHTPAR) {
                printf("%s", del_f_r);
                space_1(strlen(del_f_r));
            } else if (tok.subType == DEL_KOMA) {
                printf("%s", del_k);
                space_1(strlen(del_k));
            } else if (tok.subType == DEL_LEFTPAR) {
                printf("%s", del_l);
                space_1(strlen(del_l));
            } else if (tok.subType == DEL_RIGHTPAR) {
                printf("%s", del_r);
                space_1(strlen(del_r));
            } else if (tok.subType == DEL_SEMICOLON) {
                printf("%s", del_s);
                space_1(strlen(del_s));
            }
        } else if (tok.type == TOKEN_WHITESPACE) {
            continue;
        }

        printf("\"%s\"\n", tok.lexeme);
    }
}

void printNaturalCode(struct TokenList * t_list, int y) {
    for (int i = 0; i < y; i++) {
        struct Token tok;
        tok = *getToken(t_list, i);
        if (tok.type == TOKEN_KEYWORD) {
            Console_setCursorAttribute(FG_MAGENTA);
        } else if (tok.type == TOKEN_IDENTIFIER) {
            if (strcmp(tok.lexeme, "printf") == 0) {
                Console_setCursorAttribute(FG_MAGENTA);
            } else {
                Console_setCursorAttribute(FG_WHITE);
            }
        } else if (tok.type == TOKEN_OPERATOR) {
            Console_setCursorAttribute(FG_WHITE);
        } else if (tok.type == TOKEN_LITERAL) {
            if (tok.subType == LIT_FLOAT || tok.subType == LIT_INTEGER) {
                Console_setCursorAttribute(FG_GREEN);
            } else if (tok.subType == LIT_STRING) {
                Console_setCursorAttribute(FG_INTENSITY_YELLOW);
            }
        } else if (tok.type == TOKEN_DELIMITER) {
            Console_setCursorAttribute(FG_WHITE);
        }

        if (tok.type == TOKEN_LITERAL && tok.subType == LIT_STRING) {
            printf("\"%s\"", tok.lexeme);
        } else {
            printf("%s", tok.lexeme);
        }
    }

    Console_reset();
}

// lists
struct StringTable createStringTable(char *items, int cap, int rowCap) {
   struct StringTable table;
   table.items = items;
   table.capacity = cap;
   table.count = 0;
   table.rowCapacity = rowCap;
   return table;
}

char *getStringAt(const struct StringTable *ptable, int index) {
   char *p = (*ptable).items;
   p += index * (*ptable).rowCapacity;
   return p;
}

void addString(struct StringTable *ptable, const char *str) {
    int rowIndex = (*ptable).count;
    char *p = ptable -> items;
    p += rowIndex * ptable -> rowCapacity;
    strcpy(p, str);
    (*ptable).count += 1;
}

char *findString(const struct StringTable *ptable, const char *str) {
   for (int i = 0; i < (*ptable).count; i++)
   {
       char *p = getStringAt(ptable, i);
       if (strcmp(p, str) == 0)
       {
           return p;
       }
   }
   return NULL;
}

bool containsString(const struct StringTable *ptable, const char *str) {
   return findString(ptable, str) != NULL;
}

// token list

struct TokenList createTokenTable(struct Token * array, int cap) {
    struct TokenList list;

    list.items = array;
    list.capacity = cap;
    list.count = 0;


    return list;
}

void addToken(struct TokenList * t_list, struct Token tok) {
    int count = t_list -> count;
    t_list -> items[count] = tok;
    t_list -> count += 1;
}

struct Token * getToken(struct TokenList * t_list, int index) {
    struct Token * tok = t_list -> items;
    tok += index;

    return tok;
}

void space(int length, FILE * filen) {
    int q = 0;
    q = 21 - length;

    for(int i = 0; i < q; i++) {
        fprintf(filen, " ");
    }
}

void space_1(int length) {
    int q = 0;
    q = 21 - length;

    for(int i = 0; i < q; i++) {
        printf(" ");
    }
}