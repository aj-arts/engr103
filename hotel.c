// For this assignment please create a program that will act as a hotel registration system. In your hotel, you will have 3 floors of rooms with 10 rooms on each floor. All rooms can hold 4 guests maximum. When someone checks into your hotel, they tell you the floor they would like to be on and if a room is available, one is randomly assigned. If the floor is not available, one is assigned on another floor  (at the rate of the floor they wanted). If there are no rooms at all, you need to report you are full. When someone wants to check-out, you need to enter the floor and room number. For each room, you must capture: Guest last name and number of occupants. Each room should also have a nightly rate that is normally $100/Executive Floor, $90/Business Floor, $80/Economy Floor. In addition to checking in and out hotel guests correctly, you need to be able to generate some basic reports:

// Nightly Income: With the current registers guests, how much money will the hotel gross tonight?
// Floor Listing: For a given floor, what are the names of the guests and the room numbers so someone could go find them?
// Evacuation Count: In the event of an emergency, how many guests total are there so you can count them at the emergency evacuation point.
// Capacity: How full (available rooms) is each floor of the hotel?

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Guest
{
    char lastName[20];
    int numOccupants;
    int roomNumber;
    int floorNumber;
    int nightlyRate;
} Guest;

typedef struct Room
{
    int roomNumber;
    Guest *guest;
} Room;

typedef struct Floor
{
    char floorName[20];
    int floorNumber;
    Room rooms[10];
} Floor;

typedef struct Hotel
{
    Floor floors[3];
} Hotel;

void printHotel(Hotel *hotel)
{
    printf("Ajinkya's Hotel\n");
    for (int i = 0; i < 3; i++)
    {
        hotel->floors[i].floorNumber = i+1;
        printf("Floor %d:\n", hotel->floors[i].floorNumber);
        for (int j = 0; j < 10; j++)
        {
            hotel->floors[i].rooms[j].roomNumber = j+1;
            printf("Room %d: ", hotel->floors[i].rooms[j].roomNumber);
            if (hotel->floors[i].rooms[j].guest != NULL)
            {
                printf("%s\n", hotel->floors[i].rooms[j].guest->lastName);
            }
            else
            {
                printf("Empty\n");
            }
        }
    }
}

Guest* createGuest(char lastName[20], int numOccupants, int nightlyRate)
{
    Guest *guest = malloc(sizeof(Guest));
    strcpy(guest->lastName, lastName);
    guest->numOccupants = numOccupants;
    guest->nightlyRate = nightlyRate;
    return guest;
}

void printGuest(Guest *guest)
{
    printf("Guest: %s\n", guest->lastName);
    printf("Number of Occupants: %d\n", guest->numOccupants);
    printf("Room Number: %d\n", guest->roomNumber);
    printf("Floor Number: %d\n", guest->floorNumber);
    printf("Nightly Rate: %d\n", guest->nightlyRate);
}

void addGuestToRoom(Hotel *hotel, Guest *guest, int floorNumber, int roomNumber)
{
    hotel->floors[floorNumber].rooms[roomNumber].guest = guest;
    guest->floorNumber = floorNumber;
    guest->roomNumber = roomNumber;
}

void removeGuestFromRoom(Hotel *hotel, int floorNumber, int roomNumber)
{
    free(hotel->floors[floorNumber].rooms[roomNumber].guest);
}

int preferredFloor(int nightlyRate)
{
    if (nightlyRate == 100)
    {
        return 2;
    }
    else if (nightlyRate == 90)
    {
        return 1;
    }
    else if (nightlyRate == 80)
    {
        return 0;
    }
    return -1;
}

void checkIn(Hotel *hotel, Guest *guest)
{
    int preferredFloorNumber = preferredFloor(guest->nightlyRate);
    for (int i=0; i<3; i++){
        int floorindex = (i+preferredFloorNumber)%3;
        for (int j=0; j<10; j++){
            if (hotel->floors[floorindex].rooms[j].guest == NULL){
                addGuestToRoom(hotel, guest, floorindex, j);
                printf("Guest %s checked in to room %d on floor %d\n", guest->lastName, j, floorindex);
                return;
            }
        }
    }
    printf("Sorry, we are full\n");
}

int nightlyIncome(Hotel *hotel)
{
    int totalIncome = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (hotel->floors[i].rooms[j].guest != NULL)
            {
                totalIncome += hotel->floors[i].rooms[j].guest->nightlyRate;
            }
        }
    }
    return totalIncome;
}

int main(){
    Hotel* hotel = malloc(sizeof(Hotel));
    char* lastName = malloc(sizeof(char)*20);
    int numOccupants;
    int nightlyRate;
    int choice;
    while (1){
        printf("1. Check in\n");
        printf("2. Check out\n");
        printf("3. Print hotel\n");
        printf("4. Nightly income\n");
        printf("5. Exit\n");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                printf("Enter last name: ");
                scanf("%s", lastName);
                if (strlen(lastName) > 20)
                {
                    printf("Invalid last name\n");
                    break;
                }
                
                printf("Enter number of occupants: ");
                scanf("%d", &numOccupants);
                if (numOccupants > 4 || numOccupants < 1)
                {
                    printf("Invalid number of occupants (1-4)\n");
                    break;
                }
                
                printf("Enter nightly rate (100, 90, 80): ");
                scanf("%d", &nightlyRate);
                if (nightlyRate != 100 && nightlyRate != 90 && nightlyRate != 80)
                {
                    printf("Invalid nightly rate\n");
                    break;
                }

                checkIn(hotel, createGuest(lastName, numOccupants, nightlyRate));
                break;
            case 2:
                printf("Enter floor number: ");
                int floorNumber;
                scanf("%d", &floorNumber);
                printf("Enter room number: ");
                int roomNumber;
                scanf("%d", &roomNumber);
                printf("Guest %s checked out of room %d on floor %d\n", hotel->floors[floorNumber].rooms[roomNumber].guest->lastName, roomNumber, floorNumber);
                removeGuestFromRoom(hotel, floorNumber, roomNumber);
                break;
            case 3:
                printHotel(hotel);
                break;
            case 4:
                printf("Nightly income: %d\n", nightlyIncome(hotel));
                break;
            case 5:
                return 0;
        }
    }
    return 0;
}