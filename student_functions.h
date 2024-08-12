#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// Display all menu options to user
void displayMenu()
{
    printf("O = Output all student records\n");
    printf("C = Copy the binary file to a backup binary file.\n");
    printf("M = Menu: show this menu\n");
    printf("N = New student will be added to the student roster file\n");
    printf("R = Remove a student's record\n");
    printf("X = Exit from this program\n");
}

// Display all student records in binary file
void viewAllRecords()
{
    // Open the binary file for reading
    FILE *file = fopen("roster.bin", "rb");
    if (file == NULL)
    {
        printf("Error opening file");
        return;
    }

    student_info student;
    int record_count = 0;

    // Read and display all records
    while (fread(&student, sizeof(student_info), 1, file) == 1)
    {
        printf("\n");
        // Skip records with negative CWID
        if (student.cwid < 0)
            continue;

        // Display the student record
        printf("name = %s\n", student.name);
        printf("cwid = %u\n", student.cwid);
        printf("major = %s\n", student.major);
        printf("class level = ");
        switch (student.class_level)
        {
        case Freshman:
            printf("Freshman\n");
            break;
        case Sophomore:
            printf("Sophomore\n");
            break;
        case Junior:
            printf("Junior\n");
            break;
        case Senior:
            printf("Senior\n");
            break;
        default:
            printf("Unknown\n");
        }
        printf("zip = %d\n", student.zip_code);
        printf("\n-------------------------------------\n");

        record_count++;
    }
    // Print number of records
    printf("Number of data records is %d.\n", record_count);

    fclose(file);
}

// Store backup data into a new file
void backupBinFile()
{
    // Open the binary file for reading
    FILE *input_file = fopen("roster.bin", "rb");
    if (input_file == NULL)
    {
        printf("Error opening input file\n");
        return;
    }

    // Open the backup binary file for writing
    FILE *backup_file = fopen("roster.bak", "wb");
    if (backup_file == NULL)
    {
        printf("Error opening backup file\n");
        fclose(input_file);
        return;
    }

    student_info student;

    // Read and copy records
    while (fread(&student, sizeof(student_info), 1, input_file) == 1)
    {
        // Check if the record is marked as deleted
        if (student.cwid >= 0)
        {
            // Write the record to the backup file
            fwrite(&student, sizeof(student_info), 1, backup_file);
        }
    }

    // Close files
    fclose(input_file);
    fclose(backup_file);

    printf("Backup completed successfully\n");
}

// Prompt user to enter and display new student information
void addNewStudent()
{
    // Open the binary file for reading and writing
    FILE *file = fopen("roster.bin", "rb+");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    student_info new_student;
    int found_removed = 0;

    // Search for the removed record and check if record is marked as removed
    while (fread(&new_student, sizeof(student_info), 1, file) == 1)
    {
        if (new_student.cwid == 0)
        {
            found_removed = 1;
            break;
        }
    }

    // If no records were remove then append to end of binary file
    if (!found_removed)
    {
        printf("No removed records found. Appending new student at the end.\n");
        fseek(file, 0, SEEK_END);
        // Otherwise, overwrite removed record
    }
    else
    {
        printf("Found a removed record. Overwriting...\n");
        fseek(file, -sizeof(student_info), SEEK_CUR);
    }

    // Prompt user to enter new student information
    printf("Enter new student name: ");
    fgets(new_student.name, sizeof(new_student.name), stdin);
    strtok(new_student.name, "\n");

    printf("Enter new student cwid: ");
    scanf("%u", &new_student.cwid);

    printf("Enter new student major: ");
    scanf("%s", new_student.major);

    printf("Enter new student class level (freshman=0,soph=1,junior=2,senior=3): ");
    int class_level;
    scanf("%d", &class_level);
    getchar(); // Consume newline character
    switch (class_level)
    {
    case 0:
        new_student.class_level = Freshman;
        break;
    case 1:
        new_student.class_level = Sophomore;
        break;
    case 2:
        new_student.class_level = Junior;
        break;
    case 3:
        new_student.class_level = Senior;
        break;
    default:
        printf("Invalid class level. Defaulting to Unknown.\n");
        break;
    }

    printf("Enter new student zip code: ");
    scanf("%d", &new_student.zip_code);

    // Write the new student record into the binary file
    fwrite(&new_student, sizeof(student_info), 1, file);

    // Close the file
    fclose(file);

    printf("New student added successfully.\n");
}

// Remove student record from binary file
void removeStudentData()
{
    // Prompt user to enter student CWID
    unsigned int cwid;
    printf("Enter the CWID of the student to be removed: ");
    scanf("%u", &cwid);
    getchar(); // Clear the input buffer

    // Open the binary file for reading and writing
    FILE *file = fopen("roster.bin", "rb+");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    student_info student;
    int found = 0;
    long pos = -1;

    // Search for the student by CWID
    while (fread(&student, sizeof(student_info), 1, file))
    {
        if (student.cwid == cwid)
        {
            found = 1;
            pos = ftell(file) - sizeof(student_info); // Record the position of the found student
            break;
        }
    }

    // If record is found then remove student record
    if (found)
    {
        // Rewind to the position of the found student
        fseek(file, pos, SEEK_SET);

        // Reset all records except class_level
        strcpy(student.name, "");
        student.cwid = 0;
        strcpy(student.major, "");
        student.zip_code = 0;

        // Write the modified student record back to the file
        fwrite(&student, sizeof(student_info), 1, file);
        fclose(file);

        printf("The data of student %u has been removed.\n", cwid);
    }
    else // Otherwise, record is not found
    {
        printf("Student not found.\n");
        fclose(file);
    }