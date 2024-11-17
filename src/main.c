#include "arcadeMenu.h"
#include "flappyBird.h"
#include "menu.h"
#include "pong.h"
#include "snake.h"

#include <ncurses.h>

int main() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);  // Enable special keys (arrows, F1, etc.)
  nodelay(stdscr, TRUE); // Non-blocking input mode

  // INIT COLOR
  start_color();
  init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
  init_pair(RED, COLOR_RED, COLOR_BLACK);
  init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
  init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
  init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);

  attron(COLOR_PAIR(WHITE));

  ARCADE_run();

  endwin();
  return 0;
}
