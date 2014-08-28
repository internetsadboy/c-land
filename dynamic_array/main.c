#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[])
{
  int i;

  int *p; // reference var to access dynamically created array of elements

  p = calloc(10, sizeof(int)); // make int array of 10 elements
                                  // calloc(nElem, nBytes)

  for ( i = 0; i < 10; i++ ) {
    *(p + i) = i;  // equivalent of array[i] in weakly typed lang (sets up dynamic access)
  }

  for ( i = 0; i < 10; i++ ) {
    printf("*(p + %d) = %d\n", i, *(p + i));
  }

  free(p); // un-reserve memory used by the array

  putchar('\n');

  return 0;
}
