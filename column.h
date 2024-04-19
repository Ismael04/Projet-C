#ifndef COLUMN_H
#define COLUMN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a column
typedef struct {
    char *title;          // Title of the column
    int *data;            // Pointer to the array of integer data
    unsigned int size;    // Logical size: number of values in the column
    unsigned int max_size;// Physical size: maximum capacity of the array
} Column;

// Function declarations
Column *create_column(const char *title);
void insert_value(Column *column, int value);
void print_col(const Column *column);
void delete_column(Column **column);
int count_value(const Column *column, int value); // Counts occurrences of a value
int value_at_index(const Column *column, unsigned int index); // Returns the value at a given index
int find_max(const Column *column); // Finds the maximum value in the column
int count_less_than(const Column *column, int x); // New function
int count_equals_x(const Column *column, int x);  // New function


#endif // COLUMN_H
