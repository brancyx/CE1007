//
//  main.c
//  reverseAr1D
//
//  Created by Brandon Chen on 1/2/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include <stdio.h>
void printReverse1(int ar[], int size);
void printReverse2(int ar[], int size);
void reverseAr1D(int ar[], int size);
int main()
{
    int ar[80];
    int size, i;
    printf("Enter array size: \n");
    scanf("%d", &size);
    printf("Enter %d data: \n", size);
    for (i=0; i <= size-1; i++)
        scanf("%d", &ar[i]);
    printReverse1(ar, size);
    printReverse2(ar, size);
    reverseAr1D(ar, size);
    printf("\nreverseAr1D(): ");
    if (size > 0) {
        for (i=0; i<size; i++)
            printf("%d ", ar[i]);
    }
    return 0; }
void printReverse1(int ar[], int size)
{
    int i;
    printf("printReverse1(): ");
    for (i=size-1; i>=0; i--)
    {
        printf("%d ", ar[i]);
    }
}
void printReverse2(int ar[], int size)
{
    int i;
    printf("\nprintReverse2(): ");
    for (i=0; i<size; i++)
    {
        printf("%d ", *(ar+size-1-i));
    }
}
void reverseAr1D(int ar[ ], int size)
{
    int i, temp[size];
    for (i=0; i<size; i++)
    {
        temp[i] = ar[size-1-i];
    }
    for (i=0; i<size; i++)
    {
        *(ar+i) = temp[i];
    }
}
