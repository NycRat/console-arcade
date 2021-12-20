#ifndef ALL_THE_STUFF
#define ALL_THE_STUFF

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <sys/time.h>

#define BLOCK 219

#define WIDTH 110
#define HEIGHT 30

#define BLACK			0
#define BLUE			1
#define GREEN			2
#define CYAN			3
#define RED				4
#define MAGENTA			5
#define BROWN			6
#define LIGHTGRAY		7
#define DARKGRAY		8
#define LIGHTBLUE		9
#define LIGHTGREEN		10
#define LIGHTCYAN		11
#define LIGHTRED		12
#define LIGHTMAGENTA	13
#define YELLOW			14
#define WHITE			15

char** buffer;
double dt=0;
short running=0;
struct timeval FRAME_begin, FRAME_end;
double tempTime = 0;
int frames = 0;

void cls()
{
  const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_SCREEN_BUFFER_INFO csbi;
  COORD topLeft = {0, 0};

  if (!GetConsoleScreenBufferInfo(hOut, &csbi))
  {
    abort();
  }

  DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

  DWORD written;

  FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

  // was filling with invalid characters
  // FillConsoleOutputCharacter(hOut, csbi.wAttributes, length, topLeft, &written);

  SetConsoleCursorPosition(hOut, topLeft);

}

void setCursorPosition(int x, int y)
{
  const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD coord = {(SHORT)x, (SHORT)y};
  SetConsoleCursorPosition(hOut, coord);
}

void setConsoleColour(unsigned short colour)
{
  const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hOut, colour);
}

#endif