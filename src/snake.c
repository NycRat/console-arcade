#include "snake.h"
#include "utils.h"
#include <ncurses.h>
#include <stdlib.h>
#include <sys/time.h>

enum directions SNAKE_moveBuffer[3];
int SNAKE_moveAddIndex = 0;
struct Vector2 SNAKE_applePos;
struct SNAKE_snake SNAKE_snake;
short SNAKE_keysPressed[4];

void add(struct SNAKE_snake *snake)
{
  if (snake->size + 1 > snake->maxSize)
  {
    struct SNAKE_part *newParts = calloc(snake->maxSize * 2, sizeof(struct SNAKE_part));
    for (int i = 0; i < snake->size; i++)
    {
      newParts[i] = snake->parts[i];
    }
    free(snake->parts);
    snake->parts = newParts;
    snake->maxSize *= 2;
  }
  enum directions tempDirection = snake->parts[snake->size - 1].direction;
  snake->parts[snake->size].direction = tempDirection;
  snake->parts[snake->size].pos.x =
      snake->parts[snake->size - 1].pos.x - (tempDirection == Right) + (tempDirection == Left);
  snake->parts[snake->size].pos.y =
      snake->parts[snake->size - 1].pos.y - (tempDirection == Down) + (tempDirection == Up);
  snake->size++;
}

int SNAKE_run()
{
  SNAKE_initialize();
  SNAKE_render();
  gettimeofday(&begin, NULL);
  double tempTime = 0;
  while (running)
  {
    avah_sleep(1);
    gettimeofday(&end, NULL);
    tempTime = (end.tv_sec - begin.tv_sec) * 1000000 + (end.tv_usec - begin.tv_usec);
    tempTime /= 1000;
    SNAKE_processInput();
    if (tempTime > SNAKE_DELAY)
    {
      gettimeofday(&begin, NULL);
      SNAKE_update();
      SNAKE_render();
    }
  }
  mvprintw(1, 0, "Press [R] to play again");
  mvprintw(2, 0, "Press [Q] to quit");
  refresh();
  while (1)
  {
    int c = getch();
    if (c == 'r')
    {
      break;
    }
    if (c == 'q')
    {
      return 0;
    }
    avah_sleep(1);
  }
  return SNAKE_run();
}

void SNAKE_initialize()
{
  running = 1;
  SNAKE_moveAddIndex = 0;
  for (int i = 0; i < 3; i++)
    SNAKE_moveBuffer[i] = None;

  SNAKE_snake.size = 4;
  SNAKE_snake.maxSize = 8;
  free(SNAKE_snake.parts);
  SNAKE_snake.parts = calloc(SNAKE_snake.maxSize, sizeof(struct SNAKE_part));
  for (int i = 0; i < SNAKE_snake.size; i++)
  {
    SNAKE_snake.parts[i].pos.x = 3 + (3 - i);
    SNAKE_snake.parts[i].pos.y = HEIGHT / 4;
    SNAKE_snake.parts[i].direction = Right;
  }

  srand(time(NULL));
  SNAKE_applePos.x = (rand() % (WIDTH - 4)) / 4;
  SNAKE_applePos.y = (rand() % (HEIGHT - 4)) / 2;

  dispose_buffer();
  cls();
}

void SNAKE_addMove(enum directions direction)
{
  if (SNAKE_moveAddIndex < 3)
  {
    enum directions previousDirection;
    if (SNAKE_moveAddIndex != 0)
    {
      previousDirection = SNAKE_moveBuffer[SNAKE_moveAddIndex - 1];
    }
    else
    {
      previousDirection = SNAKE_snake.parts[0].direction;
    }
    if ((previousDirection <= 2 && direction > 2) || (previousDirection > 2 && direction <= 2))
    {
      SNAKE_moveBuffer[SNAKE_moveAddIndex] = direction;
      SNAKE_moveAddIndex++;
    }
  }
}

void SNAKE_move(struct SNAKE_part *part, enum directions direction)
{
  if (direction == Up || direction == Down)
  {
    part->pos.y += ((direction - 1) * 2 - 1);
  }
  else if (direction == Left || direction == Right)
  {
    // * 2
    part->pos.x += ((direction - 3) * 2 - 1);
  }
}

void SNAKE_update()
{
  // move

  if (SNAKE_moveBuffer[0] != None)
  {
    SNAKE_snake.parts[0].direction = SNAKE_moveBuffer[0];

    for (int i = 0; i < 2; i++)
    {
      SNAKE_moveBuffer[i] = SNAKE_moveBuffer[i + 1];
    }
    SNAKE_moveBuffer[2] = None;
    SNAKE_moveAddIndex--;
  }
  for (int i = SNAKE_snake.size - 1; i > 0; i--)
  {
    SNAKE_move(&SNAKE_snake.parts[i], SNAKE_snake.parts[i].direction);
    SNAKE_snake.parts[i].direction = SNAKE_snake.parts[i - 1].direction;
  }
  SNAKE_move(&SNAKE_snake.parts[0], SNAKE_snake.parts[0].direction);

  struct Vector2 snakeHeadPos;
  snakeHeadPos.x = SNAKE_snake.parts[0].pos.x;
  snakeHeadPos.y = SNAKE_snake.parts[0].pos.y;

  if (snakeHeadPos.x > WIDTH / 4 - 1 || snakeHeadPos.x < 0 || snakeHeadPos.y > HEIGHT / 2 - 1 || snakeHeadPos.y < 0)
  {
    running = 0;
    return;
  }

  if (buffer[snakeHeadPos.y][snakeHeadPos.x] == '#') //&&
                                                     // SNAKE_snake.parts[SNAKE_snake.size-1].pos.x != snakeHeadPos.x &&
                                                     // SNAKE_snake.parts[SNAKE_snake.size-1].pos.y != snakeHeadPos.y)
  {
    running = 0;
    return;
  }

  if (snakeHeadPos.x == SNAKE_applePos.x && snakeHeadPos.y == SNAKE_applePos.y) // eats apple
  {
    mvprintw(SNAKE_applePos.y, SNAKE_applePos.x, "    ");
    mvprintw(SNAKE_applePos.y + 1, SNAKE_applePos.x, "    ");
    struct Vector2 tempApplePos;
    if (SNAKE_snake.size < ((WIDTH - 4) / 4) + ((HEIGHT - 4) / 2))
    {
      while (1)
      {
        tempApplePos.x = (rand() % (WIDTH - 4)) / 4;
        tempApplePos.y = (rand() % (HEIGHT - 4)) / 2;
        if (buffer[tempApplePos.y][tempApplePos.x] != '#' && tempApplePos.x != snakeHeadPos.x &&
            tempApplePos.y != snakeHeadPos.y)
        {
          SNAKE_applePos.x = tempApplePos.x;
          SNAKE_applePos.y = tempApplePos.y;
          break;
        }
      }
    }
    add(&SNAKE_snake);
  }
}

void SNAKE_processInput()
{
  int c = getch();
  if (c == 'q')
  {
    running = 0;
    return;
  }
  if (c == KEY_UP) // up
  {
    if (!SNAKE_keysPressed[0])
    {
      SNAKE_addMove(Up);
      SNAKE_keysPressed[0] = 1;
    }
  }
  else
  {
    SNAKE_keysPressed[0] = 0;
  }
  if (c == KEY_DOWN) // down
  {
    if (!SNAKE_keysPressed[1])
    {
      SNAKE_addMove(Down);
      SNAKE_keysPressed[1] = 1;
    }
  }
  else
  {
    SNAKE_keysPressed[1] = 0;
  }
  if (c == KEY_LEFT) // left
  {
    if (!SNAKE_keysPressed[2])
    {
      SNAKE_addMove(Left);
      SNAKE_keysPressed[2] = 1;
    }
  }
  else
  {
    SNAKE_keysPressed[2] = 0;
  }
  if (c == KEY_RIGHT) // right
  {
    if (!SNAKE_keysPressed[3])
    {
      SNAKE_addMove(Right);
      SNAKE_keysPressed[3] = 1;
    }
  }
  else
  {
    SNAKE_keysPressed[3] = 0;
  }
}

void SNAKE_render()
{
  cls();
  for (int y = 0; y < HEIGHT / 2; y++)
  {
    for (int x = 0; x < WIDTH / 4; x++)
    {
      for (int i = 0; i < SNAKE_snake.size; i++)
      {
        if (x == SNAKE_snake.parts[i].pos.x && y == SNAKE_snake.parts[i].pos.y)
        {
          // if (buffer[SNAKE_snake.parts[i].pos.y][SNAKE_snake.parts[i].pos.x]
          // != '#') { buffer[y][x] = '#';
          // }
          mvprintw(y * 2, x * 4, "%c%c%c%c", BLOCK, BLOCK, BLOCK, BLOCK);
          mvprintw(y * 2 + 1, x * 4, "%c%c%c%c", BLOCK, BLOCK, BLOCK, BLOCK);
          break;
        }
      }
    }
  }

  set_text_color(COLOR_RED);
  mvprintw(SNAKE_applePos.y * 2, SNAKE_applePos.x * 4, "%c%c%c%c", BLOCK, BLOCK, BLOCK, BLOCK);
  mvprintw(SNAKE_applePos.y * 2 + 1, SNAKE_applePos.x * 4, "%c%c%c%c", BLOCK, BLOCK, BLOCK, BLOCK);

  set_text_color(COLOR_WHITE);
  mvprintw(0, 0, "SNAKE LENGTH: %d", SNAKE_snake.size);

  refresh();
}
