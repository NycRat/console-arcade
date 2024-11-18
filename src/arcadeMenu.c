#include "arcadeMenu.h"
#include "menu.h"
#include "utils.h"
#include <ncurses.h>

int ARCADE_run()
{
  ARCADE_initialize();
  refresh();
  while (running)
  {
    avah_sleep(1000 / FPS);
    if (MENU_processInput(PONG_run, FB_run, SNAKE_run))
    {
      ARCADE_initialize();
    }
    MENU_render();
    refresh();
  }
  cls();
  refresh();
  return 0;
}

void ARCADE_initialize()
{
  MENU_initialize("PONG", "FLAPPY BIRD", "SNAKE");
  set_text_color(COLOR_CYAN);

  const char arcade_graphic[] =
#include "menuGraphic.txt"
      ;

  mvprintw(2, 0, arcade_graphic);

  set_text_color(COLOR_WHITE);
  mvprintw(HEIGHT - 1, WIDTH - 32, "Press [Q] to exit any game");
}
