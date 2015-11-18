#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define FILE_LENGTH 0x1000

int main()
{
  int fd;
  char *fm;

  fd = open("test", O_RDWR | O_CREAT);
  fm = (char*)mmap(NULL, FILE_LENGTH, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  if (fm == MAP_FAILED)
  {
    exit(1);
  }
  close(fd);
  strcpy(fm, "this is a test\n");
  return 0;
}
