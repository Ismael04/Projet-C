#include "column.h"
#include "cdataframe.h"
// Function to create a column (4.1.1)
Column *create_column(const char *title) {
    Column *col = malloc(sizeof(Column));
    if (col == NULL) return NULL;

    col->title = strdup(title);
    col->size = 0;
    col->max_size = 10; // Start with an initial capacity of 10
    col->data = malloc(col->max_size * sizeof(int));
    if (col->data == NULL) {
        free(col->title);
        free(col);
        return NULL;
    }
    return col;
}

// Function to insert a value into a column (4.1.2)
void insert_value(Column *column, int value) {
    if (column->size == column->max_size) {
        int *new_data = realloc(column->data, (column->max_size + 10) * sizeof(int));
        if (new_data == NULL) return;
        column->data = new_data;
        column->max_size += 10;
    }
    column->data[column->size++] = value;
}

// Function to print the content of a column (4.1.4)
void print_col(const Column *column) {
    printf("Column: %s\n", column->title);
    for (unsigned int i = 0; i < column->size; i++) {
        printf("[%u] %d\n", i, column->data[i]);
    }
}

// Function to free a column from memory (4.1.3)
void delete_column(Column **column) {
    if (column == NULL || *column == NULL) return;
    free((*column)->data);
    free((*column)->title);
    free(*column);
    *column = NULL;
}

// Function to count occurrences of a specific value (4.1.5)
int count_value(const Column *column, int value) {
    int count = 0;
    for (unsigned int i = 0; i < column->size; i++) {
        if (column->data[i] == value) {
            count++;
        }
    }
    return count;
}

// Function to check value at a specific index (4.1.5)
int value_at_index(const Column *column, unsigned int index) {
    if (index < column->size) {
        return column->data[index];
    } else {
        printf("Index out of bounds.\n");
        return -1; // Indicative error value
    }
}

// Function to find the maximum value in the column (4.1.5)
int find_max(const Column *column) {
    if (column->size == 0) return -1; // Indicative error if column is empty

    int max = column->data[0];
    for (unsigned int i = 1; i < column->size; i++) {
        if (column->data[i] > max) {
            max = column->data[i];
        }
    }
    return max;
}
// Function to count values less than a specified value 'x' (4.1.5)
int count_less_than(const Column *column, int x) {
    int count = 0;
    for (unsigned int i = 0; i < column->size; i++) {
        if (column->data[i] < x) {
            count++;
        }
    }
    return count;
}

// Function to count the number of values equal to 'x' (4.1.5)
int count_equals_x(const Column *column, int x) {
    int count = 0;
    for (unsigned int i = 0; i < column->size; i++) {
        if (column->data[i] == x) {
            count++;
        }
    }
    return count;
}

// Implementations for Column functions
// Function to create a new column
Column* create_cdataframe_column(const char *title) {
    Column *col = malloc(sizeof(Column));
    if (col) {
        col->title = strdup(title);
        col->data = NULL;
        col->size = 0;
        col->capacity = 0;
    }
    return col;
}

void insert_cdataframe_value(Column *col, int value) {
    if (col->size >= col->capacity) {
        int new_capacity = col->capacity == 0 ? 4 : col->capacity * 2;
        int *new_data = realloc(col->data, new_capacity * sizeof(int));
        if (!new_data) return;
        col->data = new_data;
        col->capacity = new_capacity;
    }
    col->data[col->size++] = value;
}

void print_cdataframe_col(const Column *col) {
    printf("%s: ", col->title);
    for (int i = 0; i < col->size; i++) {
        printf("%d ", col->data[i]);
    }
    printf("\n");
}


// Implementations for CDataframe functions
CDataframe* create_cdataframe() {
    CDataframe *df = malloc(sizeof(CDataframe));
    if (!df) return NULL;
    df->columns = NULL;
    df->num_columns = 0;
    df->capacity = 0;
    return df;
}

void fill_cdataframe_with_input(CDataframe *df) {
    if (!df) return;

    int numColumns = 0;
    printf("Enter the number of columns to add: ");
    scanf("%d", &numColumns);

    for (int i = 0; i < numColumns; i++) {
        char title[100];
        printf("Enter title for column %d: ", i + 1);
        scanf("%s", title);

        Column *newColumn = create_column(title);
        if (!newColumn) continue; // Continue on failure to allocate new column

        int numValues;
        printf("Enter the number of values for column '%s': ", title);
        scanf("%d", &numValues);

        for (int j = 0; j < numValues; j++) {
            int value;
            printf("Enter value %d for column '%s': ", j + 1, title);
            scanf("%d", &value);
            insert_value(newColumn, value);
        }

        add_column(df, newColumn);
    }
}

void hard_fill_cdataframe(CDataframe *df) {
    if (!df) return;

    // Example of predefined data
    Column *col1 = create_column("Random Column 1");
    int values1[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < sizeof(values1) / sizeof(values1[0]); i++) {
        insert_value(col1, values1[i]);
    }
    add_column(df, col1);

    Column *col2 = create_column("Random Column 2");
    int values2[] = {5, 15, 25, 35, 45};
    for (int i = 0; i < sizeof(values2) / sizeof(values2[0]); i++) {
        insert_value(col2, values2[i]);
    }
    add_column(df, col2);
}

void display_cdataframe(const CDataframe *df) {
    for (int i = 0; i < df->num_columns; i++) {
        print_col(df->columns[i]);
    }
}

void add_column(CDataframe *df, Column *col) {
    if (df->num_columns >= df->capacity) {
        int new_capacity = df->capacity == 0 ? 4 : df->capacity * 2;
        Column **new_columns = realloc(df->columns, new_capacity * sizeof(Column *));
        if (!new_columns) return;
        df->columns = new_columns;
        df->capacity = new_capacity;
    }
    df->columns[df->num_columns++] = col;
}

// Function to delete a column from the dataframe by title
void delete_column_from_dataframe(CDataframe *df, const char *title) {
    if (!df || !title) return;
    for (int i = 0; i < df->num_columns; i++) {
        if (strcmp(df->columns[i]->title, title) == 0) {
            // Found the column, delete and remove from array
            delete_column(&(df->columns[i]));  // Assuming delete_column takes Column**
            // Shift remaining columns left
            for (int j = i; j < df->num_columns - 1; j++) {
                df->columns[j] = df->columns[j + 1];
            }
            df->num_columns--;
            break;
        }
    }
}

// Function to free the entire dataframe
void free_cdataframe(CDataframe *df) {
    if (!df) return;
    // Free all columns
    for (int i = 0; i < df->num_columns; i++) {
        delete_column(&(df->columns[i]));  // Ensure this matches the expected function signature
    }
    free(df->columns);
    free(df);
}
