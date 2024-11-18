#ifndef CONSOLE_UTIL
#define CONSOLE_UTIL

#include <ncurses.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h> // usleep

// #define BLOCK (unsigned char)219
// #define BLOCK 219
#define BLOCK '#'
// #define BLOCK "\u2588"
// #define BLOCK "\xE2\x96\x88"

#define WIDTH 110
#define HEIGHT 30

char **buffer;
double dt_seconds = 0;
short running = 0;
struct timeval begin, end;
double tempTime = 0;
int frames = 0;
int option = 0;
short keyPressed = 0;

void MENU_render();
void MENU_initialize(char *o1, char *o2, char *o3);
int MENU_processInput(int (*f1)(), int (*f2)(), int (*f3)());
int MENU_executeOption(int (*f1)(), int (*f2)(), int (*f3)());

struct Vector2f
{
  double x, y;
};

struct Vector2
{
  short x, y;
};

int TempGetAsyncKeyState(int vKey)
{
  return 0;
}

int getKeyActuallyPressed(int vKey)
{
  //
  return getch() == vKey;
}

void cls()
{
  clear();
}

void setConsoleColor(int color)
{
  //
  attron(COLOR_PAIR(color));
}

void disposeBuffer()
{
  free(buffer);
  buffer = (char **)malloc(sizeof(char *) * HEIGHT);
  for (int i = 0; i < HEIGHT; i++)
  {
    buffer[i] = (char *)malloc(sizeof(char) * WIDTH);
  }
}

void avah_sleep(int millis)
{
#ifdef _WIN32
  Sleep(millis);
#else
  usleep(millis * 1000);
#endif
}

#endif
