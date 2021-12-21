#include "stuff.h"

void MENU_render();
void MENU_initialize();

int option=0;
int MENU_executeOption();
short MENU_keyPressed=0;

int PONG_run();
int SV_run();
int FB_run();

int MENU_run()
{
  MENU_initialize();
  while (running)
  {
    if (GetAsyncKeyState(0x20)) // SPACE
    {
      if (MENU_executeOption()==1)
      {
        return 0;
      }
      MENU_initialize();
    }
    if (GetAsyncKeyState(0x26)) // UP
    {
      if (!MENU_keyPressed)
      {
        if (option>0)
        {
          option--;
        }
      }
      MENU_keyPressed=1;
    }
    else if (GetAsyncKeyState(0x28)) // DOWN
    {
      if (!MENU_keyPressed)
      {
        if (option<3) // idk, 3 for now
        {
          option++;
        }
      }
      MENU_keyPressed=1;
    }
    else
    {
      MENU_keyPressed=0;
    }

    MENU_render();

    // testingj
    setCursorPosition(0,0);
    printf("%d", option);
  }
}

int MENU_executeOption()
{
  if (option==0)
  {
    return PONG_run();
  }
  else if (option == 1)
  {
    return SV_run();
  }
  else if (option == 2)
  {
    return FB_run();
  }
  else if (option == 3)
  {
    return 1;
  }
  return -1;
}

void MENU_initialize()
{
  option=0;
  running = 1;
  disposeBuffer();
  cls();
  setConsoleColour(WHITE);
  setCursorPosition(WIDTH/3+1,15);
  printf("PONG GAME");
  setCursorPosition(WIDTH/3,19);
  printf("SORTING VISUALIZER");
  setCursorPosition(WIDTH/3-1,23);
  printf("FLAPPY BIRD");
  setCursorPosition(WIDTH/3-2,27);
  printf("EXIT");
}

void MENU_render()
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
