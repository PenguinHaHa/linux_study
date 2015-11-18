#include <stdio.h>
#include <signal.h>

void sigbus_handler(int signal_number)
{
  printf("SIGBUS\n");
  sleep(2);
}

void sigsegv_handler(int signal_number)
{
  printf("SIGSEGV\n");
  sleep(2);
}

int main()
{
  struct sigaction sa1;
  struct sigaction sa2;

  sa1.sa_handler = &sigbus_handler;
  sigaction(SIGBUS, &sa1, NULL);

  sa2.sa_handler = &sigsegv_handler;
  sigaction(SIGSEGV, &sa2, NULL);
  
  sleep(2);

  __asm__("pushf\n"
          "orl $(1 << 18), (%rsp)\n"
          "popf");

  printf("aaa\n");
  while(1)
  {
    printf("wait be killed :(\n");
    sleep(5);
  }
  printf("bbb\n");

  return 0;
}
