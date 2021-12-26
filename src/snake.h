#include "stuff.h"
#define SNAKE_DELAY 500

void SNAKE_initialize();
void SNAKE_update();
void SNAKE_render();
void SNAKE_processInput();

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
};

void add(struct SNAKE_snake *snake)
{
  snake->parts = calloc(snake->size * 2, sizeof(struct SNAKE_snake));
}

enum directions SNAKE_moveBuffer[3];
int SNAKE_moveAddIndex;
struct Vector2 SNAKE_applePos;
struct SNAKE_snake SNAKE_snake;
short SNAKE_keysPressed[4];

int SNAKE_run()
{
  SNAKE_initialize();
  SNAKE_render();
  gettimeofday(&begin, NULL);
  while (running)
  {
    Sleep(1);
    setCursorPosition(0, 1);
    gettimeofday(&end, NULL);
    double temp = (end.tv_sec - begin.tv_sec) * 1000000 - (end.tv_usec - begin.tv_usec);
    temp /= 1000;
    SNAKE_processInput();
    if (temp > SNAKE_DELAY)
    {
      gettimeofday(&begin, NULL);
      SNAKE_update();
      SNAKE_render();
    }
  }
}

void SNAKE_initialize()
{
  SNAKE_moveAddIndex = 0;
  for (int i = 0; i < 3; i++)
    SNAKE_moveBuffer[i] = None;

  SNAKE_snake.size = 4;
  free(SNAKE_snake.parts);
  SNAKE_snake.parts = calloc(SNAKE_snake.size, sizeof(struct SNAKE_snake));
  for (int i = 0; i < SNAKE_snake.size; i++)
  {
    SNAKE_snake.parts[i].pos.x = 3 + (3 - i);
    SNAKE_snake.parts[i].pos.y = HEIGHT / 2;
    SNAKE_snake.parts[i].direction = Right;
  }

  srand(time(NULL));
  SNAKE_applePos.x = rand() % (WIDTH / 2);
  SNAKE_applePos.y = rand() % HEIGHT;

  disposeBuffer();
  cls();
}

void SNAKE_addMove(enum directions direction)
{
  if (SNAKE_moveAddIndex < 3)
  {
    SNAKE_moveBuffer[SNAKE_moveAddIndex] = direction;
    SNAKE_moveAddIndex++;
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
  for (int i = SNAKE_snake.size - 1; i > 0; i--)
  {
    SNAKE_move(&SNAKE_snake.parts[i], SNAKE_snake.parts[i].direction);
    SNAKE_snake.parts[i].direction = SNAKE_snake.parts[i].direction;
  }
  SNAKE_move(&SNAKE_snake.parts[0], SNAKE_snake.parts[0].direction);

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

  if (0) // eats apple
  {
    SNAKE_applePos.x = rand() % (WIDTH / 2);
    SNAKE_applePos.y = rand() % HEIGHT;
    add(&SNAKE_snake);
  }
}

void SNAKE_processInput()
{
  if (GetAsyncKeyState(VK_ESCAPE))
  {
    running = 0;
    return;
  }
  if (GetAsyncKeyState(0x26)) // up
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
  if (GetAsyncKeyState(0x28)) // down
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
  if (GetAsyncKeyState(0x25)) // left
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
  if (GetAsyncKeyState(0x27)) // right
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
  short hasSnake = 0;
  for (int y = 0; y < HEIGHT; y++)
  {
    for (int x = 0; x < WIDTH / 2; x++)
    {
      hasSnake = 0;
      for (int i = 0; i < SNAKE_snake.size; i++)
      {
        if (x == SNAKE_snake.parts[i].pos.x && y == SNAKE_snake.parts[i].pos.y)
        {
          if (buffer[SNAKE_snake.parts[i].pos.y][SNAKE_snake.parts[i].pos.x] != '#')
          {
            buffer[y][x] = '#';
            setCursorPosition(x * 2, y);
            // printf("%c%c", BLOCK, BLOCK);
            printf("%d%d", i, i);
          }
          hasSnake = 1;
          break;
        }
      }
      if (!hasSnake)
      {
        if (buffer[y][x] == 'L')
        {
          buffer[y][x] = ' ';
          setCursorPosition(x * 2, y);
          printf("  ");
        }
        if (buffer[y][x] == '#')
        {
          buffer[y][x] = 'L';
          setCursorPosition(x * 2, y);
          printf("  ");
        }
      }
    }
    setCursorPosition(0, 0);
  }

  setConsoleColour(RED);
  setCursorPosition(SNAKE_applePos.x, SNAKE_applePos.y);
  printf("%c%c", BLOCK, BLOCK);

  setConsoleColour(WHITE);
  setCursorPosition(0, 0);
  // printf("%d %d %d %d", SNAKE_snake.parts[0].direction, SNAKE_snake.parts[1].direction, SNAKE_snake.parts[2].direction, SNAKE_snake.parts[3].direction);
  printf("%d %d %d", SNAKE_moveBuffer[0], SNAKE_moveBuffer[1], SNAKE_moveBuffer[2]);
  setCursorPosition(0, 0);
}