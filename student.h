#ifndef STUDENT_H
#define STUDENT_H

#include <stdint.h>

enum Class {Freshman, Sophomore, Junior, Senior};

typedef struct student_info{
    char name[22];
    unsigned int cwid;
    char major[20];
    enum Class class_level;
    int zip_code;
} student_info;

// Function declarations
void viewAllRecords();
void backupBinFile();
void addNewStudent();
void displayMenu();
void removeStudentData();

#endif 
