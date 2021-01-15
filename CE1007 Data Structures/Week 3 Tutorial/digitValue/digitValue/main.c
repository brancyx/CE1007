//
//  main.c
//  digitValue
//
//  Created by Brandon Chen on 27/1/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include <stdio.h>

int digitValue1(int num, int k);
void digitValue2(int num, int k, int * result);
int main(){
    int num, digit, result=-1;
    
    printf("Enter the number: \n");
    scanf("%d", &num);
    printf("Enter k position: \n");
    scanf("%d", &digit);
    printf("digitValue1(): %d\n",  digitValue1(num, digit));
    
    digitValue2(num, digit, &result);
    printf("digitValue2(): %d\n", result);
    return 0; }

int digitValue1(int num, int k)
{
    int digit;
    digit = (num / (10 ^ (k - 1))) % 10;
    return digit;
}

void digitValue2(int num, int k, int *result)
{
    *result = (num / (10 ^ (k - 1))) % 10;
}
