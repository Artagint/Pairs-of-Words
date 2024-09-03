// Artem Tagintsev, CS360, hw1, 09/04/2024
// This file holds the funciton prototypes responsible for checking errors
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Make sure the user provides 2 or more arguments
int checkArgumentsFirst(int argc);

// Check if first character in argv[1] is a '-', and check to make sure a number is valid
int checkNumber(char *argv, int argc);

// Loop through every file and check if it is a valid file
int checkFile(char **argv, int argc, int startReadingFiles);
