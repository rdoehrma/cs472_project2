#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char *argv[])
{
  const int SIZE = 4096;

  const char* name = "OS";
  char message1[1000] = "testing";
  
  int n;
  n = atoi(argv[1]);
  char fibStr[100];
  sprintf(fibStr, "%d", n);
  strcpy(message1, fibStr);

  int shm_fd; 
  void* ptr; 
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, SIZE);
  ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

  //writing time
  sprintf(ptr, "%s", message1);

  int pid = fork();
  if (pid == 0)
    { 
      execlp("./fib_shm_child", "fib_shm_child", NULL);
    }
  wait(5);
  
  printf("%s", (char*)ptr);
  return 0;
}
