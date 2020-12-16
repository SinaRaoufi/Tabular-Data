#include "table.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Table **TableLists = NULL;
size_t numOfTables = 0;

void InsertTableToList(Table *t)
{
    TableLists = (Table **)realloc(TableLists, (numOfTables + 1) * sizeof(Table *));
    TableLists[numOfTables] = t;
    numOfTables++;
}

void CreateTable(const char *tableName, size_t tableColumns)
{
    if (!IsTableExist(tableName))
    {
        if (tableColumns > 0)
        {
            Table *newTable = (Table *)malloc(sizeof(Table));

            if (newTable)
            {
                snprintf(newTable->tableName, MAX_TABLE_NAME_LENGTH, "%s", tableName);
                newTable->columns = tableColumns;
                newTable->rows = 0;
                newTable->indexOfData = 0;
            }
            InsertTableToList(newTable);
        }
        else
            printf("%s", "Error: The number of columns in the table must greater than one!");
    }
    else
        printf("Error: table %s is already exist! \n", tableName);
}

bool IsTableExist(const char *tableName)
{
    for (size_t i = 0; i < numOfTables; i++)
    {
        Table *table = TableLists[i];
        if (!strcmp(tableName, table->tableName))
            return true;
    }
    return false;
}

int GetIndexOfTableList(const char *tableName)
{
    for (size_t i = 0; i < numOfTables; i++)
    {
        Table *table = TableLists[i];
        if (!strcmp(tableName, table->tableName))
            return i;
    }
    return -1;
}

bool IsColumnsMatch(char str[], size_t numOfColumns)
{
    char tmp[1024];
    int i = 0;
    while (str[i] != '\0')
    {
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = '\0';

    size_t counter = 0;
    char del[] = {"[ ]"};
    char *ptr = strtok(tmp, del);
    while (ptr != NULL)
    {
        counter++;
        ptr = strtok(NULL, del);
    }
    if (counter == numOfColumns)
        return true;
    else
        return false;
}

void InsertRow(const char *tableName)
{
    if (IsTableExist(tableName))
    {
        char string[1024];
        GetString(string, 1024);
        int index = GetIndexOfTableList(tableName);
        Table *table = TableLists[index];

        if (IsColumnsMatch(string, table->columns))
        {
            char del[] = {"[ ]"};
            double input[table->columns];
            char *ptr = strtok(string, del);
            int i = 0;
            while (ptr != NULL)
            {
                input[i] = atof(ptr);
                i++;
                ptr = strtok(NULL, del);
            }
            table->rows++;
            table = (Table *)realloc(table, sizeof(Table) + (table->rows * table->columns * sizeof(double)));
            for (size_t j = 0; j < table->columns; j++)
            {
                table->data[table->indexOfData] = input[j];
                table->indexOfData++;
            }
            TableLists[index] = table;
        }
        else
            printf("Error: The number of data entered is not the same as the number of columns in the table!\n");
    }
    else
        printf("Error: there is no table with this name!\n");
}

void DisplayTable(const char *tableName)
{
    if (IsTableExist(tableName))
    {
        int indexOfTable = GetIndexOfTableList(tableName);
        Table *table = TableLists[indexOfTable];
        printf("Table %s with %zd columns and %zd rows.\n", table->tableName, table->columns, table->rows);
        if (table->rows != 0)
        {
            int k = 0;
            for (size_t i = 0; i < table->rows; i++)
            {
                printf("[%zd] ", i);
                printf("[");
                for (size_t j = 0; j < table->columns; j++)
                {
                    PrintNumber(table->data[k]);
                    printf(" ");
                    k++;
                }
                printf("\b]\n");
            }
        }
        else
            printf("Table is empty!\n");
    }
    else
        printf("Error: There is no table with this name!\n");
}

void DropTable(const char *tableName, size_t rowToDrop)
{
    if (IsTableExist(tableName))
    {
        int index = GetIndexOfTableList(tableName);
        Table *table = TableLists[index];
        if (table->rows)
        {
            table->rows--;
            if (rowToDrop != table->rows)
                for (size_t i = rowToDrop; i < table->rows; i++)
                    memmove(&table->data[table->columns * i], &table->data[table->columns * (i + 1)], table->columns * sizeof(double));
            table = (Table *)realloc(table, sizeof(Table) + (table->rows * table->columns * sizeof(double)));
            table->indexOfData -= table->columns;
            TableLists[index] = table;
        }
        else
            printf("Error: Table is empty!\n");
    }
    else
        printf("Error: There is no table with this name!\n");
}

void ShowStatistics(const char *tableName)
{
    int index = GetIndexOfTableList(tableName);
    Table *table = TableLists[index];
    double max[table->columns];
    double min[table->columns];
    double sum[table->columns];
    double average[table->columns];
    double variance[table->columns];
    double standardDeviation[table->columns];
    MinOfEachColumn(table, min);
    MaxOfEachColumn(table, max);
    SumOfEachColumn(table, sum);
    AverageOfEachColumn(table, sum, average);
    VarianceOfEachColumn(table, average, variance);
    StandardDeviation(table, variance, standardDeviation);
    printf("[min ] ");
    printf("[");
    PrintStatisticsDatas(min, table->columns);
    printf("\b]\n");

    printf("[max ] ");
    printf("[");
    PrintStatisticsDatas(max, table->columns);
    printf("\b]\n");

    printf("[sum ] ");
    printf("[");
    PrintStatisticsDatas(sum, table->columns);
    printf("\b]\n");

    printf("[avg ] ");
    printf("[");
    PrintStatisticsDatas(average, table->columns);
    printf("\b]\n");

    printf("[var ] ");
    printf("[");
    PrintStatisticsDatas(variance, table->columns);
    printf("\b]\n");

    printf("[std ] ");
    printf("[");
    PrintStatisticsDatas(standardDeviation, table->columns);
    printf("\b]\n");
}

void PrintNumber(double number)
{
    double fractpart, intpart;
    fractpart = modf(number, &intpart);
    if (fractpart)
        printf("%0.2f", number);

    else
        printf("%0.0f", number);
}

void PrintStatisticsDatas(double array[], int numOfColumns)
{
    for (int i = 0; i < numOfColumns; i++)
    {
        PrintNumber(array[i]);
        printf(" ");
    }
}

void StandardDeviation(Table *table, double variance[], double standardDeviation[])
{
    for (int i = 0; i < table->columns; i++)
        standardDeviation[i] = variance[i] * variance[i];
}

void VarianceOfEachColumn(Table *table, double average[], double variance[])
{
    for (int i = 0; i < table->columns; i++)
    {
        double varianceOfEachColumn = 0;
        for (int j = 0; j < table->rows; j++)
        {
            long long int base = (table->data[i + (j * table->columns)] - average[i]);
            long long int exp = 2;
            long long result = 1;
            while (exp != 0)
            {
                result *= base;
                --exp;
            }
            varianceOfEachColumn += result;
        }
        varianceOfEachColumn /= table->rows;
        variance[i] = varianceOfEachColumn;
    }
}

void SumOfEachColumn(Table *table, double sum[])
{
    for (int i = 0; i < table->columns; i++)
    {
        double sumOfEachColumn = 0;
        for (int j = 0; j < table->rows; j++)
            sumOfEachColumn += table->data[i + (j * table->columns)];
        sum[i] = sumOfEachColumn;
    }
}

void AverageOfEachColumn(Table *table, double sum[], double average[])
{
    for (int i = 0; i < table->columns; i++)
        average[i] = sum[i] / (table->rows);
}

void MinOfEachColumn(Table *table, double min[])
{
    for (int i = 0; i < table->columns; i++)
    {
        double minOfEachColumn = table->data[i];
        for (int j = 0; j < table->rows; j++)
            if (table->data[i + (j * table->columns)] < minOfEachColumn)
                minOfEachColumn = table->data[i + (j * table->columns)];
        min[i] = minOfEachColumn;
    }
}

void MaxOfEachColumn(Table *table, double max[])
{
    for (int i = 0; i < table->columns; i++)
    {
        double maxOfEachColumn = table->data[i];
        for (int j = 0; j < table->rows; j++)
            if (table->data[i + (j * table->columns)] > maxOfEachColumn)
                maxOfEachColumn = table->data[i + (j * table->columns)];
        max[i] = maxOfEachColumn;
    }
}

void MergeTwoTable(Table *table1, Table *table2, int index)
{
    if (table1->columns == table2->columns)
    {
        size_t rowBeforeMerge = table1->rows;
        table1->rows += table2->rows;
        table1->indexOfData += table2->indexOfData;
        table1 = (Table *)realloc(table1, sizeof(Table) + (table1->rows * table1->columns * sizeof(double)));
        size_t j = 0;
        for (size_t i = rowBeforeMerge * table1->columns; i < (table1->rows * table1->columns); i++)
        {
            table1->data[i] = table2->data[j];
            j++;
        }

        TableLists[index] = table1;
    }
    else
        printf("Error: Can't merge these two tables. Columns are not the same size!\n");
}

void MergeTable(const char *tableName1, const char *tableName2)
{
    int index1 = GetIndexOfTableList(tableName1);
    int index2 = GetIndexOfTableList(tableName2);
    Table *table1 = TableLists[index1];
    Table *table2 = TableLists[index2];
    MergeTwoTable(table1, table2, index1);
}

void SortColumn(const char *tableName, size_t columnToSort)
{
    size_t index = GetIndexOfTableList(tableName);
    Table *table = TableLists[index];
    double min = table->data[columnToSort];
    for (size_t i = columnToSort; i < (table->rows * table->columns - columnToSort); i += table->columns)
        for (size_t j = i + table->columns; j < table->rows * table->columns - columnToSort; j += table->columns)
            if (table->data[i] > table->data[j])
            {
                double tmp = table->data[i];
                table->data[i] = table->data[j];
                table->data[j] = tmp;
            }
}

void ExportTableToFile(const char *tableName, const char *fileName)
{
    if (IsTableExist(tableName))
    {
        FILE *file;
        int index = GetIndexOfTableList(tableName);
        Table *table = TableLists[index];
        if (!IsFileExist(fileName))
        {
            file = fopen(fileName, "w");
            fclose(file);
        }
        if (IsFileEmpty(fileName))
        {
            file = fopen(fileName, "a");
            fprintf(file, "%s\n", table->tableName);
            fprintf(file, "%zd\n", table->rows);
            fprintf(file, "%zd\n", table->columns);
            fprintf(file, "%zd\n", table->indexOfData);
            int k = 0;
            for (int i = 0; i < table->rows; i++)
                for (int j = 0; j < table->columns; j++)
                {
                    fprintf(file, "%f ", table->data[k]);
                    k++;
                }

            fclose(file);
        }
        else
        {
            printf("The file is not empty. Do you want to overwritten it? [Y/N]\n");
            char choise;
            scanf("%c", &choise);
            choise = tolower(choise);
            if (choise == 'y')
            {
                file = fopen(fileName, "w");
                fprintf(file, "%s\n", table->tableName);
                fprintf(file, "%zd\n", table->rows);
                fprintf(file, "%zd\n", table->columns);
                fprintf(file, "%zd\n", table->indexOfData);
                int k = 0;
                for (int i = 0; i < table->rows; i++)
                    for (int j = 0; j < table->columns; j++)
                    {
                        fprintf(file, "%f ", table->data[k]);
                        k++;
                    }
                fclose(file);
            }
            else if (choise != 'n')
                printf("Invalid input\n");
        }
    }
    else
        printf("Error: there is no table with this name!\n");
}

void ImportTableFromFile(const char *tableName, const char *fileName)
{
    if (IsFileExist(fileName))
    {
        if (IsTableExist(tableName))
        {
            int index = GetIndexOfTableList(tableName);
            Table *table = TableLists[index];
            if (!IsFileEmpty(fileName))
            {
                FILE *file;
                file = fopen(fileName, "r");
                if (file != NULL)
                {
                    Table *tempTable = (Table *)malloc(sizeof(Table));

                    if (tempTable)
                    {
                        snprintf(tempTable->tableName, MAX_TABLE_NAME_LENGTH, "%s", tableName);
                        tempTable->columns = 0;
                        tempTable->rows = 0;
                        tempTable->indexOfData = 0;
                    }
                    fscanf(file, "%s\n", tempTable->tableName);
                    fscanf(file, "%zd\n", &tempTable->rows);
                    fscanf(file, "%zd\n", &tempTable->columns);
                    fscanf(file, "%zd\n", &tempTable->indexOfData);
                    tempTable = (Table *)realloc(tempTable, sizeof(Table) + (tempTable->rows * tempTable->columns * sizeof(double)));
                    int k = 0;
                    for (int i = 0; i < tempTable->rows; i++)
                        for (int j = 0; j < tempTable->columns; j++)
                        {
                            fscanf(file, "%lf ", &tempTable->data[k]);
                            k++;
                        }
                    fclose(file);
                    MergeTwoTable(table, tempTable, index);
                    free(tempTable);
                }
                else
                    printf("Error: can't open the file!\n");
            }
            else
                printf("Error: The file is empty!\n");
        }
        else
            printf("Error: there is no table with this name!\n");
    }
    else
        printf("Error: there is no file with this name!\n");
}

bool IsFileExist(const char *fileName)
{
    FILE *file;
    file = fopen(fileName, "r");

    if (file == NULL)
        return false;

    fclose(file);
    return true;
}

bool IsFileEmpty(const char *fileName)
{
    FILE *file;
    file = fopen(fileName, "r");
    int size;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fclose(file);
    if (size == 0)
        return true;
    else
        return false;
}