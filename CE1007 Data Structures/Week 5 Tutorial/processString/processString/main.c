//
//  main.c
//  processString
//
//  Created by Brandon Chen on 9/2/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include <stdio.h>
#include <string.h>
void processString(char *str, int *totVowels, int *totDigits);
int main()
{
    char str[50], *p;
    int totVowels, totDigits;
    
    printf("Enter the string: \n");
    fgets(str, 80, stdin);
    printf("str: %s", str);
    if (p=strchr(str,'\n'))
        *p = '\0';
    
    processString(str, &totVowels, &totDigits);
    printf("Total vowels = %d\n", totVowels);
    printf("Total digits = %d\n", totDigits);
    return 0;
}

void processString(char *str, int *totVowels, int *totDigits)
{
    int i=0, j=0;
    while (*str != '\0') {
        if (isdigit(*str)) {
            i += 1;
        }
        else if (*str == 'a' || *str == 'A' || *str == 'e' || *str == 'E' || *str == 'i' || *str == 'I' || *str == 'o' || *str == 'O' || *str == 'u' || *str == 'U') {
            j += 1;
        }
        str++;
        }
    *totDigits = i;
    *totVowels = j;
}

