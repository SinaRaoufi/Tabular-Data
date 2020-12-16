#include "App.h"
#include <stdbool.h>

void init()
{
    // Clear the screen
    ClearScreen();
    while (true)
    {
        printf("-> ");
        CheckCommand();
    }
}
