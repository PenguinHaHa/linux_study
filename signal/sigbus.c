#include <stdio.h>
#include <signal.h>

void sigbus_handler(int signal_number)
{
  printf("SIGBUS\n");
  sleep(2);
}

int main()
{
  int apple = 0x12345678;
  int *fruit;

  struct sigaction sa;

//  __asm__("pushf\norl $0x40000, (%rsp)\npopf");
  
  sa.sa_handler = &sigbus_handler;
  sigaction(SIGBUS, &sa, NULL);

  fruit = &apple;
  printf("apple was %x\n", apple);
  printf("fruit is %x\n", *fruit);

  fruit = (int *)(((char*)fruit) + 1);
  printf("apple was %x\n", apple);
  printf("fruit is %x\n", *fruit);

  printf("aaa\n");
  while(1)
  {
    printf("wait be killed :(\n");
    sleep(5);
  }
  printf("bbb\n");
  
  return 0;
}
