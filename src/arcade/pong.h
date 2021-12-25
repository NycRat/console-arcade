#include "../stuff.h"
#define PONG_BALL_SPEED 0.08
#define PONG_BALL_SIZE 1
#define PONG_PADDLE_SPEED 0.04
#define PONG_PADDLE_SIZE 3

double PONG_ballAngle;
struct Vector2 PONG_ballPos;
struct Vector2 PONG_ballVel;
int PONG_p1Score;
int PONG_p2Score;
double PONG_p1Y;
double PONG_p2Y;
int PONG_numRandSide[2];

void PONG_render();
void PONG_update();
void PONG_initialize();
void PONG_processInput();

void PONG_collision(int side);
double distance(double x1, double y1, double x2, double y2);

int PONG_run()
{
  PONG_initialize();
  while (running)
  {
    gettimeofday(&begin, NULL);
    PONG_processInput();
    PONG_update();
    PONG_render();
    dt = 0;
    Sleep(1);
    while (dt < 1)
    {
      gettimeofday(&end, NULL);
      dt = ((end.tv_sec - begin.tv_sec) * 1000000 + (end.tv_usec - begin.tv_usec));
      dt /= 1000;
    }

    tempTime += dt;

    if (tempTime >= 1000)
    {
      tempTime -= 1000;
      setCursorPosition(0, 0);
      printf("FPS: %d", frames);
      frames = 0;
    }
    setCursorPosition(0, 0);
    frames++;
  }
  return 0;
}

void PONG_processInput()
{
  if (GetAsyncKeyState(VK_ESCAPE))
  {
    running = 0;
  }
  if (GetAsyncKeyState(0x57)) // W
  {
    PONG_p1Y -= PONG_PADDLE_SPEED * dt;
    PONG_p1Y = ((PONG_p1Y > 2) ? PONG_p1Y : 1.5);
  }
  if (GetAsyncKeyState(0x53)) // S
  {
    PONG_p1Y += PONG_PADDLE_SPEED * dt;
    PONG_p1Y = ((PONG_p1Y + PONG_PADDLE_SIZE < HEIGHT) ? PONG_p1Y : HEIGHT - PONG_PADDLE_SIZE);
  }
  if (GetAsyncKeyState(0x26)) // UP
  {
    PONG_p2Y -= PONG_PADDLE_SPEED * dt;
    PONG_p2Y = ((PONG_p2Y > 2) ? PONG_p2Y : 1.5);
  }
  if (GetAsyncKeyState(0x28)) // DOWN
  {
    PONG_p2Y += PONG_PADDLE_SPEED * dt;
    PONG_p2Y = ((PONG_p2Y + PONG_PADDLE_SIZE < HEIGHT) ? PONG_p2Y : HEIGHT - PONG_PADDLE_SIZE);
  }
}

void PONG_collision(int side)
{
  if (side == 1 || side == 3)
  {
    PONG_ballAngle -= PONG_ballAngle * 2;
    PONG_ballVel.x = cos(PONG_ballAngle);
    PONG_ballVel.y = sin(PONG_ballAngle);
  }
  else
  {
    PONG_ballAngle = side / 2 * M_PI + ((double)(rand() % 51) / 100) - 0.25;
    PONG_ballVel.x = cos(PONG_ballAngle);
    PONG_ballVel.y = sin(PONG_ballAngle);
  }
}

void PONG_initialize()
{
  running = 1;
  disposeBuffer();
  cls();
  srand(time(NULL));

  PONG_p1Score = 0;
  PONG_p2Score = 0;
  PONG_ballAngle = 0;

  PONG_ballPos.x = WIDTH / 2 - 30;
  PONG_ballPos.y = HEIGHT / 2;

  PONG_ballVel.x = 1;
  PONG_ballVel.y = 0;

  PONG_p1Y = HEIGHT / 2;
  PONG_p2Y = HEIGHT / 2;
  PONG_numRandSide[0] = 0;
  PONG_numRandSide[1] = 0;

  setConsoleColour(CYAN);
  setCursorPosition(WIDTH / 4, 1);
  printf("%d", PONG_p1Score);
  setConsoleColour(GREEN);
  setCursorPosition(WIDTH - WIDTH / 4, 1);
  printf("%d", PONG_p2Score);
  setConsoleColour(WHITE);
}

void PONG_update()
{
  if (PONG_ballPos.x + PONG_BALL_SPEED * PONG_ballVel.x * dt >= WIDTH - 3 &&
      PONG_ballPos.y >= PONG_p2Y - 0.5 && PONG_ballPos.y <= PONG_p2Y + PONG_PADDLE_SIZE + 0.5)
  {
    PONG_collision(2);
  }
  else
  {
    if (PONG_ballPos.x + PONG_BALL_SPEED * PONG_ballVel.x * dt >= WIDTH)
    {
      int side = rand() % 2;
      if (PONG_numRandSide[side] >= 2)
      {
        PONG_numRandSide[side] = 0;
        side = !side;
      }
      PONG_numRandSide[!side] = 0;
      PONG_numRandSide[side]++;

      PONG_ballPos.x = WIDTH / 2 + ((side) ? 30 : -30);
      PONG_ballPos.y = HEIGHT / 2;
      PONG_ballAngle = side * M_PI;
      PONG_ballVel.x = cos(PONG_ballAngle);
      PONG_ballVel.y = sin(PONG_ballAngle);
      PONG_p1Score++;
      setConsoleColour(CYAN);
      setCursorPosition(WIDTH / 4, 1);
      printf("%d", PONG_p1Score);
      setConsoleColour(WHITE);
    }
  }
  if (PONG_ballPos.x + PONG_BALL_SPEED * PONG_ballVel.x * dt <= 2 &&
      PONG_ballPos.y >= PONG_p1Y - 0.5 && PONG_ballPos.y <= PONG_p1Y + PONG_PADDLE_SIZE + 0.5)
  {
    PONG_collision(0);
  }
  else
  {
    if (PONG_ballPos.x + PONG_BALL_SPEED * PONG_ballVel.x * dt <= 0)
    {
      int side = rand() % 2;
      if (PONG_numRandSide[side] >= 2)
      {
        PONG_numRandSide[side] = 0;
        side = !side;
      }

      PONG_numRandSide[!side] = 0;
      PONG_numRandSide[side]++;

      PONG_ballPos.x = WIDTH / 2 + ((side) ? 30 : -30);
      PONG_ballPos.y = HEIGHT / 2;
      PONG_ballAngle = side * M_PI;
      PONG_ballVel.x = cos(PONG_ballAngle);
      PONG_ballVel.y = sin(PONG_ballAngle);
      PONG_p2Score++;
      setConsoleColour(GREEN);
      setCursorPosition(WIDTH - WIDTH / 4, 1);
      printf("%d", PONG_p2Score);
      setConsoleColour(WHITE);
    }
  }
  if (PONG_ballPos.y + PONG_BALL_SPEED * PONG_ballVel.y * dt >= HEIGHT)
  {
    PONG_collision(1);
  }
  if (PONG_ballPos.y + PONG_BALL_SPEED * PONG_ballVel.y * dt <= 2)
  {
    PONG_collision(3);
  }
  PONG_ballPos.x += PONG_BALL_SPEED * PONG_ballVel.x * dt;
  PONG_ballPos.y += PONG_BALL_SPEED * PONG_ballVel.y * dt;
}

void PONG_render()
{
  for (int y = 2; y < HEIGHT; y++)
  {
    for (int x = 0; x < WIDTH; x++)
    {
      if (distance(x, y, PONG_ballPos.x, PONG_ballPos.y) <= PONG_BALL_SIZE)
      {
        if (buffer[y][x] != '#')
        {
          setCursorPosition(x, y);
          printf("%c", BLOCK);
        }
        buffer[y][x] = '#';
      }
      else if (y >= PONG_p1Y && y < PONG_p1Y + PONG_PADDLE_SIZE && x == 2)
      {
        if (buffer[y][x] != '1')
        {
          setConsoleColour(CYAN);
          setCursorPosition(x, y);
          printf("%c", BLOCK);
          setConsoleColour(WHITE);
        }
        buffer[y][x] = '1';
      }
      else if (y >= PONG_p2Y && y < PONG_p2Y + PONG_PADDLE_SIZE && x == WIDTH - 3)
      {
        if (buffer[y][x] != '2')
        {
          setConsoleColour(GREEN);
          setCursorPosition(x, y);
          printf("%c", BLOCK);
          setConsoleColour(WHITE);
        }
        buffer[y][x] = '2';
      }
      else
      {
        if (buffer[y][x] == 'L')
        {
          setCursorPosition(x, y);
          printf(" ");
          buffer[y][x] = ' ';
        }
        if (buffer[y][x] == '#' || buffer[y][x] == '1' || buffer[y][x] == '2')
        {
          setCursorPosition(x, y);
          printf(" ");
          buffer[y][x] = 'L';
        }
      }
    }
  }
  setCursorPosition(0, 0);
}

double distance(double x1, double y1, double x2, double y2)
{
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}