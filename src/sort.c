#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>

#include "utils.h"
#include "array_io.h"


void sort(element buffer[], int size);


int main(int argc, char *argv[]){
  /* Sort provided elements with insertion sort algorithm. 
   Get elements as command line args and print to stdout sorted array.
   Type check is performed.
   */
  int size = 0;
  int option =  0;
  bool descending = false;

  while ((option = getopt(argc, argv, "d")) != -1){
    switch(option){
      case 'd':
	descending = true;
	break;
      default:
        printf("Usage: %s [d]\n", argv[0]);
        break;
    }
  }
  
  element *buffer = (element *) ec_malloc(MAXSIZE * sizeof(element));
  memset(buffer, '\0', sizeof(buffer));
  size = read_input(buffer);
  sort(buffer, size);
  printf("\nSorted array:\n");
  print_array(buffer, size, " ");
  printf("\n");
  free(buffer);
  return 0;
}


void sort(element buffer[], int size){
  /* Insertion sort */
  int i, j;
  for (i = 1; i < size; i++){
	print_array(buffer, size, " ");
	printf("\n");
	for (j = 0; j < i; j++) {
		if (!compare_elements(&buffer[j], &buffer[i])){
			swap_elements(&buffer[i], &buffer[j]);
		}
	}
  }
}

