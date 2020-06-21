//
//  main.c
//  Week9_Q2
//
//  Created by Brandon Chen on 21/3/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>

////////////////////////////////////////////////////////////

typedef struct _listnode{
    int item;
    struct _listnode *next;
} ListNode;


void main()
{
    ListNode *head, *p, *temp;
    int n;
    
    
    head=NULL;
    p=NULL;        // pointing to the last node in the list
    printf("Enter a list of numbers, terminated by the value -1:\n");
    
    /////////////////////////////////////////////////////////////////
    
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
    //////////////////////////////////////////////////////////////////
}
