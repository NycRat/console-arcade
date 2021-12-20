#include "stuff.h"


int FB_Pipe1_Y;
int FB_Pipe1_X;

void FB_Render();
void FB_Update();
void FB_Initialize();

int FB_Run()
{
  FB_Initialize();
  while (running)
  {
    gettimeofday(&FRAME_begin, NULL);
    FB_Update();
    FB_Render();
    dt=0;
    while (dt<=0)
    {
      gettimeofday(&FRAME_end, NULL);
      dt = ((FRAME_end.tv_sec - FRAME_begin.tv_sec) * 1000000 + (FRAME_end.tv_usec - FRAME_begin.tv_usec));
      dt /= 1000;
    }
    tempTime+=dt;
    if (tempTime>=1000)
    {
      tempTime-=1000;
    }
  }
}

void FB_Initialize()
{
  running = 1;
  free(buffer);
  buffer = malloc(sizeof(char *) * HEIGHT);
  for (int i = 0; i < HEIGHT; i++)
  {
    buffer[i] = malloc(sizeof(char) * WIDTH);
  }
  cls();
  srand(time(NULL));
}

void FB_Update()
{

}

void FB_Render()
{
}