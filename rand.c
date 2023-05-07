#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randint(){
    srand(time(NULL));
    return rand()%100+1;
}

void prompt() {
    printf("Guess the number: \n");
}

int main(){
    int number = randint();
    int guess;
    int isCorrect = 0;
    while(!isCorrect){
        prompt();
        scanf("%d", &guess);
        if(guess == number){
            printf("You guessed correctly!\n");
            isCorrect = 1;
        } else {
            printf("You guessed incorrectly!\n");
        }
    }
    return 0;
}