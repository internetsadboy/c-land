#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define BUFF_SIZE 2048

int main (void)
{
  char input[BUFF_SIZE], *myargv[64], *myarg, *pos;
  int status, argc;
  pid_t pid;


  while (911)
  {
    printf("Myshell> ");

    // collect user input
    fgets(input, BUFF_SIZE, stdin);

    // use \n to terminate strings
    if ((pos = strchr(input, '\n')) != NULL) *pos = '\0';

    // exit kills the process
    if (!strncmp(input, "exit", 4)) break;

    // forking error handler
    if ((pid = fork()) < 0)
    {
      fprintf(stderr, "[Error] failure to fork child process\n");
      break;
    }

    // successful fork
    if (pid == 0)
    {
      // tokenize string input
      myarg = strtok(input, " ");
      argc = 0;

      // add args to myargv array
      while (myarg != NULL)
      {
        myargv[argc] = myarg;
        myarg = strtok(NULL, " ");
        argc++;
      }

      myargv[argc] = NULL;

      // execute the user's args
      if (execvp(myargv[0], myargv) < 0)
      {
        fprintf(stderr, "[Error] invalid command\n");
        break;
      }
    }
    else
    {
      // listen for process event
      while (wait(&status) != pid);
    }
  }

  return 0;
}
