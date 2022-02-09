#define PLUS 1
#define MINUS -1

typedef struct digit
{
    struct digit *prev;
	int num;
	struct digit *next;
}digit;

typedef struct number
{
	int sign, dec;
	digit *head, *tail;
}number;


void initNumber(number *num);					
void addAtEnd(number *num, char c);			
void printNumber(number num);					
void addInFront(number *num, int n);			
int length(number num);						
void remov(number *num, int pos);				
void zeroRemove(number *num);					
