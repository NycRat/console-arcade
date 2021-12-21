#include "stuff.h"
#include "sortingVisualizer.h"
#include "pong.h"
#include "menu.h"
#include "flappyBird.h"

int main()
{
  for (int i=0; i<=255; i++)
  {
    printf("%c", i);
  }
  getch();
  return MENU_run();
}