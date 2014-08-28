#include <stdlib.h>
#include <stdio.h>


char *readFile (char *fileName)
{
  FILE *file = fopen(fileName, "r");
  char *code;
  size_t n = 0;
  int c;

  // can't open file
  if (file == NULL) {
    return NULL;
  }

  code = malloc(1000);

  while ((c = fgetc(file)) != EOF)
  {
    code[n++] = (char) c;
  }

  // terminate w/ the null character
  code[n] = '\0';

  return code;
}


int main (int argc, char *argv[])
{
  char *content = readFile("b64_alphabet.txt");
  printf("%s", content);
}
