#include "arcadeMenu.h"
#include <ncurses.h>

int main()
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);  // Enable special keys (arrows, F1, etc.)
  nodelay(stdscr, TRUE); // Non-blocking input mode

  // INIT COLOR
  start_color();
  int colors[] = {COLOR_BLACK, COLOR_RED,     COLOR_GREEN, COLOR_YELLOW,
                  COLOR_BLUE,  COLOR_MAGENTA, COLOR_CYAN,  COLOR_WHITE};

  for (int i = 0; i < 8; i++)
  {
    init_pair(colors[i], colors[i], COLOR_BLACK);
  }

  attron(COLOR_PAIR(COLOR_WHITE));

  ARCADE_run();

  endwin();
  return 0;
}
