#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "operations.h"
#include <limits.h>
#define OPERAND 100
#define OPERATOR 200
#define END 300

typedef struct token
{
    int type;
    number *num;
    char op;
} token;
number *evaluate(number *nos1, number *nos2, char op);
int Precedence(char op);
int Associvity(char op);
int isDigit(char c);
int isoperator(char c);
token getValue(char *expr, int *reset);
number *infix_eval(char *exp);
int read(char *line, int len);