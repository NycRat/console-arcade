#include "stuff.h"
#define PONG_BALL_SPEED 0.08
#define PONG_BALL_SIZE 1
#define PONG_PADDLE_SPEED 0.04
#define PONG_PADDLE_SIZE 3

double PONG_ballX;
double PONG_ballY;
double PONG_ballAngle;
int PONG_p1Score;
int PONG_p2Score;
double PONG_p1Y;
double PONG_p2Y;

void PONG_render();
void PONG_update();
void PONG_initialize();

void PONG_collision(int side);
double distance(double x1, double y1, double x2, double y2);

int PONG_run()
{
  PONG_initialize();
  while (running)
  {
    gettimeofday(&begin, NULL);
    PONG_update();
    PONG_render();
    if (GetAsyncKeyState(VK_ESCAPE))
    {
      return 0;
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
    dt=0;
    while (dt<=0)
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

void PONG_collision(int side)
{
  if (side == 1 || side == 3)
  {
    PONG_ballAngle -= PONG_ballAngle * 2;
  }
  else
  {
    PONG_ballAngle = side / 2 * M_PI + ((double)(rand() % 51) / 100) - 0.25;
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
  PONG_ballX = WIDTH/2-30;
  PONG_ballY = HEIGHT/2;
  PONG_ballAngle = 0;
  PONG_p1Y = HEIGHT / 2;
  PONG_p2Y = HEIGHT / 2;

  setConsoleColour(CYAN);
  setCursorPosition(WIDTH / 4, 1);
  printf("%d", PONG_p1Score);
  setConsoleColour(BLUE);
  setCursorPosition(WIDTH - WIDTH / 4, 1);
  printf("%d", PONG_p2Score);
  setConsoleColour(WHITE);
}

void PONG_update()
{
  if (PONG_ballX + PONG_BALL_SPEED * cos(PONG_ballAngle) * dt >= WIDTH - 3 &&
    PONG_ballY >= PONG_p2Y - 0.5 && PONG_ballY <= PONG_p2Y + PONG_PADDLE_SIZE + 0.5)
  {
    PONG_collision(2);
  }
  else
  {
    if (PONG_ballX + PONG_BALL_SPEED * cos(PONG_ballAngle) * dt >= WIDTH)
    {
      int side = rand()%2; // 0 1
      PONG_ballX = WIDTH / 2 + ((side) ? 30 : -30);
      PONG_ballY = HEIGHT / 2;
      PONG_ballAngle = side*M_PI;
      PONG_p1Score++;
      setConsoleColour(CYAN);
      setCursorPosition(WIDTH / 4, 1);
      printf("%d", PONG_p1Score);
      setConsoleColour(WHITE);
    }
  }
  if (PONG_ballX + PONG_BALL_SPEED * cos(PONG_ballAngle) * dt <= 2 && 
    PONG_ballY >= PONG_p1Y - 0.5 && PONG_ballY <= PONG_p1Y + PONG_PADDLE_SIZE + 0.5)
  {
    PONG_collision(0);
  }
  else
  {
    if (PONG_ballX + PONG_BALL_SPEED * cos(PONG_ballAngle) * dt <= 0)
    {
      int side=rand()%2;
      PONG_ballX = WIDTH / 2 + ((side) ? 30 : -30);
      PONG_ballY = HEIGHT / 2;
      PONG_ballAngle = side*M_PI;
      PONG_p2Score++;
      setConsoleColour(BLUE);
      setCursorPosition(WIDTH - WIDTH / 4, 1);
      printf("%d", PONG_p2Score);
      setConsoleColour(WHITE);
    }
  }
  if (PONG_ballY + PONG_BALL_SPEED * sin(PONG_ballAngle) * dt >= HEIGHT)
  {
    PONG_collision(1);
  }
  if (PONG_ballY + PONG_BALL_SPEED * sin(PONG_ballAngle) * dt <= 2)
  {
    PONG_collision(3);
  }
  PONG_ballX += PONG_BALL_SPEED * cos(PONG_ballAngle) * dt;
  PONG_ballY += PONG_BALL_SPEED * sin(PONG_ballAngle) * dt;
}

void PONG_render()
{
  for (int y = 2; y < HEIGHT; y++)
  {
    for (int x = 0; x < WIDTH; x++)
    {
      if (distance(x, y, PONG_ballX, PONG_ballY) <= PONG_BALL_SIZE)
      {
        if (buffer[y][x] != '#')
        {
          setCursorPosition(x, y);
          printf("%c", BLOCK);
        }
        buffer[y][x] = '#';
      }
      else if (y >= PONG_p1Y && y <= PONG_p1Y + PONG_PADDLE_SIZE && x == 2)
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
      else if (y >= PONG_p2Y && y <= PONG_p2Y + PONG_PADDLE_SIZE && x == WIDTH - 3)
      {
        if (buffer[y][x] != '2')
        {
          setConsoleColour(BLUE);
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