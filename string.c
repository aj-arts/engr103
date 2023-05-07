#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr;
    char myChar;

    if(!(fptr = fopen("string.c", "r")))
    {
        printf("File could not be opened.\n");
        exit(1);
    }
    printf("%c", 25);
}