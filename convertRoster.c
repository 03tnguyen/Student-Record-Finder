#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

int main()
{
    // Open text file for reading
    FILE *input_file = fopen("roster.txt", "r");

    // Open binary file for writing. If file does not exist, it will be created
    FILE *output_file = fopen("roster.bin", "wb");

    // Check for text file and binary file 
    if (input_file == NULL || output_file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    char line[100];
    student_info student;

    // Read each line from the text file
    while (fgets(line, sizeof(line), input_file))
    {
        if (line[0] == '\n') // Skip blank lines
        {
            continue;
        }

        // Read name and remove mewline character
        strcpy(student.name, line);
        student.name[strcspn(student.name, "\n")] = '\0';

        // Read CWID
        fgets(line, sizeof(line), input_file);
        student.cwid = atoi(line);

        // Read major
        fgets(line, sizeof(line), input_file);
        strtok(line, "\n");
        strcpy(student.major, line);

        // Read class level
        fgets(line, sizeof(line), input_file);
        strtok(line, "\n");
        if (strcmp(line, "Freshman") == 0)
            student.class_level = Freshman;
        else if (strcmp(line, "Sophomore") == 0)
            student.class_level = Sophomore;
        else if (strcmp(line, "Junior") == 0)
            student.class_level = Junior;
        else if (strcmp(line, "Senior") == 0)
            student.class_level = Senior;

        // Read zip code
        fgets(line, sizeof(line), input_file);
        student.zip_code = atoi(line);

        // Write student info into binary file
        fwrite(&student, sizeof(student), 1, output_file);
    }

    // Close text file and binary file
    fclose(input_file);
    fclose(output_file);

    return 0;
}
