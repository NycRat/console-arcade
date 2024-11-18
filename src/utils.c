#include "utils.h"

#include <ncurses.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

char **buffer;
double dt_seconds = 0;
short running = 0;
struct timeval begin, end;
double tempTime = 0;
int frames = 0;
int option = 0;
short keyPressed = 0;

void cls()
{
  clear();
}

void set_text_color(int color)
{
  attron(COLOR_PAIR(color));
}

void dispose_buffer()
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
