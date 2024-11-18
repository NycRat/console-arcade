#include "utils.h"

// int MENU_run()
// {
//   MENU_initialize("ARCADE", "CASINO", "SORTING VISUALIZER");
//   while (running)
//   {
//     if (MENU_processInput(ARCADE_run, CASINO_run, SV_run))
//     {
//       MENU_initialize("ARCADE", "CASINO", "SORTING VISUALIZER");
//     }
//     MENU_render();
//   }
// }

int MENU_processInput(int (*f1)(), int (*f2)(), int (*f3)())
{
  int c = getch();
  if (c == 'q')
  {
    running = 0;
    return 0;
  }
  else if (c == ' ')
  {
    if (!keyPressed)
    {
      keyPressed = 1;

      // NOTE GO INTO THE GAME HERE
      if (MENU_executeOption(f1, f2, f3) == 1)
      {
        running = 0;
        return 0;
      }
      return 1;
    }
    return 0;
  }
  else if (c == KEY_UP) // UP
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
  else if (c == KEY_DOWN) // DOWN
  {
    if (!keyPressed)
    {
      if (option < 3) // idk, 3 for now
      {
        option++;
      }
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
  char *menu_items[] = {o1, o2, o3, "EXIT"};

  option = 0;
  running = 1;
  disposeBuffer();
  cls();
  setConsoleColor(COLOR_WHITE);

  for (int i = 0; i < 4; i++)
  {
    mvprintw(15 + 4 * i, WIDTH / 3 + 5, "%s", menu_items[i]);
  }
}

void MENU_render()
{
  for (int b = 0; b < 4; b++)
  {
    char tempBlockChar = '#';
    char tempColour = 'W';
    if (b == option)
    {
      tempBlockChar = '*';
      tempColour = 'G';
      setConsoleColor(COLOR_GREEN);
    }

    if (buffer[15 + b * 4][WIDTH / 4] != tempColour)
    {
      mvprintw(15 + b * 4, WIDTH / 4, "%c", tempBlockChar);
    }
    buffer[15 + b * 4][WIDTH / 4] = tempColour;

    if (buffer[15 + b * 4][WIDTH - WIDTH / 4 - 1] != tempColour)
    {
      mvprintw(15 + b * 4, WIDTH - WIDTH / 4 - 1, "%c", tempBlockChar);
    }
    buffer[15 + b * 4][WIDTH - WIDTH / 4 - 1] = tempColour;

    for (int y = 14 + b * 4; y < b * 4 + 17; y += 2)
    {
      for (int x = WIDTH / 4; x < WIDTH - WIDTH / 4; x++)
      {
        if (buffer[y][x] != tempColour)
        {
          mvprintw(y, x, "%c", tempBlockChar);
        }
        buffer[y][x] = tempColour;
      }
    }
    setConsoleColor(COLOR_WHITE);
  }
}
