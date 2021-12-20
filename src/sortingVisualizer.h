#include "stuff.h"

int array[WIDTH];
int arrIndex=0;

clock_t start, stop;

void SV_Render();
void SV_Update();
void SV_Initialize();

int SV_Run()
{
  SV_Initialize();
  setConsoleColour(RED);
  SV_Render();
  // setConsoleColour(BLUE);
  start = clock();
  while (running)
  {
    stop = clock();
    if (stop - start >= 20) {
      start = clock();
      SV_Update();
      SV_Render();
    }
  }
  setConsoleColour(GREEN);
  buffer = malloc(sizeof(char*)*HEIGHT);
  for (int i=0; i<HEIGHT; i++)
  {
    buffer[i] = malloc(sizeof(char)*WIDTH);
  }
  SV_Render();
  while (getch()!='a'){}
  return 0;
}

void SV_Initialize()
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

void SV_Update()
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

void SV_Render()
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