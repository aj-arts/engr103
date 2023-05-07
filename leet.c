#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fptr;
    FILE *fptr2;

    char filename[100], c, d;
    printf("Enter the filename to open: ");
    scanf("%s", filename);
    fptr = fopen(filename, "r");
    if(fptr == NULL){
        printf("Cannot open file \n");
        exit(0);
    }
    fptr2 = fopen("output.txt", "a");
    c = fgetc(fptr);
    while(c != EOF){
        if (c == 'E' || c == 'e')
        {
            c = '3';
        } if (c == 'O' || c == 'o')
        {
            c = '0';
        } if (c == 'A' || c == 'a')
        {
            c = '4';
        } if (c == 'S' || c == 's')
        {
            c = '5';
        } if (c == 'T' || c == 't')
        {
            c = '7';
        }
        fputc(c, fptr2);
        printf("%c", c);
        c = fgetc(fptr);
    }
    return 0;
}