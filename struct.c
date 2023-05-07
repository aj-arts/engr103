#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int roomNumber;
    int occupancy;
} Room;

int main(){
    srand(time(NULL));
    Room room[10];
    for (int i = 0; i < 10; i++){
        room[i].roomNumber = i+1;
        room[i].occupancy = rand() % 5;
    }
    for (int i = 0; i < 10; i++){
        printf("Room %d: %d\n", room[i].roomNumber, room[i].occupancy);
    }
}