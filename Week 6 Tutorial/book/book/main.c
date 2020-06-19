//
//  main.c
//  book
//
//  Created by Brandon Chen on 18/2/20.
//  Copyright © 2020 Brandon Chen. All rights reserved.
//

#include <stdio.h>
#include <string.h>
typedef  struct {
    char title[80];
    char lastname[80];
    char firstname[80];
    char publisher[80];
} Booktype;
void readBook(Booktype *book);
void printBook(Booktype book);
int main()
{
    Booktype book;
    readBook(&book);
    printf("The book information: \n");
    printBook(book);
}
void readBook(Booktype *book)
{
    printf("Enter title of the book: \n");
    fgets((*book).title,80,stdin);
    
    printf("Enter the author first name: \n");
    fgets((*book).firstname,80,stdin);
    
    printf("Enter the author last name: \n");
    fgets((*book).lastname,80,stdin);
    
    printf("Enter the publisher name: \n");
    fgets((*book).publisher,80,stdin);
}
void printBook(Booktype book)
{
    printf("Title: %s", book.title);
    printf("Author: %s %s", book.firstname,book.lastname);
    printf("Publisher: %s", book.publisher);

}
