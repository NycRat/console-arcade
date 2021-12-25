#include "../stuff.h"
#define SNAKE_DELAY 200

void SNAKE_initialize();
void SNAKE_render();
void SNAKE_processInput();

int SNAKE_run()
{
  SNAKE_initialize();
  gettimeofday(&begin, NULL);
  while (running)
  {
    Sleep(1);
    gettimeofday(&end, NULL);
    double temp = (end.tv_sec - begin.tv_sec) * 1000000 - (end.tv_usec - begin.tv_usec);
    temp /= 1000;
    if (temp > SNAKE_DELAY)
    {
      SNAKE_processInput();
      SNAKE_render();
    }
  }
}

void SNAKE_processInput()
{
  Sleep(1);
  if (GetAsyncKeyState(0x00))
  {
  }
  if (GetAsyncKeyState(0x00))
  {
  }
  if (GetAsyncKeyState(0x00))
  {
  }
  if (GetAsyncKeyState(0x00))
  {
  }
}

void SNAKE_initialize()
{
}

void SNAKE_render()
{
  for (int y = 0; y < HEIGHT; y++)
  {
    for (int x = 0; x < WIDTH; x++)
    {
    }
  }
}
