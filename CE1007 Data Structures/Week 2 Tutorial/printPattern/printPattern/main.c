//
//  main.c
//  printPattern
//
//  Created by Brandon Chen on 17/1/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include <stdio.h>
int main()
{
    int row, col, height;
    int num = 0;
    printf("Enter the height: \n");
    scanf("%d", &height);
    printf("Pattern: \n");
    
    for (row = 1; row <= height; ++row){
        if (num <= 2){
            ++num;
        }
        else {
            num = 1;
        }
        for (col = 1; col <= row; ++col){
            printf("%d", num);
        }
        printf("\n");
    }
    
    return 0; }

