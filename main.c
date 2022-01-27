#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data; // dll for storing data
    struct node *prev;
    struct node *next;
} node;

// create a stack for these lists
typedef struct mainStack
{
    node *list;
    struct mainStack *next;
} mainStack;

// create a character stack for operands
typedef struct charStack
{
    char ch;
    struct charStack *next;
} charStack;

charStack *topChar = NULL;

void pushChar(char c) // push function for character stack
{
    charStack *temp;
    temp = malloc(sizeof(charStack));
    temp->ch = c;
    temp->next = topChar;
    topChar = temp;
    return;
}

// push function for double list
mainStack *topMain = NULL;

void pushMain(node *head) // push function for main stack
{
    mainStack *temp;
    temp = malloc(sizeof(mainStack));
    temp->list = head;
    temp->next = topMain;
    topMain = temp;
    return;
}
node *add_at_end(node *head, int d)
{
    printf("Adding at end\n");
    node *temp;
    node *ptr = NULL;
    temp = malloc(sizeof(node));
    temp->prev = NULL;
    temp->data = d;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
    }
    ptr = head;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    temp->next = NULL;
    temp->prev = ptr;
    ptr->next = temp;
    return head;
}
void destroy(node *head)
{
    node *ptr = head;
    if (head == NULL)
    {
        return;
    }
    else
    {
        while (head != NULL)
        {
            ptr = head;
            head = head->next;
            free(ptr);
        }
    }
}
// for adding we need to pop the lists
node *popList(mainStack *head)
{
    printf("POPPING");
    node *reqList;
    mainStack *ptr;
    ptr = topMain;
    reqList = head->list;
    topMain = topMain->next;
    free(ptr);
    ptr = NULL;
    return reqList;
}

// DISPLAY FUNC NOT WORKING CHK AGAIN
// display the contents of node
void displayDLL(node *head)
{
    printf("I'm in display DLL\n");
    node *ptr = head;
    while (ptr != NULL)
    {
        printf("%d\t", ptr->data);
        ptr = ptr->next;
    }
    return;
}
// display the contents of the entire stack
//  void display(mainStack* head)
//  {
//      mainStack* ptr=head;
//      while(ptr!=NULL)
//      {
//          displayDLL(head->list);
//          printf("\n");
//          ptr=ptr->next;
//      }
//      return;
//  }

int main()
{
    mainStack *head;
    charStack *head1;
    node *head2;
    node *ans;
    int p = 0;
    int i = 0;
    char s[255];
    printf("Enter Expression\n");
    gets(s);
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] - '0' >= 0 && s[i] - '0' <= 9)
        {
            // printf("Adding Number to Stack\n");
            add_at_end(head2, s[i] - '0');
        }
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^' || s[i] == '%')
        {
            // printf("Adding Operator to Stack\n");
            pushChar(s[i]);
        }
        pushMain(head->list);
        destroy(head2);
    }

    ans = popList(head);

    displayDLL(ans);
}
