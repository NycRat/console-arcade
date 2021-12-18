#include "stuff.h"
#include <sys/time.h>

struct timeval begin,end;

long total=0;;

int runPong()
{
  while (running)
  {
    gettimeofday(&begin, NULL);
    system("cls");
    if (GetAsyncKeyState(VK_ESCAPE))
    {
      running = 0;
    }
    if (GetAsyncKeyState(0x57))
    {
      printf("%ld\n", (end.tv_sec-begin.tv_sec)*1e6 + (end.tv_usec-begin.tv_usec));
      // printf("things: %ld\n", end.tv_sec*1e6+end.tv_usec);
    }
    render();
    gettimeofday(&end, NULL);
  }
  return 0;
}