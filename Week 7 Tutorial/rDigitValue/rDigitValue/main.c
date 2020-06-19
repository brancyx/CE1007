//
//  main.c
//  rDigitValue
//
//  Created by Brandon Chen on 29/2/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include <stdio.h>
int rDigitValue1(int num, int k);
void rDigitValue2(int num, int k, int *result);
int main()
{
    int k;
    int number, digit;
    printf("Enter a number: \n");
    scanf("%d", &number);
    printf("Enter k position: \n");
    scanf("%d", &k);
    printf("rDigitValue1(): %d\n", rDigitValue1(number, k));
    rDigitValue2(number, k, &digit);
    printf("rDigitValue2(): %d\n", digit);
    return 0; }
int rDigitValue1(int num, int k)
{
    int result;
    if (k==0) {
        return 0;
    }
    else if (k==1) {
        return num%10;
    }
    else {
        result = rDigitValue1(num/10, k-1);
    }
    return result;
}
void rDigitValue2(int num, int k, int *result)
{
    if (k==0) {
        *result = 0;
    }
    else if (k==1) {
        *result = num%10;
    }
    else {
        rDigitValue2(num/10, k-1, result);
    }
}
