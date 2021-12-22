#include "stuff.h"

#include "tempcat/sortingVisualizer.h"
#include "arcade/arcadeMenu.h"
#include "arcade/flappyBird.h"
#include "arcade/pong.h"
#include "arcade/snake.h"
#include "casino/casinoMenu.h"
#include "casino/blackjack.h"
#include "casino/slots.h"
#include "menu.h"

int main()
{
  // for (int i = 0; i <= 255; i++)
  // {
  //   printf("%c", i);
  // }
  // getch();
  return MENU_run();
}