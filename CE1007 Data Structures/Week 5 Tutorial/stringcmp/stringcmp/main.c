//
//  main.c
//  stringcmp
//
//  Created by Brandon Chen on 9/2/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#define INIT_VALUE 999
int stringcmp(char *s1, char *s2);
int main()
{
    char source[80], target[80], *p;
    int result = INIT_VALUE;
    
    printf("Enter a source string: \n");
    fgets(source, 80, stdin);
    if (p=strchr(source,'\n')) *p = '\0';
    
    printf("Enter a target string: \n");
    fgets(target, 80, stdin);
    if (p=strchr(target,'\n')) *p = '\0';
    
    result = stringcmp(source, target);
    if (result == 1)
        printf("stringcmp(): greater than");
    else if (result == 0)
        printf("stringcmp(): equal");
    else if (result == -1)
        printf("stringcmp(): less than");
    else
        printf("stringcmp(): error");
    return 0;
}

int stringcmp(char *s1, char *s2)
{
    int sum1=0, sum2=0;
    
    sum1 = (int)(*(s1));
    printf("sum1: %d", s1);
    sum2 = (int)(*(s2));
    printf("sum2: %d", s2);
    
    if (sum1 < sum2) {
        return -1;
    }
    else if (sum1 > sum2) {
        return 1;
    }
    return 0;
}
