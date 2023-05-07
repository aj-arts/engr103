/* This program is a game called "impostor". The player has to guess the impostor among a list of suspects.
The program generates a random number to choose the impostor and gives the player five chances to guess it. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random number within a range
int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1;
    }
    else
    {
        low_num = max_num + 1;
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

// Function to print the list of suspects
void suspectList()
{
    printf("\n1. Red\n2. Yellow\n3. Blue\n4. Green\n5. White\n6. Black\n\n");
}

// Function to print the game introduction
void intro()
{
    printf("Welcome to the game of impostor!\n");
    printf("You are a detective and you have to find the impostor.\n");
    printf("You have 5 chances to guess the impostor.\n");
    printf("Good luck!\n");
}

// Function to print the name of a non-impostor suspect
void impostorName(int guess){
    switch (guess)
    {
    case 1:
        printf("Red is not the impostor.\n");
        break;
    case 2:
        printf("Yellow is not the impostor.\n");
        break;
    case 3:
        printf("Blue is not the impostor.\n");
        break;
    case 4:
        printf("Green is not the impostor.\n");
        break;
    case 5:
        printf("White is not the impostor.\n");
        break;
    case 6:
        printf("Black is not the impostor.\n");
        break;
    default:
        break;
    }
}

// Main function
int main()
{
    intro();// Prints the game introduction
    int impostor = random_number(1, 6);// Generates the impostor
    int guess;// Variable to store the player's guess
    int chances = 1;// Variable to count the player's chances
    suspectList();// Prints the list of suspects
    printf("One of them is an impostor. Who is it?\n");
    printf("Enter the number of the impostor (1-6): ");
    scanf("%d", &guess);// Reads the player's guess from the standard input
    while(guess<1 || guess>6){
        // Validates the player's input
        printf("Invalid input. Try again.\n");
        printf("Enter the number of the impostor (1-6): ");
        scanf("%d", &guess);
    }

    while(chances<5)
    {
        if(guess==impostor){
            printf("\nYou win!\n");
            break;
        }
        else{
            impostorName(guess);
        }
        printf("You have %d chances left.\n", 5 - chances);
        suspectList();
        printf("Enter the number of the impostor (1-6): ");
        scanf("%d", &guess);
        while(guess<1 || guess>6){
            printf("Invalid input. Try again.\n");
            printf("Enter the number of the impostor (1-6): ");
            scanf("%d", &guess);
        }
        chances++;
    }
    if(chances==5){
        printf("\nYou lose!\n");
    }
    return 0;
}