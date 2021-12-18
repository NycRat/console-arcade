#include <stdio.h>
#include <conio.h>
#include <windows.h>

int running = 1;

int main()
{
  while (running)
  {
    printf("xd");
    if (GetAsyncKeyState(VK_ESCAPE))
    {
      running = 0;
    }
  }
}