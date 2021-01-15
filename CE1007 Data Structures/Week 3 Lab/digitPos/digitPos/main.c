//
//  main.c
//  digitPos
//
//  Created by Brandon Chen on 27/1/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include <stdio.h>
int digitPos1(int num, int digit);
void digitPos2(int num, int digit, int *result);
int main()
{
    int number, digit, result=0;
    printf("Enter the number: \n");
    scanf("%d", &number);
    printf("Enter the digit: \n");
    scanf("%d", &digit);
    printf("digitPos1(): %d\n", digitPos1(number, digit));
    digitPos2(number, digit, &result);
    printf("digitPos2(): %d\n", result);
    return 0; }
int digitPos1(int num, int digit)
{
    int rem, position_from_right = 1;
    while(num){
        rem = num % 10;
        if (rem == digit){
            break;
        }
        position_from_right++;
        num = num/10;
    }
    return position_from_right;
}
void digitPos2(int num, int digit, int *result)
{
    int rem;
    while(num){
        rem = num % 10;
        (*result)++;
        if (rem == digit){
            break;
        }
        num = num/10;
    }
}
