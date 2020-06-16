//
//  main.c
//  computeSeries
//
//  Created by Brandon Chen on 17/1/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include <stdio.h>
int main()
{
    int n, denominator = 1;
    float x, result = 1.0, numerator = 1.0;
    printf("Enter x: \n");
    scanf("%f", &x);
    
    for (n = 1; n <= 10; n++){
        numerator = numerator * x; //numerator *= x;
        denominator = denominator * (n); //denominator *= n;
        result = result + (numerator / denominator); //result += numerator/denominator;
    }
    printf("Result = %.2f\n",  result);
    return 0; }
