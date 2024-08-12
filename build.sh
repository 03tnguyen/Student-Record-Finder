#!/bin/bash

# Remove unnecessary object files
echo "Removing object files..."
rm -f *.o

# Grant execute permissions to the build script
echo "Granting execute permissions to build.sh..."
chmod u+x build.sh

# Check for the existence of header file before compiling
if [ -f student.h ]; then
    echo "Compiling student.h..."
    gcc -c student.h
else
    echo "Error: student.h not found."
    exit 1
fi

# Compile and run convertRoster.c to create the binary file
echo "Compiling convertRoster.c..."
gcc -o convert convertRoster.c
echo "Running convert to create the binary file..."
./convert

# Compile and run menu.c to create the menu interface
echo "Compiling main.c to create the menu interface..."
gcc -o main main.c 
echo -e "Running main to display the menu...\n"
./main

echo "Script execution completed successfully."