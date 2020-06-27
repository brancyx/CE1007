//
//  main.c
//  balanced()
//
//  Created by Brandon Chen on 4/4/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

//CX1007 Data Structures
//Week 11 Solutions (Stack and Queques)

////////////////////////////////////////////////////////////

//#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <stdlib.h>

//////////////////////////////////   linked list //////////////////////////////////////////////

typedef struct _listnode{
    char item;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
    int size;
    ListNode *head;
    ListNode *tail;
} LinkedList;

////////////////////////////////// stack    //////////////////////////////////////////////

typedef struct stack{
    LinkedList ll;
} Stack;

//////////////////////////////////// queue ////////////////////////////////////////////

typedef struct _queue{
    LinkedList ll;
} Queue;

////////////////////////////////////////////////////////////////////////////////
void printList(ListNode *head);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, char value);
int removeNode(LinkedList *ll, int index);



//////////////////////////////////////////////////

void push(Stack *s, char item);
char pop(Stack *s);
char peek(Stack *s);
int isEmptyStack(Stack *s);


//////////////////////////////////////////////////

void enqueue(Queue *q, char item);
char dequeue(Queue *q);
int isEmptyQueue(Queue *s);
char peekQueue(Queue *q);

///////////////////////////////////////////////////////////////

int  balanced(char *expression);

//////////////////////////////////////////////////////////////////
/////

int main()
{
    
    char* expression=NULL;
    int i;
    
    char item;
    Queue q;
    q.ll.head=NULL;
    q.ll.tail=NULL;
    q.ll.size=0;
    
    printf("Enter an expression, terminated by a newline:\n");
    while(1){
        scanf("%c",&item);
        if(item=='\n') break;
        enqueue(&q,item);
    }
    enqueue(&q,'\0');
    expression = (char *)malloc(sizeof(char)*q.ll.size);
    i=0;
    while(!isEmptyQueue(&q)){
        expression[i++] = peekQueue(&q);
        dequeue(&q);
    }
    
    int isbalanced=balanced(expression);
    if (isbalanced==0){
        printf("The expression is balanced.\n");
    }else{
        printf("The expression is not balanced.\n");
    }
    
    if(!expression){
        free(expression);
        expression=NULL;
    }
    return 0;
    
    
}


void push(Stack *s, char item){
    insertNode(&(s->ll), 0, item);
}

char pop(Stack *s){
    char item;
    
    item = ((s->ll).head)->item;
    removeNode(&(s->ll), 0);
    return item;
}

char peek(Stack *s){
    return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s){
    if ((s->ll).size == 0)
        return 1;
    return 0;
}




////////////////////////////////////////////////////////////////////////////////

void enqueue(Queue *q, char item){
    insertNode(&(q->ll), q->ll.size, item);
}

char dequeue(Queue *q){
    char item;
    item = ((q->ll).head)->item;
    removeNode(&(q->ll), 0);
    return item;
}

char peekQueue(Queue *q){
    return ((q->ll).head)->item;
}

int isEmptyQueue(Queue *q){
    if ((q->ll).size == 0)
        return 1;
    return 0;
}



////////////////////////////////////////////////////////////////////////////////

void printList(ListNode *head){
    
    ListNode *temp = head;
    
    if (temp == NULL)
        return;
    
    while (temp != NULL){
        printf("%d ", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){
    
    ListNode *temp;
    
    if (ll == NULL || index < 0 || index >= ll->size)
        return NULL;
    
    temp = ll->head;
    
    if (temp == NULL || index < 0)
        return NULL;
    
    while (index > 0){
        temp = temp->next;
        if (temp == NULL)
            return NULL;
        index--;
    }
    
    return temp;
}

int insertNode(LinkedList *ll, int index, char value){
    
    ListNode *pre, *cur;
    
    if (ll == NULL || index < 0 || index > ll->size + 1)
        return -1;
    
    // If empty list or inserting first node, need to update head pointer
    if (ll->head == NULL || index == 0){
        cur = ll->head;
        ll->head = malloc(sizeof(ListNode));
        ll->tail = ll->head;
        ll->head->item = value;
        ll->head->next = cur;
        ll->size++;
        return 0;
    }
    
    // Inserting as new last node
    if (index == ll->size){
        pre = ll->tail;
        cur = pre->next;
        pre->next = malloc(sizeof(ListNode));
        ll->tail = pre->next;
        pre->next->item = value;
        pre->next->next = cur;
        ll->size++;
        return 0;
    }
    
    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    if ((pre = findNode(ll, index-1)) != NULL){
        cur = pre->next;
        pre->next = malloc(sizeof(ListNode));
        
        if (index == ll->size)
            ll->tail = pre->next;
        
        pre->next->item = value;
        pre->next->next = cur;
        ll->size++;
        return 0;
    }
    
    return -1;
}

int removeNode(LinkedList *ll, int index){
    
    ListNode *pre, *cur;
    
    // Highest index we can remove is size-1
    if (ll == NULL || index < 0 || index >= ll->size)
        return -1;
    
    // If removing first node, need to update head pointer
    if (index == 0){
        cur = ll->head->next;
        free(ll->head);
        ll->head = cur;
        ll->size--;
        
        if (ll->size == 0)
            ll->tail = 0;
        
        return 0;
    }
    
    // Find the nodes before and after the target position
    // Free the target node and reconnect the links
    if ((pre = findNode(ll, index-1)) != NULL){
        
        // Removing the last node, update the tail pointer
        if (index == ll->size - 1){
            ll->tail = pre;
            free(pre->next);
            pre->next = NULL;
        }
        else{
            cur = pre->next->next;
            free(pre->next);
            pre->next = cur;
        }
        ll->size--;
        return 0;
    }
    
    return -1;
}




////////////////////////////////////////////////////////////
//Question 4

int balanced(char *expression){
    
    Stack s;
    s.ll.head = NULL;
    s.ll.tail = NULL;
    s.ll.size = 0;
    
    while (*expression) {
        if (*expression == '(' || *expression == '[' || *expression == '{') {
            push(&s, *expression);
        }
        
        else if (*expression == ')') {
            if (isEmptyStack(&s) || pop(&s) != '(')
                return -1;
        }
        
        else if (*expression == ']') {
            if (isEmptyStack(&s) || pop(&s) != '[')
                return -1;
        }
        
        else if (*expression == '}') {
            if (isEmptyStack(&s) || pop(&s) != '{')
                return -1;
        }
        
        expression++;
    }
    
    if (isEmptyStack(&s))
        return 0;
    else
        return -1;
    
}

////////////////////////////////////////////////////////////////////////////////


