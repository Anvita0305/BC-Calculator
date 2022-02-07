#include "eval.h"

int main()
{
    number *r;
    char expr[3000];
    printf("For quiting the program click q or Q\n");
    printf("\n");
    while (read(expr, 3000))
    {
        r = infix_eval(expr);
        if (r != NULL)
            printNumber(*r);
        else
            printf("Invalid  Expression\n");
    }
    return 0;
}