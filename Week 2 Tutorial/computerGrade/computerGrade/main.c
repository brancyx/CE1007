//
//  main.c
//  computerGrade
//
//  Created by Brandon Chen on 19/1/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include <stdio.h>

char findGrade(int);
int main()
{
    /* insert variable declarations here */
    int studentNumber = 0, mark;
    char grade;
    
    printf("Enter Student ID: \n");
    scanf("%d", &studentNumber);
    while (studentNumber != -1)
    {
        printf("Enter Mark: ");
        scanf("%d", &mark);
        grade = findGrade(mark);
        printf("Grade = %c\n", grade);
        printf("Enter Student ID: ");
        scanf("%d", &studentNumber);
    }
    return 0; }

char findGrade(int marks)
{   char grade;
    switch((marks+5)/10){
        case 10:
        case 9:
        case 8:
            grade = 'A';
            return grade;
            break;
        case 7:
            grade = 'B';
            return grade;
            break;
        case 6:
            grade = 'C';
            return grade;
            break;
        case 5:
            grade = 'D';
            return grade;
            break;
        default:
            grade = 'F';
            return grade;
            break;
    }
}
