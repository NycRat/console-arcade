#include "../stuff.h"

int BJ_deck[52];
int BJ_money;

void BJ_initialize();

int BJ_run()
{
  while (running)
  {
    setCursorPosition(0, 0);
    printf("$%d", BJ_money);
  }
}

void BJ_initialize()
{
  running = 1;
  disposeBuffer();
  BJ_money = 200;
}