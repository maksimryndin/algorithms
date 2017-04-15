#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "utils.h"
#include "array_io.h"


bool compare(element *, element *);
void swap(element *, element *);


int main(int argc, char *argv[]){
  /* Sort provided elements with insertion sort algorithm. 
   Get elements as command line args and print to stdout sorted array.
   Type check is performed.
   */
  int size = 0;
  bool descending = false;
  // Read command line args
	/*
  while (--argc > 0)
    switch(argv[argc]){
      case "--desc":
	descending = true;
	break;
    }*/
  
  element *buffer = (element *) ec_malloc(MAXSIZE * sizeof(element));
  memset(buffer, '\0', sizeof(buffer));
  size = read_input(buffer);
  print_array(buffer, size);
  free(buffer);
  return 0;
}



// Use strcmp for char arrays
bool compare(element *a, element *b){
  /* Comparison function.
   * Return TRUE if first argument is 
   * greater than the second one, and FALSE otherwise.
  */
  
}

void swap(element *a, element *b){
  element tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}
