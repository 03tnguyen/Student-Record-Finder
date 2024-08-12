#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "student_functions.h"

void viewAllRecords();
void backupBinFile();
void addNewStudent();
void displayMenu();
void removeStudentData();

int main()
{
    printf("Welcome to student roster file\n");
    printf("We keep your records current.\n");
    printf("This program is maintained by Tram Nguyen.\n");

    // Display menu options
    printf("\nPlease select one of the following options by entering the associated single character.\n");
    displayMenu();

    // Call specified function according to user's input
    char choice;
    do
    {
        printf("\nPlease enter a selection: ");
        scanf(" %c", &choice);
        getchar();

        switch (choice)
        {
        case 'O':
            viewAllRecords();
            break;
        case 'C':
            backupBinFile(); 
            break;
        case 'N': 
            addNewStudent();
            break;
        case 'M': 
            displayMenu();
            break;
        case 'R':
            removeStudentData();
            break;
        case 'X':
            printf("\nThank you for using the Student Record System.\n");
            printf("You may use this software at any time. Bye.\n");
            break;
        default: 
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 'X');
    printf("\n");
    return 0;
}
