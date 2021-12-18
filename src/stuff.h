#ifndef ALL_THE_STUFF
#define ALL_THE_STUFF

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define WIDTH 110
#define HEIGHT 30

char* display;
double dt=0;

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