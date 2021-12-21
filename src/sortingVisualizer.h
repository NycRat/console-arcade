#include "stuff.h"

int array[WIDTH];
int arrIndex=0;

void SV_render();
void SV_update();
void SV_initialize();

int SV_run()
{
  SV_initialize();
  setConsoleColour(RED);
  SV_render();
  // setConsoleColour(BLUE);
  gettimeofday(&begin, NULL);
  while (running)
  {
    gettimeofday(&end, NULL);
    if ((end.tv_sec - begin.tv_sec) * 1000000 + end.tv_usec - begin.tv_usec>= 20000) {
      gettimeofday(&begin, NULL);
      SV_update();
      SV_render();
    }
    setCursorPosition(0,0);
  }
  setConsoleColour(GREEN);
  buffer = malloc(sizeof(char*)*HEIGHT);
  for (int i=0; i<HEIGHT; i++)
  {
    buffer[i] = malloc(sizeof(char)*WIDTH);
  }
  SV_render();
  while (getch()!='a'){}
  return 0;
}

void SV_initialize()
{
  running=1;
  buffer = malloc(sizeof(char*)*HEIGHT);
  for (int i=0; i<HEIGHT; i++)
  {
    buffer[i] = malloc(sizeof(char)*WIDTH);
  }
  cls();
  srand(time(NULL));

  arrIndex=0;
  for (int i=0; i<WIDTH; i++)
  {
    array[i] = rand()%HEIGHT+1;
  }
}

void SV_update()
{
  for (int i=arrIndex+1; i<WIDTH; i++)
  {
    if (array[i]<array[arrIndex])
    {
      int t=array[i];
      array[i]=array[arrIndex];
      array[arrIndex]=t;
    }
  }
  arrIndex++;
  if (arrIndex>=WIDTH)
  {
    running=0;
  }
}

void SV_render()
{
  for (int y=0; y<HEIGHT; y++)
  {
    for (int x=0; x<WIDTH; x++)
    {
      if (array[x]>=HEIGHT-y)
      {
        if (buffer[y][x] != '#')
        {
          setCursorPosition(x,y);
          printf("%c", BLOCK+2);
        }
        buffer[y][x]='#';
      }
      else
      {
        if (buffer[y][x] == 'L')
        {
          setCursorPosition(x,y);
          printf(" ");
          buffer[y][x] = ' ';
        }
        if (buffer[y][x] == '#')
        {
          setCursorPosition(x,y);
          printf(" ");
          buffer[y][x]='L';
        }
      }
    }
  }
  buffer[HEIGHT-1][WIDTH]='\0';
  setCursorPosition(0,0);
}