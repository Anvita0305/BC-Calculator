#include<stdio.h>
#include "eval.h"

int main()
{
    number *res;
    char expr[3000];
    printf("\n");
    printf("For quiting the program click q or Q\n");
    printf("\n");
    while (read(expr, 1000))
    {
        res = infix_eval(expr);
        if (res != NULL)
            printNumber(*res);
        else
            printf("Invalid Expression enter again\n");
    }
    return 0;
}