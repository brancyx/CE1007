//
//  main.c
//  countChars
//
//  Created by Brandon Chen on 17/1/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include <stdio.h>
int main()
{
    int ccount = 0, dcount = 0;
    char ch;
    printf("Enter your characters (# to end): \n");
    scanf("%c", &ch);
    /*printf("%c", ch);*/
    
    while (ch != '#') {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
            ccount++;
            printf("ccount = %d", ccount);
            printf("\nEnter your characters (# to end): \n");
            scanf(" %c", &ch);
        }
        else if (ch >= '0' && ch <= '9'){
            dcount++;
            printf("dcount = %d", dcount);
            printf("\nEnter your characters (# to end): \n");
            scanf(" %c", &ch);
        }
    }
    
    
    printf("The number of digits: %d\n", dcount);
    printf("The number of letters: %d\n", ccount);
    return 0;
}


