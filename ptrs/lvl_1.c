#include <stdio.h>


// basic example creating/using pointers
void beep()
{
  char ch, *chptr, *ptr;

  ch = 'c';
  chptr = &ch;
  ptr = "I am a string";

  int i, *intptr;

  i = 20;
  intptr = &i;

  float f, *fptr;

  f = 1.2000;
  fptr = &f;

  printf("[%c] [%d] [%f] [%c] [%s]\n", *chptr, *intptr, *fptr, *ptr, ptr);

  return;
}


// pointer example using a struct
void boop()
{
  struct st {
    int a;
    char ch;
  };

  struct st obj;
  struct st *stobj = &obj;

  stobj->a = 5;
  stobj->ch = 'a';

  printf("=======================================\n");
  printf("[%d] [%c]\n", stobj->a, stobj->ch);
}


int main (void)
{
  beep();
  boop();
  return 0;
}
