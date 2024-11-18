#pragma once

#define BLOCK '#'

#define WIDTH 110
#define HEIGHT 30
#define FPS 240

extern char **buffer;
extern double dt_seconds;
extern short running;
extern struct timeval begin, end;
extern double tempTime;
extern int frames;
extern int option;
extern short keyPressed;

void cls();
void set_text_color(int color);
void dispose_buffer();
void avah_sleep(int millis);

struct Vector2f
{
  double x, y;
};

struct Vector2
{
  short x, y;
};
