#include "list.h"

typedef struct numNode
{
	number *num;
	struct numNode *next;
}numNode;
typedef numNode *numStack;

typedef struct charNode
{
	char a;
	struct charNode *p;
}charNode;
typedef charNode *charStack;

//num func
void nodeInit(numStack *s);
void nodePush(numStack *s, number *a);
number *nodePop(numStack *s);
int nodeIsEmpty(numStack *s);

//char func
void charInit(charStack *s);
void charPush(charStack *s, char t);
char charPop(charStack *s);
char charPeek(charStack s);
int charIsEmpty(charStack *s);
