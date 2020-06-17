//
//  main.c
//  findAr1D
//
//  Created by Brandon Chen on 30/1/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.

// (findAr1D) Write a function findAr1D() that returns the subscript of the first appearance of a target number in an array. For example, if ar = { 3,6,9,4,7,8 }, then findAr1D(6,ar,3) will return 0 where 6 is the size of the array and 3 is the number to be found, and findAr1D(6,ar,9) will return 2. If the required number is not in the array, the function will return -1.


#include <stdio.h>
#define INIT_VALUE -1000

int findAr1D(int size, int ar[], int target);
int main()
{
    int ar[20];
    int size, i, target, result = INIT_VALUE;
    
    printf("Enter array size: \n");
    scanf("%d", &size);
    printf("Enter %d data: \n", size);
    
    for (i=0; i<=size-1; i++)
        scanf("%d", &ar[i]);
    
    printf("Enter the target number: \n");
    scanf("%d", &target);
    
    result = findAr1D(size, ar, target);
    
    if (result == -1)
        printf("findAr1D(): Not found\n");
    else
        printf("findAr1D(): %d", result);
    return 0;
}

int findAr1D(int size, int ar[], int target)
{
    
}
