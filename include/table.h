#ifndef TABLE_IG
#define TABLE_IG

#include "input.h"
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX_TABLE_NAME_LENGTH 1024

//an struct for table
struct table
{
    size_t rows;
    size_t columns;
    char tableName[MAX_TABLE_NAME_LENGTH];
    size_t indexOfData;
    double data[];
};

//define struct table as Table
typedef struct table Table;

//add a new table to list of tables
void InsertTableToList(Table *t);

//check existence of a table
bool IsTableExist(const char *tableName);

//find index of a table from list of table and return it's index
int GetIndexOfTableList(const char *tableName);

//check datas that suppose to add to table with existed table's column
bool IsColumnsMatch(char str[], size_t numOfColumns);

//get name of the table and add a new row to that table(if that table existed)
void InsertRow(const char *tableName);

//get name of the table and number of table's column and create a table with that information
void CreateTable(const char *tableName, size_t tableColumns);

//get name of table and display table's informations such as name of table,number of columns, number of rows and datas
void DisplayTable(const char *tableName);

//get name of table and index of one of the table
void DropTable(const char *tableName, size_t rowToDrop);

//get name of table and call expected functions
void ShowStatistics(const char *tableName);

//print each statistics datas such as min,max,sum,avg,vat,std
void PrintStatisticsDatas(double array[], int numOfColumns);

/*developed version of printf that print a number
if the given number is decimal, print that number with two precision
*/
void PrintNumber(double number);

//calculate min of each column of table
void MinOfEachColumn(Table *table, double min[]);

//calculate average of each column of table
void AverageOfEachColumn(Table *table, double sum[], double average[]);

//calculate max of each column of table
void MaxOfEachColumn(Table *table, double max[]);

//calculate sum of each column of table
void SumOfEachColumn(Table *table, double sum[]);

//calculate variance of each column of table
void VarianceOfEachColumn(Table *table, double average[], double variance[]);

//calculate standarddeviation of each column of table
void StandardDeviation(Table *table, double variance[], double standardDeviation[]);

//get the name of two tables and merge them eachother
void MergeTable(const char *tableName1, const char *tableName2);

//merge two table with eachother
void MergeTwoTable(Table *table1, Table *table2, int index);

//get the name of table and the index of column that suppose to sort
void SortColumn(const char *tableName, size_t columnToSort);

//add a table's information to a file
void ExportTableToFile(const char *tableName, const char *fileName);

//get a table's informations from a file
void ImportTableFromFile(const char *tableName, const char *fileName);

//check is a file exist or not
bool IsFileExist(const char *fileName);

//check is file empty or not
bool IsFileEmpty(const char *fileName);

#endif