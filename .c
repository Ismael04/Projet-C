
#ifndef CDATAFRAME_H
#define CDATAFRAME_H

#include "column.h"  // Include the definition of Column

// CDataframe structure
typedef struct {
    Column **columns;    // Array of pointers to Columns
    int num_columns;     // Number of columns
    int capacity;        // Capacity of the dataframe (for dynamic resizing)
} CDataframe;

// Function prototypes for CDataframe
CDataframe* create_cdataframe(void);
void fill_cdataframe_with_input(CDataframe *df);
void hard_fill_cdataframe(CDataframe *df);
void display_cdataframe(const CDataframe *df);
void add_column(CDataframe *df, Column *col);
void delete_column_from_dataframe(CDataframe *df, const char *title);
void free_cdataframe(CDataframe *df);

#endif //CDATAFRAME_H
