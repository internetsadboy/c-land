#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define BUFF_SIZE 2048

int main (void)
{
  TCHAR buffer[BUFF_SIZE];
  TCHAR input[BUFF_SIZE];

  char *pos;

  PROCESS_INFORMATION process_info;
  STARTUPINFO startup_info;

  ZeroMemory(&startup_info, sizeof(startup_info));
  startup_info.cb = sizeof(startup_info);

  ZeroMemory(&process_info, sizeof(process_info));

  while (1)
  {
    printf("Myshell> ");

    // collect user input
    fgets(input, BUFF_SIZE, stdin);

    // \n terminates strings
    if ((pos = strchr(input, '\n')) != NULL) *pos = '\0';

    // exit kills the process
    if (!strncmp(input, "exit", 4)) break;

    // prepend cmd /C to expose cmd commands
    sprintf(buffer, "cmd /C %s", input);

    // create process, handle error
    if (!CreateProcess(
		    NULL,
		    buffer,
		    NULL,
		    NULL,
		    FALSE,
		    0,
		    NULL,
		    NULL,
		    &startup_info,
        &process_info
		 )) {
      fprintf(stderr, "[Error] failed to fork process: (%d)\n", GetLastError());
    }

    WaitForSingleObject(process_info.hProcess, INFINITE);

    // close handles
    CloseHandle(process_info.hProcess);
    CloseHandle(process_info.hThread);
  }

  return 0;
}
