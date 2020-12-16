#include "input.h"
#include "table.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>


void ClearScreen()
{
    system("clear");
}

void ToLower(char *array)
{
    int i = 0;
    while (array[i])
    {
        array[i] = tolower(array[i]);
        i++;
    }
}

void GetString(char *string, size_t size)
{
    fgets(string, size, stdin);

    char *tmp = string;
    while (*tmp)
    {
        if (iscntrl(*tmp))
            *tmp = '\0';
        tmp++;
    }
}

void CheckCommand()
{
    char array[MAX_LENGTH_OF_INPUT];
    scanf("%s", array);
    ToLower(array);
    if (!strcmp(array, "create"))
    {
        char tableName[50];
        scanf("%s", tableName);
        size_t column;
        fscanf(stdin, "%zd", &column);
        CreateTable(tableName, column);
    }
    else if (!strcmp(array, "insert"))
    {
        char tableName[50];
        scanf("%s", tableName);
        InsertRow(tableName);
    }
    else if (!strcmp(array, "display"))
    {
        char tableName[50];
        scanf("%s", tableName);
        DisplayTable(tableName);
    }

    else if (!strcmp(array, "drop"))
    {
        char tableName[50];
        scanf("%s", tableName);
        size_t rowToDrop;
        fscanf(stdin, "%zd", &rowToDrop);
        DropTable(tableName, rowToDrop);
    }
    else if (!strcmp(array, "merge"))
    {
        char tableName1[50];
        char tableName2[50];
        scanf("%s", tableName1);
        scanf("%s", tableName2);
        MergeTable(tableName1, tableName2);
    }
    else if (!strcmp(array, "sort"))
    {
        char tableName[50];
        scanf("%s", tableName);
        size_t columnToSort;
        fscanf(stdin, "%zd", &columnToSort);
        SortColumn(tableName, columnToSort);
    }
    else if (!strcmp(array, "statistics"))
    {
        char tableName[50];
        scanf("%s", tableName);
        ShowStatistics(tableName);
    }
    else if (!strcmp(array, "export"))
    {
        char tableName[50];
        char fileName[50];
        scanf("%s", tableName);
        scanf("%s", fileName);
        ExportTableToFile(tableName, fileName);
    }
    else if (!strcmp(array, "import"))
    {
        char tableName[50];
        char fileName[50];
        scanf("%s", tableName);
        scanf("%s", fileName);
        ImportTableFromFile(tableName, fileName);
    }
    else if (!strcmp(array, "clear"))
    {
        ClearScreen();
    }
    else if (!strcmp(array, "exit"))
        exit(0);
    else
    {
        while ((getchar()) != '\n')
            ;
        printf("Error: command not found\n");
        return;
    }
}