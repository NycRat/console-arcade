#include "stuff.h"

void MENU_render();
void MENU_initialize();
void MENU_processInput();

int MENU_executeOption();

int ARCADE_run();
int CASINO_run();
int SV_run();

int MENU_run()
{
  MENU_initialize();
  while (running)
  {
    MENU_processInput();
    MENU_render();
    // testingj
    setCursorPosition(0, 0);
    printf("%d", option);
  }
}

void MENU_processInput()
{
  if (getKeyActuallyPressed(VK_SPACE)) // SPACE
  {
    if (!keyPressed)
    {
      keyPressed = 1;
      if (MENU_executeOption() == 1)
      {
        running = 0;
        return;
      }
      MENU_initialize();
    }
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
}

int MENU_executeOption()
{
  if (option == 0)
  {
    return ARCADE_run();
  }
  else if (option == 1)
  {
    return CASINO_run();
  }
  else if (option == 2)
  {
    return SV_run();
  }
  else if (option == 3)
  {
    return 1;
  }
  return -1;
}

void MENU_initialize()
{
  option = 0;
  running = 1;
  disposeBuffer();
  cls();
  setConsoleColour(WHITE);
  setCursorPosition(WIDTH / 3 + 5, 15);
  printf("ARCADE");
  setCursorPosition(WIDTH / 3 + 5, 19);
  printf("CASINO");
  setCursorPosition(WIDTH / 3 - 1, 23);
  printf("SORTING VISUALIZER");
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
