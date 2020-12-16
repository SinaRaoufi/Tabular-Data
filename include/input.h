#ifndef INPUT_IG
#define INPUT_IG

#include <string.h>
#include <stdio.h>
#include "table.h"

#define MAX_LENGTH_OF_INPUT 1024

//clear bash screen
void ClearScreen();

//convert an array of char to lowercase
void ToLower(char *array);

//check command from input to do things
void CheckCommand();

//developed version of fgets() function
void GetString(char *string, size_t size);

#endif