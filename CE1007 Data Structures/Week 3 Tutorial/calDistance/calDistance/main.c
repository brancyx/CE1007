//
//  main.c
//  calDistance
//
//  Created by Brandon Chen on 27/1/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include <stdio.h>
#include <math.h>
void inputXY(double *x1, double *y1, double *x2, double *y2);
void outputResult(double dist);
double calDistance1(double x1, double y1, double x2, double y2);
void calDistance2(double x1, double y1, double x2, double y2, double *dist);
int main()
{
    double x1, y1, x2, y2, distance=-1;
    
    inputXY(&x1, &y1, &x2, &y2);                   // call by reference
    distance = calDistance1(x1, y1, x2, y2);       // call by value
    printf("calDistance1(): ");
    outputResult(distance);
    calDistance2(x1, y1, x2, y2, &distance);       // call by reference
    printf("calDistance2(): ");
    outputResult(distance);                        // call by value
    return 0;
    
    
    
    
}
void inputXY(double *x1, double *y1, double *x2, double *y2)
{
    printf("Input values for x1, y1, x2, y2: ");
    scanf("%lf %lf %lf %lf", &*x1, &*y1, &*x2, &*y2);
}
void outputResult(double dist)
{
    printf("%.2lf\n", dist);
}
double calDistance1(double x1, double y1, double x2, double y2)
{
    double distance;
    distance = sqrt(pow((x2 - x1), 2) + pow((y2 - y1),2));
    return distance;
}
    
void calDistance2(double x1, double y1, double x2, double y2, double
                  *dist)
{
    *dist = sqrt(pow((x2 - x1), 2) + pow((y2 - y1),2));
}

