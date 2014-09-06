#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


int main (int argc, char *argv[])
{

  // validate number of arguments
  if (argc > 3) {

    printf("[Error: too many arguments]\n>> Usage $ ./cp <file> <file>\n");
    exit(0);

  } else if (argc < 3) {

    printf("[Error: too few arguments]\n>> Usage $ ./cp <file> <file>\n");
    exit(0);

  } else {

    int fileInput, fileOutput;

    // open file
    fileInput = open(argv[1], O_RDONLY);

    // open returns a filedescriptor (int), returns -1 on failure
    if (fileInput >= 0) {

      // create new file
      fileOutput = open(argv[2], O_CREAT | O_EXCL | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IXUSR |
                                 S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);

      // if open didn't fail
      if (fileOutput >= 0) {
        char buffer[256];
        size_t copied;
        int totalCopied;

        // read 256 bytes at a time
        copied = read(fileInput, buffer, 256);
        totalCopied = copied;

        while (copied > 0) {
          write(fileOutput, buffer, copied);
          copied = read(fileInput, buffer, 256);
          totalCopied += copied;
        }

        printf("copied %d bytes", totalCopied);
        close(fileOutput);

      } else {

        // can't create a file w/ same name
        fprintf(stderr, "[Error: %s already exists\n]", argv[2]);
        close(fileInput);
        return 1;

      }

      close(fileInput);

    } else {

      // open failure
      fprintf(stderr, "[Error: %s does not exist\n]", argv[1]);
      return 1;

    }

  }

  return 0;
}
