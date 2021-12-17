#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

const int arrSize = 80;
const int maxValue = 16;
int array[arrSize];
int arrIndex=0;
int running=1;

clock_t start, stop;

void render();
void update();
void initialize();

int main()
{
  initialize();
  render();

  start = clock();
  while (running)
  {
    stop = clock();
    if (stop - start >= 50) {
      start = clock();
      update();
      render();
    }
  }
}

void initialize()
{
  srand(time(NULL));

  for (int i=0; i<arrSize; i++)
  {
    array[i] = rand()%maxValue+1;
  }
}

void update()
{
  for (int i=arrIndex+1; i<arrSize; i++)
  {
    if (array[i]<array[arrIndex])
    {
      int t=array[i];
      array[i]=array[arrIndex];
      array[arrIndex]=t;
    }
  }
  arrIndex++;
  if (arrIndex>=arrSize)
  {
    running=0;
  }
}

void render()
{
  char*str = (char*)malloc(maxValue*(arrSize+1));
  int t=0;
  for (int y=0; y<maxValue; y++)
  {
    for (int x=0; x<arrSize; x++)
    {
      if (array[x]>=maxValue-y)
      {
        str[t]='#';
      }
      else
      {
        str[t]=' ';
      }
      t++;
    }
    str[t]='\n';
    t++;
  }
  str[t]='\0';
  system("cls");
  printf("%s", str);
  free(str);
}