//
// By Penguin, 2014.7
//

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <setjmp.h>

#define FILE_LENGTH 0x1000

static sigjmp_buf jmpbuf;
//pthread_t thread_id[2];

void sigsegv_handler(int sig_num)
{
//  int jmpbufno;

//  pthread_t tid;
//  tid = pthread_self();
//  if (tid == thread_id[0])
//    jmpbufno = 1;
//  else 
//    jmpbufno = 2;

//  printf("This is SIGSEGV handler : pid %d, thread id %lu, jmpbuf %lx, jmpbufno %d\n", getpid(), tid, (unsigned long)jmpbuf, jmpbufno);
//  siglongjmp(jmpbuf, jmpbufno);
  siglongjmp(jmpbuf, 1);
//  pthread_cancel(tid);
}

void sigbus_handler(int sig_num)
{
//  int jmpbufno;
//  pthread_t tid;
//  tid = pthread_self();
//  if (tid == thread_id[0])
//    jmpbufno = 1;
//  else 
//    jmpbufno = 2;
//  printf("This is SIGBUS handler : pid %d, thread id %lu, jmpbuf %lx, jmpbufno %d\n", getpid(), tid, (unsigned long)jmpbuf, jmpbufno);
//  siglongjmp(jmpbuf, jmpbufno);
  siglongjmp(jmpbuf, 1);
//  pthread_cancel(tid);
}

void *thread_func1(void *threadnum)
{
  int i;
  pthread_t tid;

  for (i = 0; i < 10; i++)
  {
    tid = pthread_self();
    printf("This is thread %d, thread id %lu : %d\n", *(int *)threadnum, tid, i);
    sleep(1);
  }
}

void *thread_func2(void *threadnum)
{
  int i;
  pthread_t tid;
  int threadno;
  sigset_t set;

  threadno = *(int*)threadnum;
  tid = pthread_self();
  printf("This is thread %d, thread id %lu\n", threadno, tid);
  
  if (threadno != 1)
  {
//    sigemptyset(&set);
//    sigaddset(&set, SIGBUS);
//    sigaddset(&set, SIGSEGV);
//    if (pthread_sigmask(SIG_BLOCK, &set, NULL))
//      printf("block SIGBUS and SIGSEGV failed\n");
    signal(SIGBUS, SIG_IGN);
    signal(SIGSEGV, SIG_IGN);
  }

  if(sigsetjmp(jmpbuf, 1))
  {
    printf("return from siglongjmp\n");
  }

//  thread_id[threadno - 1] = tid;
  for (i = 0; i < 3; i++)
  {
    printf("This is thread %d, thread id %lu : %d\n", threadno, tid, i);
    sleep(1);
  }
//  char *pc = (char*)0x00001111;
//  *pc= 7;

  int fd;
  char *fm;

  fd = open("test", O_RDWR | O_CREAT);
  fm = (char*)mmap(NULL, FILE_LENGTH, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  if (fm == MAP_FAILED)
  {
    printf("mmap failed\n");
  }
  close(fd);
  strcpy(fm, "this is a test\n");
//  __asm__("pushf\norl $0x40000, (%rsp)\npopf");
  
  for (i = 0; i < 2; i++)
  {
    tid = pthread_self();
    printf("After SIGSEGV This is thread %d, thread id %lu : %d\n", *(int *)threadnum, tid, i);
    sleep(1);
  }
}

int main()
{
  pthread_t thread1_id;
  pthread_t thread2_id;
 
  struct sigaction sa1;
  struct sigaction sa2;

  sa1.sa_handler = &sigsegv_handler;
  sigaction(SIGSEGV, &sa1, NULL);
  sa2.sa_handler = &sigbus_handler;
  sigaction(SIGBUS, &sa2, NULL);
 
//  if(sigsetjmp(jmpbuf, 1))
//  {
//    printf("return from siglongjmp\n");
//  }

  printf("MAIN pid %d, tid %lu\n", getpid(), pthread_self());

//  sleep(10);
  
  int num1 = 1;
//  pthread_create(&thread1_id, NULL, &thread_func1, &num1);
  pthread_create(&thread1_id, NULL, &thread_func2, &num1);

  sleep(6);

  int num2 = 2;
  pthread_create(&thread2_id, NULL, &thread_func2, &num2);

  pthread_join(thread1_id, NULL);
  pthread_join(thread2_id, NULL);
}
