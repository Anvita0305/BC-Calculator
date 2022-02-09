#include "eval.h"

number *evaluate(number *nos1, number *nos2, char op)
{
    if (op == '+')
    {
        number *result = add(nos1, nos2);
        return result;
    }
    else if (op == '-')
    {
        number *result = sub(nos1, nos2);
        return result;
    }
    else if (op == '*')
    {
        number *result = mult(nos1, nos2);
        return result;
    }
    else if (op == '/')
    {
        number *result = division(nos1, nos2);
        return result;
    }
    else if (op == '^')
    {
        number *result = power(nos1, nos2);
        return result;
    }
    else
    {
        return NULL;
    }
}

int Precedence(char op)
{
    if ((op == '+') || (op == '-'))
        return 1;
    else if ((op == '*') || (op == '/') || (op == '%'))
        return 2;
    else if (op == '^')
        return 3;
    else
        return 4;
}

int Associvity(char op)
{
    if (op == '^') // l->r
        return 1;
    else
        return 0;
}

int isDigit(char c)
{
    int m;
    if (c >= '0' && c <= '9')
    {
        m = 1;
    }
    else
    {
        m = 0;
    }
    return m;
}

int isoperator(char c)
{
    int m = 0;

    if ((c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^'))
    {
        m = 1;
    }
    return m;
}

token getValue(char *expr, int *reset)
{
    static int i = 0;
    if (*reset == 1) // resets the entire eqn
    {
        *reset = 0;
        i = 0;
    }
    number *a = (number *)malloc(sizeof(number));
    initNumber(a);

    char c = expr[i];
    token t;
    int deciPt = 0;

    while (1)
    {
        if (c == '(' || c == ')')
        {
            i++;
            while (expr[i] == ' ')
            {
                i++;
            }
            t.op = c;
            t.type = OPERATOR;
            return t;
        }
        else if (isDigit(c) || expr[i] == '.')
        {
            addAtEnd(a, c);
            int j = i + 1;
            while (isDigit(expr[j]) || expr[j] == '.')
            {
                if (expr[j] == '.')
                {
                    deciPt = 1;
                }
                else
                {
                    addAtEnd(a, expr[j]);
                    if (deciPt == 1)
                    {
                        a->dec++;
                    }
                }
                j++;
            }
            i = j;
            while (expr[i] == ' ')
            {
                i++;
            }
            t.type = OPERAND;
            t.num = a;
            return t;
        }
        else if (isoperator(c))
        {
            t.type = OPERATOR;
            t.op = c;
            i++;
            while (expr[i] == ' ')
            {
                i++;
            }
            return t;
        }
        else if (c == '\0')
        {
            t.type = END;
            return t;
        }
    }
}

number *infix_eval(char *exp)
{
    numStack num_st;
    charStack char_st;
    nodeInit(&num_st);
    charInit(&char_st);

    int reset = 1;

    token t;

    while (1)
    {
        t = getValue(exp, &reset);

        if (t.type == OPERAND)
        {
            nodePush(&num_st, t.num);
        }
        else if (t.type == OPERATOR)
        {
            if (t.op == '(')
            {
                charPush(&char_st, t.op);
            }
            else if (t.op == ')')
            {
                while (charPeek(char_st) != '(')
                {
                    char currchar = charPop(&char_st);
                    number *a, *b;
                    a = nodePop(&num_st);
                    b = nodePop(&num_st);
                    number *result = evaluate(b, a, currchar);
                    nodePush(&num_st, result);
                }
                charPop(&char_st);
            }
            else
            {
                if ((charIsEmpty(&char_st)) || (charPeek(char_st) == '('))
                {
                    charPush(&char_st, t.op);
                }
                else
                {
                    int in_precedence = Precedence(t.op);
                    int top_precedence = Precedence(charPeek(char_st));
                    int pushed = 0;

                    if (top_precedence > in_precedence)
                    {
                        while (top_precedence > in_precedence)
                        {
                            char curr_char = charPop(&char_st);
                            number *a, *b;
                            a = nodePop(&num_st);
                            b = nodePop(&num_st);

                            number *result = evaluate(b, a, curr_char);
                            nodePush(&num_st, result);

                            if ((charIsEmpty(&char_st)) || (charPeek(char_st) == '('))
                            {
                                pushed = 1;
                                charPush(&char_st, t.op);
                                break;
                            }

                            top_precedence = Precedence(charPeek(char_st));
                        }
                        if (pushed == 1)
                            continue;
                    }

                    if (top_precedence == in_precedence)
                    {
                        int asso = Associvity(t.op);

                        if (asso == 1)
                        {
                            charPush(&char_st, t.op);
                        }
                        else
                        {
                            int ispushed = 0;
                            while (top_precedence == in_precedence)
                            {
                                char popped = charPop(&char_st);

                                number *a, *b;
                                a = nodePop(&num_st);
                                b = nodePop(&num_st);

                                number *result = evaluate(b, a, popped);
                                nodePush(&num_st, result);

                                if ((charIsEmpty(&char_st)) || (charPeek(char_st) == '('))
                                {
                                    charPush(&char_st, t.op);
                                    ispushed = 1;
                                    break;
                                }

                                top_precedence = Precedence(charPeek(char_st));
                            }
                            if (ispushed == 0)
                            {
                                charPush(&char_st, t.op);
                            }
                            continue;
                        }
                    }

                    if (in_precedence > top_precedence)
                    {
                        charPush(&char_st, t.op);
                        continue;
                    }
                }
            }
        }
        else if (t.type == END)
        {
            break;
        }
    }

    while (!charIsEmpty(&char_st))
    {
        char currchar = charPop(&char_st);
        number *a, *b;
        a = nodePop(&num_st);
        b = nodePop(&num_st);

        number *result = evaluate(b, a, currchar);
        nodePush(&num_st, result);
    }

    return nodePop(&num_st);
}

int read(char *expr, int len)
{
    int i, openBrac = 0, closeBrac = 0, mask = 0, flag = 0;
    char ch;
    i = 0;
    while (i < len - 1)
    {
        ch = getchar();
        // condition for exit
        if (ch == 'q' || ch == 'Q')
        {
            return 0;
        }
        // checking brackets
        if (ch == '(')
        {
            openBrac++;
        }
        else if (ch == ')')
        {
            closeBrac++;
        }
        if (closeBrac > openBrac)
        {
            flag = 1;
            break;
        }
        if (ch == '\n')
        {
            expr[i++] = '\0';
            mask = 1;
            break;
        }
        else
            expr[i++] = ch;
    }
    if ((flag == 1) || (openBrac != closeBrac))
    {
        printf("Invalid Expression! Please check for Brackets.\n");
        return 0;
    }
    if (mask == 1)
    {
        return i - 1;
    }
    expr[len - 1] = '\0';
    return len - 1;
}