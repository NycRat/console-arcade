#include "../stuff.h"

void CASINO_initialize();

int CASINO_money = 200;

int BJ_run();

int CASINO_run()
{
  CASINO_initialize();
  while (running)
  {
    if (MENU_processInput(BJ_run, BJ_run, BJ_run))
    {
      CASINO_initialize();
      running = 1;
    }
    MENU_render();

    setCursorPosition(0, 0);
    printf("L");
  }
  return 0;
}

void CASINO_initialize()
{
  MENU_initialize("BLACKJACK", "Asee", "IDK");
  setCursorPosition(0, 0);
  printf("$%d", CASINO_money);
}
