#include "stuff.h"

int array[WIDTH];
int arrIndex=0;
int running=1;

clock_t start, stop;

void render();
void update();
void initialize();

int runSorting()
{
  initialize();
  display = malloc((HEIGHT)*(WIDTH+1));
  setConsoleColour(FOREGROUND_RED);
  render();
  setConsoleColour(FOREGROUND_BLUE);
  start = clock();
  while (running)
  {
    stop = clock();
    if (stop - start >= 10) {
      start = clock();
      update();
      render();
    }
  }
  getch();
  return 0;
}

void initialize()
{
  srand(time(NULL));

  for (int i=0; i<WIDTH; i++)
  {
    array[i] = rand()%HEIGHT+1;
  }
}

void update()
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

void render()
{
  int t=0;
  for (int y=0; y<HEIGHT; y++)
  {
    for (int x=0; x<WIDTH; x++)
    {
      if (array[x]>=HEIGHT-y)
      {
        if (display[t] != '#')
        {
          setCursorPosition(x,y);
          printf("%c", 219);
        }
        display[t]='#';
      }
      else
      {
        if (display[t] != ' ')
        {
          setCursorPosition(x,y);
          printf("%c", 32);
        }
        display[t]=' ';
      }
      t++;
    }
    display[t]='\n';
    t++;
  }
  display[t]='\0';
  // system("cls");
  // cls();
  // printf("%s", display);
  // free(display);
  Sleep(1);
}