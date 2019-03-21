#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
  const int SIZE = 4096;
  const char* name = "OS";

  int shm_fd;
  void* ptr;

  shm_fd = shm_open(name, O_RDWR, 0666);

  ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
  int fibSum;
  int num1;
  int num2;
  int iterator;
  int fibNums;
  char test[100];
  char test2[4000];
  
  num1 = 0;
  num2 = 1;

  fibNums = atoi((char*)ptr);

  //Add  0,1 the 2 first numbers of the sequence to ptr
  sprintf(test, "%d, %d", num1, num2);
  strcat(test2, test);
 
  for(iterator = 0; iterator < fibNums - 2; iterator++)
    {
      fibSum = num1 + num2;
      sprintf(test, ", %d", fibSum);
      strcat(test2, test);
      num1 = num2;
      num2 = fibSum;      
    }
  sprintf(ptr,  "%s\n", test2);
  return 0;
}
