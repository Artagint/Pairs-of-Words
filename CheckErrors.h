// Artem Tagintsev, CS360, hw1
// This file holds the funciton prototypes responsible for checking errors
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Make sure the user provides 2 or more arguments
int checkArgumentsFirst(int argc);

// Check if first character in argv[1] is a '-', and check to make sure a number is valid
int checkNumber(char *argv, int argc);
