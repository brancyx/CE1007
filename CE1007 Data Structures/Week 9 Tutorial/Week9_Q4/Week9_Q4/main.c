//
//  main.c
//  Week9_Q4
//
//  Created by Brandon Chen on 23/3/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

// CX1007 Data Structures
// Week 9 Lab Tutorial - DynamicData-Linked Lists
// Template for Q2, Q3, and Q4

//#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

////////////////////////////////////////////////////////////

typedef struct _listnode{
    int item;
    struct _listnode *next;
} ListNode;

//////////////////////////////////////////////////////

int searchList(ListNode *head, int value);

//////////////////////////////////////////////////////

void main()
{
    ListNode *head, *p, *temp;
    int n;
    
    
    head=NULL;
    p=NULL;        // pointing to the last node in the list
    printf("Enter a list of numbers, terminated by the value -1:\n");
    
    ////////////////////////////////////////////////////////////////////
    
    scanf("%d\n", &n);
    while (n != -1) {
        if (head == NULL) {
            head = (ListNode *)malloc(sizeof(ListNode));
            p = head;
        }
        else {
            p->next = (ListNode *)malloc((sizeof(ListNode))); // Create next node
            p = p->next;
        }
        p->item = n;  // Assign integer to address pointed to by p
        p->next=NULL; // Allocate next node address to null to end
        scanf("%d", &n);
    }
    
    printf("Current list: ");
    p=head; //Pointer points to address of head
    while (p != NULL) {
        printf("%d ", p->item); // Pointer points to address of item storing integer
        p=p->next;
    }
    printf("\n");
    
    //////////////////////////////////////////////////////////////////////
    
    //search for a value in the list. Q3
    
    printf("Enter value to search for: ");
    scanf("%d", &n);
    searchList(head,n);
    
    /////////////////////////////////////////////////////////
    
    //free up memory for question 4
    //this part is wrong. It will cause problems.
    /*    p = head;
     while (p!= NULL) {
     free(p);
     p=p->next;
     }
     */
    
    
    // Question 4
    p = head;
    while (p != NULL) {
        temp = p->next;
        free(p);
        p = temp;
    }
    p = temp = NULL;
    /////////////////////////////////////////////////////////
    
}

////////////////////////////////////////////////////////////

int searchList(ListNode *head, int value)
{
    
    ////////////////////////////////////////////////////////////////////
    
    int i=0;
    
    while (head != NULL) {
        if (head->item == value) {
            printf("Value %d found at index %d", value, i);
            return 0;
        }
        else {
            head = head->next;
        }
        i++;
    }
    
    printf("Value %d cannot be found", value);
    return -1;
    
    //////////////////////////////////////////////////////////////////////
}
