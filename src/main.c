#include "arcadeMenu.h"
#include "flappyBird.h"
#include "menu.h"
#include "pong.h"
#include "snake.h"

#include <ncurses.h>

int main() {
  initscr();
  /* start_color(); */ // TODO do the color
  cbreak();
  noecho();
  keypad(stdscr, TRUE);  // Enable special keys (arrows, F1, etc.)
  nodelay(stdscr, TRUE); // Non-blocking input mode

  return ARCADE_run();
}
