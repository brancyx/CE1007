//
//  main.c
//  Week9_Q1
//
//  Created by Brandon Chen on 21/3/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include "stdlib.h"
#include "stdio.h"

////////////////////////////////////////////////////////////

void insert(char *s,int n);
void removes(char *s, int n);

//////////////////////////////////////////////////////////
void main ()
{
    int n;
    char *s;
    int choice;
    
    
    printf("How many characters do you want to input: ");
    scanf("%d", &n);
    
    s=(char *)malloc((n+1)*sizeof(char));
    
    if (s==NULL)
    {
        printf("can't allocate the memory!");
        return;
    }
    
    printf("Input the string:");
    scanf("%s",s);
    
    printf("The string is: %s\n", s);
    
    do
    {
        printf("Do you want to 1-insert or 2-remove or 3-quit?: ");
        scanf("%d",&choice);
        //getchar(); //to clear the return carriage in the buffer
        
        if (choice==1)
            insert(s,n);
        else if (choice==2)
            removes(s,n);
    }while (choice!=3);
    
    
}

//////////////////////////////////////////
void removes(char *s, int n)
{
    int i;
    
    for (i=0; i<n-1; i++) {
        *(s+i) = *(s+i+1);
    }
    *(s+i) = '\0';
    printf("Resulting string: %s\n", s);
}

//////////////////////////////////////////
void insert(char *s, int n)
{
    int i;
    char dummyvariable;
    
    for (i=n-1; i>0; i--) {
        *(s+i) = *(s+i-1);
    }
    *(s+n) = '\0';
    
    printf("What is the character you want to insert: ");
    scanf("\n", &dummyvariable);
    scanf("%c", s);
    printf("Resulting string: %s\n", s);
    
}
