#include <stdio.h>


void putstring (char *s)
{
  while ('\0' != *s)
  {
    printf("\n %d ", s);
    putchar(*s);
    s++;
  }
}


// recursive implementation
void putreverse (char *s)
{
  if(*s != '\0') {
    putreverse(s + 1);
  }

  putchar(*s);
}


// iterative implementation
void putreverseit (char *s)
{
  int l = stringlen(s);

  while(l >= 0)
  {
    putchar(*(s + l));
    l--;
  }
}


int stringlen (char *s)
{
  char *i;
  i = s;

  while('\0' != *s)
  {
    s++;
  }

  return (int) s - (int) i;
}


int main (int argc, char *argv[])
{
  char str[18] = "hello cruel world";

  putstring(str);
  putchar('\n');

  putreverse(str);
  putchar('\n');

  printf("[%d]\n", stringlen(str));

  putreverseit(str);
  putchar('\n');

  return 0;
}
