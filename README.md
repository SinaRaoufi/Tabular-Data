# Tabular-Data
A simple tabular data console application that can be used in statistical analysis. :chart_with_upwards_trend:

This simple console application consists of a set of commands, each of which performs a specific task! The commands are described below.
## Commands
When you compile and run the program, `->` is displayed indicating that the program is waiting for commands to be entered.
- **create**

    You can create an empty table by entering the `create` command:  `create table_name 5`

The example above creates an empty table called table_name with 5 columns.
You can use this command to create any number of tables you want.
> **Note:** The names of the tables are unique and it is not possible to have two tables with the same names.


- **insert**

    You can insert a new row consisting of data to the table by entering the `insert` command:  `insert table_name [-56.32 123 0 20 1]`
> **Note:** To enter data, you must enter it in`[]`.Also, the number of data entered in  `[]` must be equal to the number of columns in the table.


- **display**

    Using command `display` , you can view the data in the table: `display table_name`

- **drop**

    Using command `drop`, you can delete a desired row from the table: `drop table_name 2`

The example above delete row 2 from the table with name table_name

- **merge**

    The command `merge` gets the name of two tables with the same number of columns and adds the data of the second table to the end of the first table: `merge table_name1 table_name2`

- **sort**

    The `sort` command gets the name of a table and the number of a column from it and sorts the table according to that column in ascending order: `sort table_name 0`
> **Note:** The number of columns starts from zero!

- **statistics**

    The command `statistics`, displays the minimum element, maximum element, sum, mean, variance, and standard deviation for each table column: `statistics table_name`

- **export**

    The command `export` saves your favorite table in a text file with your favorite name: `export table_name table.txt`

- **clear**
    The command `clear`, clear console screen.

- **exit**

    Exit the program.

# Requirements
- CMake
- C++ Compiler (GCC is recommended)

```
cmake . -B build
```
After the MakeFile was created:
```
make -C build
```

# Contributing
Your contributions are always welcome!
