#ifndef ARRAY_IO_H
#define ARRAY_IO_H

#define MAXSIZE 1000
#define WORD_SIZE 100

#define STRINGIFY(x) #x


typedef enum {INTEGER, DECIMAL, WORD} type;

/* Struct to hold sortable element */
typedef struct _element {
  char word[WORD_SIZE];
  int integer;
  double decimal;
  type type;
} element;


void print_array(element buffer[], int size, char *delimiter);
int read_input(element buffer[]);
void swap_elements(element *a, element *b);
bool compare_elements(element *a, element *b);

#endif /* ARRAY_IO_H */
