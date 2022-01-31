#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void initNumber(number *a)
{
	a->head = a->tail = NULL;
	a->dec = 0;
	a->sign = PLUS;
}

void addAtEnd(number *a, char ch)
{
	if(ch < '0' || ch > '9')
		return;
	digit *temp = (digit *)malloc(sizeof(digit));
	if(temp == NULL)
		return;
	temp->num = ch - '0';
	temp->next = NULL;
	if((a->head == NULL) && (a->tail == NULL))
    {
		temp->prev = NULL;
		a->head = temp;
		a->tail = temp;
		return;
	}
	temp->prev = a->tail;
	a->tail->next = temp;
	a->tail = temp;
	return;
}



int length(number c){
	digit *p;
    p = c.head;
	int count = 0;
	while(p != NULL)
	{
		count++;
		p = p->next;
	}

	return count;
}



void addInFront(number *c, int no)
{
	if(no < 0 || no > 9)
		return;
	digit *temp = (digit *)malloc(sizeof(digit));
	if(!temp)
		return;
	temp->num = no;
	temp->prev = NULL;
	if((c->head == NULL) && (c->tail == NULL)){
		temp->next = NULL;
		c->head = c->tail = temp;
		return;
	}
	temp->next = c->head;
	c->head->prev = temp;
	c->head = temp;
	return;
}

void remov(number *a, int pos){
	int i;
	digit *p, *temp;
	if(pos < 0 || pos >= length(*a))
		return;

	p = a->head;

	for(i = 0; i < pos - 1; i++)
		p = p->next;


	if(a->head == NULL)
	{
		return;
	}


	if(length(*a) == 1)
	{
		a->head = a->tail = p = NULL;
		return;
	}

	if(pos == 0)
	{
		p->next->prev = NULL;
		a->head = p->next;
		free(p);
		return;
	}

	if(pos == length(*a) - 1)
	{
		temp = p->next;
		p->next = NULL;
		a->tail = p;
		free(temp);
		return;
	}

	temp = p->next;
	p->next = p->next->next;
	temp->next->prev = p;
	free(temp);
	return;
}



void zeroRemove(number *a)
{
	digit *p = a->head;
	int i, len = length(*a);
	for(i = 0; i < len - a->dec -1; i++)
	{
		if(p->num == 0)
		{
			a->head = p->next;
			p->next = NULL;
			a->head->prev = NULL;
			free(p);
			p = a->head;
		}
		else
		{
			break;
		}
	}
	p = a->tail;
	int decimal = a->dec;
	for(i = 0; i < decimal - 1; i++)
	{
		if(p->num == 0)
		{
			a->tail = p->prev;
			p->prev = NULL;
			a->tail->next = NULL;
			free(p);
			p = a->tail;
			a->dec--;
		}
		else
		{
			break;
		}
	}
	return;
}

void printNumber(number c)
{
	digit *p;
	int pos = 0;
	zeroRemove(&c);
	p = c.head;
	if(c.sign == MINUS)
	{
		printf("-");
		c.sign = PLUS;
	}
	while(p != NULL)
	{
		pos++;
		if(pos == (length(c) - c.dec + 1))
			printf(".");
		printf("%d", p->num);
		p = p->next;
	}
	printf("\n");
}