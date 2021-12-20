#include "stuff.h"

void MENU_Render();
void MENU_Initialize();

int option=0;
int MENU_ExecuteOption();
short MENU_KeyPressed=0;

int MENU_Run()
{
  MENU_Initialize();
  while (running)
  {
    if (GetAsyncKeyState(0x20)) // SPACE
    {
      if (MENU_ExecuteOption()==1)
      {
        return 0;
      }
      MENU_Initialize();
    }
    if (GetAsyncKeyState(0x26)) // UP
    {
      if (!MENU_KeyPressed)
      {
        if (option>0)
        {
          option--;
        }
      }
      MENU_KeyPressed=1;
    }
    else if (GetAsyncKeyState(0x28)) // DOWN
    {
      if (!MENU_KeyPressed)
      {
        if (option<3) // idk, 3 for now
        {
          option++;
        }
      }
      MENU_KeyPressed=1;
    }
    else
    {
      MENU_KeyPressed=0;
    }

    MENU_Render();

    // testingj
    setCursorPosition(0,0);
    printf("%d", option);
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
    return SV_Run();
  }
  else if (option == 2)
  {
    return 1;
  }
  else if (option == 3)
  {
    return 1;
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
  cls();
  setConsoleColour(WHITE);
  setCursorPosition(WIDTH/3+1,15);
  printf("PONG GAME");
  setCursorPosition(WIDTH/3,19);
  printf("SORTING VISUALIZER");
  setCursorPosition(WIDTH/3-1,23);
  printf("TEMP THING");
  setCursorPosition(WIDTH/3-2,27);
  printf("EXIT");
}

void MENU_Render()
{
  for (int b=0; b<4; b++)
  {
    char tempColour='W';
    if (b == option)
    {
      tempColour='G';
      setConsoleColour(GREEN);
    }

    if (buffer[15+b*4][WIDTH/4] != tempColour)
    {
      setCursorPosition(WIDTH/4,15+b*4);
      printf("%c", BLOCK);
    }
    buffer[15+b*4][WIDTH/4] = tempColour;

    if (buffer[15+b*4][WIDTH-WIDTH/4-1] != tempColour)
    {
      setCursorPosition(WIDTH-WIDTH/4-1,15+b*4);
      printf("%c", BLOCK);
    }
    buffer[15+b*4][WIDTH-WIDTH/4-1] = tempColour;
    
    for (int y=14+b*4; y<b*4+17; y+=2)
    {
      for (int x=WIDTH/4; x<WIDTH-WIDTH/4; x++)
      {
        if (buffer[y][x] != tempColour)
        {
          setCursorPosition(x,y);
          printf("%c", BLOCK);
        }
        buffer[y][x] = tempColour;
      }
    }
    setConsoleColour(WHITE);
  }

  for (int y=0; y<HEIGHT; y++)
  {
    for (int x=0; x<WIDTH; x++)
    {
    }
  }
  setCursorPosition(0,0);
}
