#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// struct to save room's data
struct Room
{
    int room_number;
    int empty_room;
    int patient_id;
};
// struct to save patient's data
struct patient
{
    int patient_id;
    char name[50];
    char status[50];
};
// struct to save user's data
struct user
{
    char username[50];
    char password[50];
    int privilage;
};
// saved array of users in struct users
struct user users[50];
// saved array of rooms in struct room
struct Room rooms[50];
// saved array of patients in struct patient
struct patient patients[50];

// functions of the system
//void login();
//void remove_reservation();
//void check_rooms();
//void update_data();
int x;
// data base of rooms
struct Room rooms[50] = {
    {101, 1, 0},
    {102, 0, 123},
    {103, 1, 0},
    {104, 0, 456},
    {105, 1, 0}};
// data base of patients
struct patient patients[50] = {
    {123, "sama", "stable"},
    {456, "hana", "critical"},
    {789, "nada", "stable"}};
// data base of users
struct user users[50] = {
    {"sama", "1111", 2},
    {"dana", "2222", 1},
    {"hana", "3333", 2},
    {"nada", "4444", 2},
    {"mariam", "5555", 1}};

void login()
{
    int f = 0;
    do
    {
        char username[50], password[50];
        // take username and password from user
        printf("Please enter your username to login: \n");
        scanf("%s", &username);
        printf("Please enter your password to procceed: \n");
        scanf("%s", &password);
        // check for user in database
        int i, found = 0;
        for (i = 0; i < 5; i++)
        {
            if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
            {
                found = 1;
                x = users[i].privilage;
                break;
            }
        }
        // user found
        if (found == 1)
        {
            f = 1;
            int privilage = users[i].privilage;
            if (privilage == 1)
            {
                printf("Welcome doctor %s \n", username);
                break;
            }
            if (privilage == 2)
            {
                printf("Welcome patient %s \n", username);
                break;
            }
        }
        else
        {
            printf("Invalid username or password please try again! \n");
            f++;
        }
        if (f == 4)
        {
            printf("Maximum attempts reached. system is exiting\n");
            exit(0);
        }
    } while (f < 4);
}
// cancel reservation function
void remove_reservation()
{
    int i, j, room_number, found = 0;
    printf("Please enter your reserved room's number: \n");
    // checking for integer value "check for one integer value"
    while (scanf("%d", &room_number) != 1)
    {
        printf("Invalid input,Please enter a valid room number: \n");
        // Clear the input buffer
        while (getchar() != '\n')
            ;
    }
    // check the room number
    for (i = 0; i < 5; i++)
    {
        if (rooms[i].room_number == room_number)
        {
            found = 1;
            if (rooms[i].patient_id == 0)
            {
                printf("Room %d is not reserved.\n", room_number);
            }
            else
            {
                rooms[i].patient_id = 0;
                printf("Reservation for room %d has been cancelled.\n", room_number);
            }
            break; // Stop looping once room found
        }
    }
    if (!found || room_number < 1)
        printf("Invalid room number,please choose again!\n");
}
// check available rooms
void check_rooms()
{
    int i, empty_room = 0;
    // Print empty rooms
    for (i = 0; i < 5; i++)
    {
        if (rooms[i].empty_room == 1)
        {
            printf("Room %d is empty.\n", rooms[i].room_number);
            empty_room++;
        }
    }
    // If no empty rooms found, print message
    if (empty_room == 0)
    {
        printf("No empty rooms available.\n");
    }
}
// update data
void update_data()
{
    int patient_idd, i, patient_found = 0,a=0;
    printf("Enter your regestired ID: ");
    while (scanf("%d", &patient_idd) != 1)
    {
        printf("Invalid input,Please enter a valid ID: ");
        // Clear the input buffer
        while (getchar() != '\n');
            
    }
    // Loop through patients to find matching ID
    for (i = 0; i < 50; i++)
    {
        patient_found=0;
        if (patients[i].patient_id == patient_idd)
        {
            char newStatus[50]; // Temporary variable to store status safely
            printf("Enter new status for patient %s:\n a)stable\n b)critical \n ", patients[i].name);
            scanf("%s", newStatus);
            if (strcmp(newStatus, "stable") == 0 || strcmp(newStatus, "critical") == 0)
            {
                if (strcmp(newStatus, patients[i].status) != 0) // Check if the new status is different from the existing one
                {
                    strcpy(patients[i].status, newStatus); // Safely copy the new status
                    printf("Patient's data is updated.\n");
                    break;
                }
                else if (strcmp(newStatus, patients[i].status) == 0)
                {
                    printf("Status of patient %s is already %s\n",patients[i].name, patients[i].status);
                     patient_found = 1; 
                     break;
                }
             }
        }
            else
            {
                printf("Invalid status,please choose again\n");
                patient_found = 1; // Invalid status, but patient was found
                a=i;
                break;
            }
        }
    // patient not found
    if (!patient_found)
    {
        int choice2;
        printf("Patient not found, please choose one of the following:\n 1)Add new patient\n 2)Back to choices\n");
        scanf("%d", &choice2);
        switch (choice2)
        {
        case 1:
        {
            // Add new patient
            if (x == 1)
            { // Check if user is a doctor
                if (a < 50)
                {
                    char name[50];
                    patients[a].patient_id = patient_idd;
                     printf("Enter patient's name: \n");
                     scanf("%s", &name);
                    int len = strlen(name);
                    if (len < 2 || !isalpha(name[0])) // Check if the length is more than 1 and the first character is a letter
                    {
                        printf("Invalid username!!\n");
                        return;
                    }
                    strcpy(patients[a].name,name);
                    printf("Choose an ID for user %s\n",name);
                    scanf("%d", &patients[a].patient_id);
                    printf("Enter new status for patient %s:\n a)stable\n b)critical \n ", patients[a].name);
                    scanf("%s", patients[a].status);
                    if (strcmp(patients[a].status, "stable") == 0 || strcmp(patients[a].status, "critical") == 0)
                    {
                        printf("Patient added successfully.\n");
                        break;
                    }
                    else
                    {
                        printf("Invalid status!!\n");
                        break;
                    }
                }
                else
                {
                    printf("Maximum number of patients reached. Cannot add new patient.\n");
                }
            }
            break;
        }
          case 2:
        {
            break;
        }
         default:
            printf("Invalid choice!!\n");
        }
    }
}
int main()
{
    printf("------ WELCOME TO HOSPITAL ------ \n");
    // login function call
    login();
    // user choose one of the functions
    int choice, i;
    while (1) // infinte loop
    {
        printf("Choose one of the following functions to procceed \n 1)Remove a reservation \n 2)check empty rooms\n 3)update patient's data \n 4)exit program\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            // check privillage
            if (users[x].privilage == 2)
            {
                remove_reservation();
            }
            else
                printf("You don't have the necessary privileges to cancel a reservation,please try again!\n");
            break;
        case 2:
            if (users[x].privilage == 1)
            {
                check_rooms();
            }
            else
                printf("You don't have the necessary privileges to check empty rooms,please try again!\n");
            break;
        case 3:
            if (users[x].privilage == 1)
            {
                update_data();
            }
            else
                printf("You don't have the necessary privileges to update patient's data,please try again!\n");
            break;
        case 4:
            exit(0);
        default:
            printf("invalid choice please try again \n");
        }
    }
}