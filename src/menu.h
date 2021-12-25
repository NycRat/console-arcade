#include "stuff.h"

int ARCADE_run();
int CASINO_run();
int SV_run();

int MENU_run()
{
  MENU_initialize("ARCADE", "CASINO", "SORTING VISUALIZER");
  while (running)
  {
    if (MENU_processInput(ARCADE_run, CASINO_run, SV_run))
    {
      MENU_initialize("ARCADE", "CASINO", "SORTING VISUALIZER");
    }
    MENU_render();
  }
}

int MENU_processInput(int (*f1)(), int (*f2)(), int (*f3)())
{
  Sleep(1);
  if (getKeyActuallyPressed(VK_SPACE)) // SPACE
  {
    if (!keyPressed)
    {
      keyPressed = 1;
      if (MENU_executeOption(f1, f2, f3) == 1)
      {
        running = 0;
        return 0;
      }
      return 1;
    }
    return 0;
  }
  else if (getKeyActuallyPressed(0x26)) // UP
  {
    if (!keyPressed)
    {
      if (option > 0)
      {
        option--;
      }
      keyPressed = 1;
    }
  }
  else if (getKeyActuallyPressed(0x28)) // DOWN
  {
    if (!keyPressed)
    {
      if (option < 3) // idk, 3 for now
      {
        option++;
      }
      keyPressed = 1;
    }
  }
  else
  {
    keyPressed = 0;
  }
  return 0;
}

int MENU_executeOption(int (*f1)(), int (*f2)(), int (*f3)())
{
  if (option == 0)
  {
    return f1();
  }
  else if (option == 1)
  {
    return f2();
  }
  else if (option == 2)
  {
    return f3();
  }
  else if (option == 3)
  {
    return 1;
  }
  return -1;
}

void MENU_initialize(char *o1, char *o2, char *o3)
{
  option = 0;
  running = 1;
  disposeBuffer();
  cls();
  setConsoleColour(WHITE);
  setCursorPosition(WIDTH / 3 + 5, 15);
  printf("%s", o1);
  setCursorPosition(WIDTH / 3 + 5, 19);
  printf("%s", o2);
  setCursorPosition(WIDTH / 3 - 1, 23);
  printf("%s", o3);
  setCursorPosition(WIDTH / 3 - 2, 27);
  printf("EXIT");
}

void MENU_render()
{
  for (int b = 0; b < 4; b++)
  {
    char tempColour = 'W';
    if (b == option)
    {
      tempColour = 'G';
      setConsoleColour(GREEN);
    }

    if (buffer[15 + b * 4][WIDTH / 4] != tempColour)
    {
      setCursorPosition(WIDTH / 4, 15 + b * 4);
      printf("%c", BLOCK);
    }
    buffer[15 + b * 4][WIDTH / 4] = tempColour;

    if (buffer[15 + b * 4][WIDTH - WIDTH / 4 - 1] != tempColour)
    {
      setCursorPosition(WIDTH - WIDTH / 4 - 1, 15 + b * 4);
      printf("%c", BLOCK);
    }
    buffer[15 + b * 4][WIDTH - WIDTH / 4 - 1] = tempColour;

    for (int y = 14 + b * 4; y < b * 4 + 17; y += 2)
    {
      for (int x = WIDTH / 4; x < WIDTH - WIDTH / 4; x++)
      {
        if (buffer[y][x] != tempColour)
        {
          setCursorPosition(x, y);
          printf("%c", BLOCK);
        }
        buffer[y][x] = tempColour;
      }
    }
    setConsoleColour(WHITE);
  }
  setCursorPosition(0, 0);
}
