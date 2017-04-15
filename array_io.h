#ifndef ARRAY_IO_H
#define ARRAY_IO_H

#define MAXSIZE 5
#define WORD_SIZE 100

#define STRINGIFY(x) #x


typedef enum {INTEGER, DECIMAL, WORD} type;
typedef enum {OUTSIDE_WORD, INSIDE_WORD} state;

// Struct to hold sortable element
typedef struct {
  char word[WORD_SIZE];
  int integer;
  double decimal;
  type type;
} element;


void print_array(element buffer[], int size);
int read_input(element buffer[]);

#endif /* ARRAY_IO_H */
