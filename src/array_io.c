#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "utils.h"
#include "array_io.h"


typedef enum {OUTSIDE_WORD, INSIDE_WORD} state;


state handle_outside_word(int c, element *elem_ptr, 
			  int *word_index_ptr);
state handle_inside_word(int c, element *elem_ptr, int *word_index_ptr, 
			 element buffer[], int *counter_ptr);
void copy_element_to_buffer(element buffer[], int buffer_index, element *elem_ptr);


void print_array(element buffer[], int size, char *delimiter){
  /*
    Print element values according to their type to stdout.	
  */
  int i;
  element temporary_element;
  for (i=0; i < size; i++){
    switch(buffer[i].type){
      case INTEGER:
	printf("%d", buffer[i].integer);
	break;
      case DECIMAL:
	printf("%f", buffer[i].decimal);
	break;
      case WORD:
	printf("%s", buffer[i].word);
	break;
    }
    printf("%s", delimiter);
  }
}


int read_input(element buffer[]){
  /* 
     Read space-delimited array elements from stdout.
     Return number of elements.
     TODO: decimal numbers
  */

  int c;
  
  int buffer_counter = 0;
  
  element temporary_element;
  
  int word_index = 0;
  
  state state = OUTSIDE_WORD;
  
  while ((c = getchar()) != EOF)
    switch (state){
      case OUTSIDE_WORD:
	state = handle_outside_word(c, &temporary_element, &word_index);
	break;
      case INSIDE_WORD:
	state = handle_inside_word(c, &temporary_element, &word_index, 
				   buffer, &buffer_counter);
	break;
      default: assert(0);       /* Never should get here */
    }
  return buffer_counter;
}


state handle_outside_word(int c, element *elem_ptr, 
			  int *word_index_ptr){
  state state = OUTSIDE_WORD;
  if (isdigit(c)) {
      state = INSIDE_WORD;
      elem_ptr->word[(*word_index_ptr)++] = c;
      elem_ptr->type = INTEGER;
  } else if (isalpha(c) || c == '_' || c == '-') {
      state = INSIDE_WORD;
      elem_ptr->word[(*word_index_ptr)++] = c;
      elem_ptr->type = WORD;
  }
  return state;
}


state handle_inside_word(int c, element *elem_ptr, int *word_index_ptr, 
			 element buffer[], int *counter_ptr){
  state state = INSIDE_WORD;
  if (isdigit(c)) {
      if (*word_index_ptr > WORD_SIZE) {
	fprintf(stderr, "Too long word %s\n", elem_ptr->word);
	exit(-1);
      }
      elem_ptr->word[(*word_index_ptr)++] = c;
  } else if (isalpha(c) || c == '_' || c == '-') {
      if (*word_index_ptr > WORD_SIZE) {
	fprintf(stderr, "Too long word %s\n", elem_ptr->word);
	exit(-1);
      }
      elem_ptr->word[(*word_index_ptr)++] = c;
      elem_ptr->type = WORD;
  } else {
    state = OUTSIDE_WORD;
    
    if (*counter_ptr + 1 > MAXSIZE) {
      fprintf(stderr, "Too many elements to sort (exceeds %d)\n", MAXSIZE);
      exit(-1);
    }
    elem_ptr->word[*word_index_ptr] = '\0';
    #ifdef DEBUG
      printf("[DEBUG] %s is %s\n", STRINGIFY(elem_ptr->word), elem_ptr->word);
    #endif
    /* Push copied and prepared element to the buffer */
    copy_element_to_buffer(buffer, *counter_ptr, elem_ptr); 
    /* Reset word index */
    *word_index_ptr = 0;
    (*counter_ptr)++;
  }
  return state;
}


void copy_element_to_buffer(element buffer[], int buffer_index, element *elem_ptr){
  switch(elem_ptr->type){
    case INTEGER:
      buffer[buffer_index].integer = atoi(elem_ptr->word);
      break;
    case DECIMAL:
      buffer[buffer_index].decimal = atof(elem_ptr->word);
      break;
    case WORD:
      strcpy(buffer[buffer_index].word, elem_ptr->word);
      break;
  }
  buffer[buffer_index].type = elem_ptr->type;
}

void swap_elements(element *a, element *b){
  assert(sizeof(*a) == sizeof(*b));
  element tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

bool compare_elements(element *a, element *b){
  /* Comparison function.
   * Return TRUE if first argument is
   * less than the second one, and FALSE otherwise.
   * WORD is considered greater than INTEGER and DECIMAL
  */

    switch(a->type){
      case INTEGER:
	  switch(b->type){
	      case INTEGER:
		return (a->integer > b->integer) ? false : true;
		break;
	      case DECIMAL:
		return (a->integer > b->decimal) ? false : true;
		break;
	      case WORD:
		return true;
		break;
	  }
          break;
      case DECIMAL:
	  switch(b->type){
	      case INTEGER:
		return (a->decimal > b->integer) ? false : true;
		break;
	      case DECIMAL:
		return (a->decimal > b->decimal) ? false : true;
		break;
	      case WORD:
		return true;
		break;
	  }
          break;
      case WORD:
          switch(b->type){
	      case INTEGER:
	      case DECIMAL:
		return false;
		break;
	      case WORD:
		return (strcmp(a->word, b->word) > 0) ? false : true;
		break;
	  }
          break;
   }
}

