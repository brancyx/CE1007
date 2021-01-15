//
//  main.c
//  printAverage
//
//  Created by Brandon Chen on 21/1/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include <stdio.h>
int main()
{
    int total, count, lines, input;
    double average;
    int i;
    printf("Enter number of lines: \n");
    scanf("%d", &lines);
    /* Write your program code here */
    for (i = 0; i < lines; i++){
        total = 0;
        count = 0;
        printf("Enter line %d (End with -1): ",i+1);
        scanf("%d", &input);
        while (input != -1){
            total += input;
            count++;
            scanf("%d", &input);
        }
        average = total / count;
        printf("Average = %.2f", average);
    }
    return 0; }
