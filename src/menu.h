#include "stuff.h"

void MENU_Render();
void MENU_Initialize();

int option=0;
int MENU_ExecuteOption();

int MENU_Run()
{
  MENU_Initialize();
  while (running)
  {
    if (GetAsyncKeyState(0x20)) // SPACE
    {
      MENU_ExecuteOption();
    }
    if (GetAsyncKeyState(0x26)) // UP
    {
      if (option<3) // idk, 3 for now
      {
        option++;
      }
    }
    if (GetAsyncKeyState(0x28)) // DOWN
    {
      if (option>0)
      {
        option--;
      }
    }
    MENU_Render();
  }
}

int MENU_ExecuteOption()
{
  if (option==0)
  {
    return PONG_Run();
  }
  else if (option == 1)
  {

  }
  else if (option == 2)
  {

  }
  return -1;
}

void MENU_Initialize()
{
  option=0;
  running = 1;
  free(buffer);
  buffer = malloc(sizeof(char*)*HEIGHT);
  for (int i=0; i<HEIGHT; i++)
  {
    buffer[i] = malloc(sizeof(char)*WIDTH);
  }
}

void MENU_Render()
{
  for (int y=0; y<HEIGHT/4; y++)
  {
    for (int x=WIDTH/4; x<WIDTH/2; x++)
    {
      if (buffer[y][x] != '#')
      {
        setCursorPosition(x,y);
        printf("%c", BLOCK);
      }
      buffer[y][x] = '#';
    }
  }

  for (int y=0; y<HEIGHT; y++)
  {
    for (int x=0; x<WIDTH; x++)
    {


    }
  }
}
