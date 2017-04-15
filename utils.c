#include "utils.h"


void fatal(char *message){
  /* Display an error message and exit */
  
  char error_message[100];
  strcpy(error_message, "[!!] Fatal Error ");
  strncat(error_message, message, 83);
  perror(error_message);
  exit(-1);
}


void *ec_malloc(unsigned int size){
  /* An error-checked malloc() wrapper */
  void *ptr;
  ptr = malloc(size);
  if (ptr == NULL)
    fatal("in ec_malloc() on memory allocation");
  return ptr;
}

