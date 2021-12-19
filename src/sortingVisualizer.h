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
  setConsoleColour(FOREGROUND_RED);
  SV_Render();
  setConsoleColour(FOREGROUND_BLUE);
  start = clock();
  while (running)
  {
    stop = clock();
    if (stop - start >= 10) {
      start = clock();
      SV_Update();
      SV_Render();
    }
  }
  getch();
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
  srand(time(NULL));

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
          printf("%c", BLOCK);
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
  // system("cls");
  // cls();
  // printf("%s", display);
  // free(display);
  Sleep(1);
}