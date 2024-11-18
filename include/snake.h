#pragma once

#include "utils.h"

#define SNAKE_DELAY 100

enum directions
{
  None,
  Up,
  Down,
  Left,
  Right
};

struct SNAKE_part
{
  struct Vector2 pos;
  enum directions direction;
};

struct SNAKE_snake
{
  struct SNAKE_part *parts;
  int size;
  int maxSize;
};

void add(struct SNAKE_snake *snake);
void SNAKE_initialize();
void SNAKE_update();
void SNAKE_render();
void SNAKE_processInput();

int SNAKE_run();

void SNAKE_addMove(enum directions direction);

void SNAKE_move(struct SNAKE_part *part, enum directions direction);

extern enum directions SNAKE_moveBuffer[3];
extern int SNAKE_moveAddIndex;
extern struct Vector2 SNAKE_applePos;
extern struct SNAKE_snake SNAKE_snake;
extern short SNAKE_keysPressed[4];
