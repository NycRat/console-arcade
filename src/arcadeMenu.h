#include "utils.h"
#include <ncurses.h>

void ARCADE_initialize();

int PONG_run();
int FB_run();
int SNAKE_run();

int ARCADE_run() {
  ARCADE_initialize();
  refresh();
  while (running) {
    avah_sleep(1);
    if (MENU_processInput(PONG_run, FB_run, SNAKE_run)) {
      ARCADE_initialize();
    }
    MENU_render();
    refresh();
  }
  cls();
  refresh();
  return 0;
}

void ARCADE_initialize() {
  MENU_initialize("PONG", "FLAPPY BIRD", "SNAKE");
  setConsoleColor(CYAN);

  const char arcade_graphic[] =
#include "menuGraphic.txt"
      ;

  mvprintw(2, 0, arcade_graphic);

  setConsoleColor(WHITE);
  mvprintw(HEIGHT - 1, WIDTH - 32, "Press [Q] to exit any game");
}
