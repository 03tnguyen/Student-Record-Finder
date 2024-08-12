#!/bin/bash
# Remove unnecessary files
rm *.o

# Grant permission
chmod u+x r.sh

# Complier check on student.h
gcc -c student.h

# Compile and run readFile.c to create a binary file from the text file
echo "The binary file is created."
gcc -o create convertRoster.c
./create

# Compile and run menu.c to create the menu interface
echo -e "Run the program \"Final semester test\"\n"
gcc -o main main.c 
./menu

echo "The bash file has terminated."
