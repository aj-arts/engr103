// For this assignment please create a program that will act as a hotel registration system. In your hotel, you will have 3 floors of rooms with 10 rooms on each floor. All rooms can hold 4 guests maximum. When someone checks into your hotel, they tell you the floor they would like to be on and if a room is available, one is randomly assigned. If the floor is not available, one is assigned on another floor  (at the rate of the floor they wanted). If there are no rooms at all, you need to report you are full. When someone wants to check-out, you need to enter the floor and room number. For each room, you must capture: Guest last name and number of occupants. Each room should also have a nightly rate that is normally $100/Executive Floor, $90/Business Floor, $80/Economy Floor. In addition to checking in and out hotel guests correctly, you need to be able to generate some basic reports:

// Nightly Income: With the current registers guests, how much money will the hotel gross tonight?
// Floor Listing: For a given floor, what are the names of the guests and the room numbers so someone could go find them?
// Evacuation Count: In the event of an emergency, how many guests total are there so you can count them at the emergency evacuation point.
// Capacity: How full (available rooms) is each floor of the hotel?

/*
Ajinkya Gokule
ENGR 103
7th May 2023
Hotel Management System
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Guest Sructure
typedef struct Guest
{
    char lastName[20];
    int numOccupants;
    int roomNumber;
    int floorNumber;
    int nightlyRate;
} Guest;

// Room Structure Contains Guest Structure
typedef struct Room
{
    int roomNumber;
    Guest *guest;
} Room;

// Floor Structure Contains Room Structure Array
typedef struct Floor
{
    char floorName[20];
    int floorNumber;
    Room rooms[10];
} Floor;

// Hotel Structure Contains Floor Structure Array
typedef struct Hotel
{
    Floor floors[3];
} Hotel;

// Prints Hotel
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

// Creates Guest
Guest* createGuest(char lastName[20], int numOccupants, int nightlyRate)
{
    Guest *guest = malloc(sizeof(Guest));
    strcpy(guest->lastName, lastName);
    guest->numOccupants = numOccupants;
    guest->nightlyRate = nightlyRate;
    return guest;
}

// Prints Guest
void printGuest(Guest *guest)
{
    printf("Guest: %s\n", guest->lastName);
    printf("Number of Occupants: %d\n", guest->numOccupants);
    printf("Room Number: %d\n", guest->roomNumber);
    printf("Floor Number: %d\n", guest->floorNumber);
    printf("Nightly Rate: %d\n", guest->nightlyRate);
}

// Adds Guest to Room
void addGuestToRoom(Hotel *hotel, Guest *guest, int floorNumber, int roomNumber)
{
    hotel->floors[floorNumber].rooms[roomNumber].guest = guest;
    guest->floorNumber = floorNumber;
    guest->roomNumber = roomNumber;
}

// Removes Guest from Room
void removeGuestFromRoom(Hotel *hotel, int floorNumber, int roomNumber)
{
    free(hotel->floors[floorNumber].rooms[roomNumber].guest);
    hotel->floors[floorNumber].rooms[roomNumber].guest = NULL;
}

// Returns Preferred Floor
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

// Checks In Guest
void checkIn(Hotel *hotel, Guest *guest)
{
    int preferredFloorNumber = preferredFloor(guest->nightlyRate);
    for (int i=0; i<3; i++){
        int floorindex = (i+preferredFloorNumber)%3;
        for (int j=0; j<10; j++){
            if (hotel->floors[floorindex].rooms[j].guest == NULL){
                addGuestToRoom(hotel, guest, floorindex, j);
                printf("Guest %s checked in to room %d on floor %d\n", guest->lastName, j+1, floorindex+1);
                return;
            }
        }
    }
    printf("Sorry, we are full\n");
}

// Returns Nightly Income
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

// Returns Total Guests
int totalGuests(Hotel *hotel)
{
    int totalGuests = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (hotel->floors[i].rooms[j].guest != NULL)
            {
                totalGuests += hotel->floors[i].rooms[j].guest->numOccupants;
            }
        }
    }
    return totalGuests;
}

// Returns Available Rooms
int availableRooms(Hotel *hotel, int floorNumber)
{
    int availableRooms = 0;
    for (int i = 0; i < 10; i++)
    {
        if (hotel->floors[floorNumber].rooms[i].guest == NULL)
        {
            availableRooms++;
        }
    }
    return availableRooms;
}

// Preloads Guests
void preloadGuests(Hotel* hotel){
    checkIn(hotel, createGuest("Smith", 2, 100));
    checkIn(hotel, createGuest("Johnson", 1, 90));
    checkIn(hotel, createGuest("Williams", 3, 80));
    checkIn(hotel, createGuest("Jones", 4, 100));
    checkIn(hotel, createGuest("Brown", 2, 90));
    checkIn(hotel, createGuest("Davis", 1, 80));
    checkIn(hotel, createGuest("Miller", 3, 100));
    checkIn(hotel, createGuest("Wilson", 4, 90));
    checkIn(hotel, createGuest("Moore", 2, 80));
    checkIn(hotel, createGuest("Taylor", 1, 100));
}

// Resets Hotel
void resetHotel(Hotel* hotel){
    for (int i=0; i<3; i++){
        for (int j=0; j<10; j++){
            if (hotel->floors[i].rooms[j].guest != NULL){
                removeGuestFromRoom(hotel, i, j);
            }
        }
    }
}

// Saves Hotel to File
void saveHotel(Hotel* hotel){
    FILE* file = fopen("hotel.txt", "w");
    for (int i=0; i<3; i++){
        for (int j=0; j<10; j++){
            if (hotel->floors[i].rooms[j].guest != NULL){
                fprintf(file, "%s %d %d %d %d\n", hotel->floors[i].rooms[j].guest->lastName, hotel->floors[i].rooms[j].guest->numOccupants, hotel->floors[i].rooms[j].guest->roomNumber, hotel->floors[i].rooms[j].guest->floorNumber, hotel->floors[i].rooms[j].guest->nightlyRate);
            }
        }
    }
    fclose(file);
}

// Loads Hotel from File
void loadHotel(Hotel* hotel){
    FILE* file = fopen("hotel.txt", "r");
    char lastName[20];
    int numOccupants;
    int roomNumber;
    int floorNumber;
    int nightlyRate;
    while (fscanf(file, "%s %d %d %d %d\n", lastName, &numOccupants, &roomNumber, &floorNumber, &nightlyRate) != EOF){
        addGuestToRoom(hotel, createGuest(lastName, numOccupants, nightlyRate), floorNumber, roomNumber);
    }
    fclose(file);
}

int main(){
    Hotel* hotel = malloc(sizeof(Hotel));
    char* lastName = malloc(sizeof(char)*20);
    int numOccupants;
    int nightlyRate;
    int choice;
    // user interface
    while (1){
        printf("1. Check in\n");
        printf("2. Check out\n");
        printf("3. Print hotel\n");
        printf("4. Nightly income\n");
        printf("5. Evacuation count\n");
        printf("6. Available rooms\n");
        printf("7. Preload guests\n");
        printf("8. Reset hotel\n");
        printf("9. Save hotel\n");
        printf("10. Load hotel\n");
        printf("11. Exit\n");
        scanf("%d", &choice);
        // switch case for user choice
        switch (choice){
            case 1:
                // take user input for last name, number of occupants and nightly rate
                printf("Enter last name: ");
                scanf("%s", lastName);

                // check if last name is valid
                if (strlen(lastName) > 20)
                {
                    printf("Invalid last name\n");
                    break;
                }
                
                printf("Enter number of occupants: ");
                scanf("%d", &numOccupants);

                // check if number of occupants is valid
                if (numOccupants > 4 || numOccupants < 1)
                {
                    printf("Invalid number of occupants (1-4)\n");
                    break;
                }
                
                printf("Enter nightly rate (100, 90, 80): ");
                scanf("%d", &nightlyRate);

                // check if nightly rate is valid
                if (nightlyRate != 100 && nightlyRate != 90 && nightlyRate != 80)
                {
                    printf("Invalid nightly rate\n");
                    break;
                }

                checkIn(hotel, createGuest(lastName, numOccupants, nightlyRate));
                break;
            case 2:
                // take user input for floor and room number for checkout
                printf("Enter floor number: ");
                int floorNumber;
                scanf("%d", &floorNumber);
                printf("Enter room number: ");
                int roomNumber;
                scanf("%d", &roomNumber);
                // check if floor and room number are valid
                if (floorNumber > 3 || floorNumber < 1)
                {
                    printf("Invalid floor number\n");
                    break;
                }
                if (roomNumber > 10 || roomNumber < 1)
                {
                    printf("Invalid room number\n");
                    break;
                }
                // decrement floor and room number to match array index
                floorNumber--;
                roomNumber--;

                // check if room is empty and checkout
                if (hotel->floors[floorNumber].rooms[roomNumber].guest == NULL)
                {
                    printf("Room is empty\n");
                    break;
                } else{
                    printf("Guest %s checked out of room %d on floor %d\n", hotel->floors[floorNumber].rooms[roomNumber].guest->lastName, roomNumber, floorNumber);
                    removeGuestFromRoom(hotel, floorNumber, roomNumber);
                }
                break;
            case 3:
                // print hotel
                printHotel(hotel);
                break;
            case 4:
                // print nightly income
                printf("Nightly income: %d\n", nightlyIncome(hotel));
                break;
            case 5:
                // print total guests
                printf("Evacuation count: %d\n", totalGuests(hotel));
                break;
            case 6:
                // print available rooms
                printf("Floor no: 1, Available rooms: %d\n", availableRooms(hotel, 0));
                printf("Floor no: 2, Available rooms: %d\n", availableRooms(hotel, 1));
                printf("Floor no: 3, Available rooms: %d\n", availableRooms(hotel, 2));
                break;
            case 7:
                // preload guests
                preloadGuests(hotel);
                break;
            case 8:
                // reset hotel
                resetHotel(hotel);
                break;
            case 9:
                // save hotel
                saveHotel(hotel);
                break;
            case 10:
                // load hotel
                loadHotel(hotel);
                break;
            case 11:
                return 0;
        }
    }
    return 0;
}