//
//  main.c
//  linearSystem
//
//  Created by Brandon Chen on 17/1/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include <stdio.h>
#include <math.h>
int main()
{
    int a1,b1,c1,a2,b2,c2;
    float x, y;
    
    printf("Enter the values for a1, b1, c1, a2, b2, c2: \n");
    scanf("%d %d %d %d %d %d", &a1, &b1, &c1, &a2, &b2, &c2);
    
    x = ((b2 * c1) - (b1 * c2)) / ((a1 * b2) - (a2 * b1));
    y = ((a1 * c2) - (a2 * c1)) / ((a1 * b2) - (a2 * b1));
    printf("x = %.2f", x);
    printf("y = %.2f", y);
    return 0; }

