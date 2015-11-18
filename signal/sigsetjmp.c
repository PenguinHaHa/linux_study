#include <setjmp.h>
#include <time.h>
#include <signal.h>

static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

int main()
{
  struct sigaction sa1;
  struct sigaction sa2;

  sa1.sa_handler = &sigusr1_handle;
  sigaction(SIGUSR1, &sa1, NULL);
  sa2.sa_handler = &sigusr2_handle;
  sigaction(SIGUSR1, &sa2, NULL);
 
  canjump = 1;

  for (;;)
    pause();

  return 0;
}

static void sigusr1_handle(int signo)
{

}
