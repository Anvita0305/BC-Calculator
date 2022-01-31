#include <stdlib.h>
#include "stack.h"

// Stack implementation to store number list.
void nodeInit(numStack *head)
{
	*head = NULL;
	return;
}

void nodePush(numStack *head, number *t)
{
	numStack temp;
	temp = (numNode *)malloc(sizeof(numNode));
	temp->num = t;
	temp->next = *head;
	*head = temp;
	return;
}

number *nodePop(numStack *head)
{
	number *t;
	numStack temp;
	t = (*head)->num;
	temp = *head;
	*head = (*head)->next;
	free(temp);
	return t;
}

int nodeIsEmpty(numStack *head)
{
	return *head == NULL;
}

//  Stack implementation to store character Operators.
void charInit(charStack *head)
{
	*head = NULL;
	return;
}

void charPush(charStack *s, char t)
{
	charStack temp;
	temp = (charNode *)malloc(sizeof(charNode));
	temp->a = t;
	temp->p = (*s);
	*s = temp;
}

char charPop(charStack *s)
{
	char t;
	charStack temp;
	temp = (*s);
	t = (*s)->a;
	*s = (*s)->p;
	free(temp);
	return t;
}

char charPeek(charStack s)
{
	return s->a;
}

int charIsEmpty(charStack *s)
{
	return *s == NULL;
}