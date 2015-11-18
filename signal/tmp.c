#include <stdio.h>
#include <signal.h>
#include <errno.h>

void sigint_handler(int signal_number)
{
  printf("SIGINT\n");
  printf("errno %d\n", errno);
  sleep(2);
}

int main()
{
  struct sigaction sa;

  sa.sa_handler = &sigint_handler;
  sigaction(SIGBUS, &sa, NULL);


  while(1)
  {
    printf("wait for SIGINT\n");
    sleep(2);
  }
  /*
  printf("aaa\n");
  char *pc = (char*)0x00001111;
  *pc= 7;
  printf("bbb\n");*/

  return 0;
}
