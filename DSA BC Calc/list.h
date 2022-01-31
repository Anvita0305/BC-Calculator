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


void initNumber(number *num);					//To initialize the number
void addAtEnd(number *num, char c);			//Append digit at end of number
void printNumber(number num);					//To print the entire number (all digits)
void addInFront(number *num, int n);			//Append at start
int length(number num);						//To find the length of number
void remov(number *num, int pos);				//To remov a digit at an index p inside linked list
void zeroRemove(number *num);					//To remov extra zeros on extreme left and on extreme right
