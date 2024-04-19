#ifndef COLUMN_H
#define COLUMN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a column (4.1)
typedef struct {
    char *title;         // Title of the column (4.1.1)
    int *data;           // Pointer to integer array (4.1.1)
    int capacity;
    unsigned int size;   // Logical size of the column (4.1.1)
    unsigned int max_size;// Physical size of the array (4.1.1)
} Column;

// Function declarations
Column *create_column(const char *title); // (4.1.1)
void insert_value(Column *column, int value); // (4.1.2)
void print_col(const Column *column); // (4.1.4)
void delete_column(Column **column); // (4.1.3)

// Additional functionality (4.1.5)
int count_value(const Column *column, int value); // Counts occurrences of a value
int value_at_index(const Column *column, unsigned int index); // Returns the value at a given index
int find_max(const Column *column); // Finds the maximum value in the column
int count_less_than(const Column *column, int x); // Finds the values less than x
int count_equals_x(const Column *column, int x);  // Finds the values equal to x

#endif
