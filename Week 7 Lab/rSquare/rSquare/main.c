//
//  main.c
//  rSquare
//
//  Created by Brandon Chen on 1/3/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include <stdio.h>
int rSquare1(int num);
void rSquare2(int num, int *result);
int main()
{
    int number, result=0;
    printf("Enter the number: \n");
    scanf("%d", &number);
    printf("rSquare1(): %d\n", rSquare1(number));
    rSquare2(number, &result);
    printf("rSquare2(): %d\n", result);
    return 0; }
int rSquare1(int num)
{
    if (num == 1) {
        return num;
    }
    else {
        return rSquare1(num-1) + (2*num - 1);
    }
}
void rSquare2(int num, int *result)
{
    if (num == 1) {
        *result = num;
    }
    else {
        rSquare2(num-1, result);
        *result += (2*num - 1);
    }
}
