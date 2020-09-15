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

struct Token
{
   char * lexeme;
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

void printList(struct TokenList * t_list);

const char * readingNumber(const char *src, char * dest);
const char * readingWord(const char * src, char * dest);
const char * readingString(const char * src, char * dest);
const char * readingOpOrDel(const char * src, char * dest);
void addToken(struct TokenList *  tlist, struct Token tok);
struct Token * getToken(struct TokenList * t_list, int index);

enum TOKEN_KEYWORD checkKey(struct Token tok);

bool dot(const char *str);
void space(int length);

int main() {
    Console_clear();
    char code[100] = "float _x = 4.112 * 0.999;\nif (_x > 4) {\n    printf(\"Result: \\\"%s\\\"\\n%d\", \"not\", _x);\n}";
    const char *p = code;
    char buf[100];
    int y = 0;
    struct Token tokens[30];
    bool checkForDot = false;

    int nKey = 3;
    int RowKey = 9;
    int nId = 10;
    int RowId = 14;
    int nLit = 5;
    int RowLit = 49;
    int nDelandop = 10;
    int RowDelandop = 1;

    char keywords[nKey][RowKey + 1];
    char identifires[nId][RowId + 1];
    char literals[nLit][RowLit + 1];
    char delandop[nDelandop][RowDelandop + 1];

    struct StringTable keywords_l = createStringTable(&keywords[0][0], 3, 10);
    addString(&keywords_l, "if");
    addString(&keywords_l, "float");

    struct StringTable identifires_l = createStringTable(&identifires[0][0], 10, 15);
    addString(&identifires_l, "printf");
    
    struct StringTable literals_l = createStringTable(&literals[0][0], 5, 50);

    struct StringTable delandop_l = createStringTable(&delandop[0][0], 10, 3);
    addString(&delandop_l, "*");
    addString(&delandop_l, ";");
    addString(&delandop_l, ",");
    addString(&delandop_l, ")");
    addString(&delandop_l, "(");
    addString(&delandop_l, "}");
    addString(&delandop_l, "{");
    addString(&delandop_l, ">");
    addString(&delandop_l, "=");

    struct TokenList t_list = createTokenTable(&tokens[0], 30);

    while (*p != '\0') {
        if (isspace(*p)) {
            p++;
        } else if (isalpha(*p) || *p == '_') {
            p = readingWord(p, buf);
            struct Token tmp; 
            if (containsString(&keywords_l, buf) == true) {
                tmp.lexeme = findString(&keywords_l, buf);
                tmp.type = TOKEN_KEYWORD;
                if (strcmp(tmp.lexeme, "if") == 0) {
                    tmp.subType = KW_IF;
                } else {
                    tmp.subType = KW_FLOAT;
                }
            } else if (containsString(&identifires_l, buf) == true) {
                tmp.lexeme = findString(&identifires_l, buf);
                tmp.type = TOKEN_IDENTIFIER;
            } else {
                addString(&identifires_l, buf);
                tmp.lexeme = findString(&identifires_l, buf);
                tmp.type = TOKEN_IDENTIFIER;
            }
            addToken(&t_list, tmp);
            y++;
        } else if (isnumber(*p) || *p == '.') {
            p = readingNumber(p, buf);
            struct Token tmp;
            addString(&literals_l, buf);
            tmp.lexeme = findString(&literals_l, buf);
            checkForDot = dot(findString(&literals_l, tmp.lexeme));
            tmp.type = TOKEN_LITERAL;
            if (checkForDot) {
                tmp.subType = LIT_FLOAT;
            } else {
                tmp.subType = LIT_INTEGER;
            }
            addToken(&t_list, tmp);
            y++;
            checkForDot = false;
        } else if (*p == '"') {
            p = readingString(p, buf);
            struct Token tmp;
            addString(&literals_l, buf);
            tmp.lexeme = findString(&literals_l, buf);
            tmp.type = TOKEN_LITERAL;
            tmp.subType = LIT_STRING;
            addToken(&t_list, tmp);
            y++;
        } else if (*p == '>' || *p == '*' || *p == '=' || *p == '(' || *p == ')' || *p == '{' || *p == '}' || *p == ';' || *p == ',') {
            p = readingOpOrDel(p, buf);
            struct Token tmp;
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
            y++;
        } else {
            p++;
        }
    }

    puts(">>>");
    puts(code);
    puts(">>>");
    printList(&t_list);
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
        if (*p == '\"' && *(p - 1) != '\\') {
            p++;
            break;
        }
        *dest = *p;
        dest++;
        p++;
    }
    *dest = '\0';

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



void printList(struct TokenList * t_list) {

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

    for (int i = 0; i < 24; i++) {
        struct Token tok;
        tok = *getToken(t_list, i);
        if (tok.type == TOKEN_KEYWORD) {
            printf("%s", key);
            space(strlen(key));
            if (tok.subType == KW_FLOAT) {
                printf("%s", _fl);
                space(strlen(_fl));
            } else if (tok.subType == KW_IF) {
                printf("%s", _if);
                space(strlen(_if));
            }
        } else if (tok.type == TOKEN_IDENTIFIER) {
            printf("%s", id);
            space(strlen(id));
            printf("%s", id_s);
            space(strlen(id_s));
        } else if (tok.type == TOKEN_OPERATOR) {
            printf("%s", op);
            space(strlen(op));
            if (tok.subType == OP_ASSIGNMENT) {
                printf("%s", op_ass);
                space(strlen(op_ass));
            } else if (tok.subType == OP_MORE) {
                printf("%s", op_mor);
                space(strlen(op_mor));
            } else if (tok.subType == OP_MULT) {
                printf("%s", op_mul);
                space(strlen(op_mul));
            }
        } else if (tok.type == TOKEN_LITERAL) {
            printf("%s", lit);
            space(strlen(lit));
            if (tok.subType == LIT_FLOAT) {
                printf("%s", l_fl);
                space(strlen(l_fl));
            } else if (tok.subType == LIT_INTEGER) {
                printf("%s", l_in);
                space(strlen(l_in));
            } else if (tok.subType == LIT_STRING) {
                printf("%s", l_str);
                space(strlen(l_str));
            }
        } else if (tok.type == TOKEN_DELIMITER) {
            printf("%s", del);
            space(strlen(del));
            if (tok.subType == DEL_FIGURE_LEFTTPAR) {
                printf("%s", del_f_l);
                space(strlen(del_f_l));
            } else if (tok.subType == DEL_FIGURE_RIGHTPAR) {
                printf("%s", del_f_r);
                space(strlen(del_f_r));
            } else if (tok.subType == DEL_KOMA) {
                printf("%s", del_k);
                space(strlen(del_k));
            } else if (tok.subType == DEL_LEFTPAR) {
                printf("%s", del_l);
                space(strlen(del_l));
            } else if (tok.subType == DEL_RIGHTPAR) {
                printf("%s", del_r);
                space(strlen(del_r));
            } else if (tok.subType == DEL_SEMICOLON) {
                printf("%s", del_s);
                space(strlen(del_s));
            }
        }

        printf("\"%s\"\n", tok.lexeme);
    }
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

void space(int length) {
    int q = 0;
    q = 21 - length;

    for(int i = 0; i < q; i++) {
        printf(" ");
    }
}
