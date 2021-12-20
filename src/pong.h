#include "stuff.h"
#define PONG_BALL_SPEED 0.08
#define PONG_BALL_SIZE 1
#define PONG_PADDLE_SPEED 0.04
#define PONG_PADDLE_SIZE 3

double ballX = 30;
double ballY = 10;
double ballAngle = 0;
int PONG_P1_Score = 0;
int PONG_P2_Score = 0;
double PONG_P1_Y = HEIGHT / 2;
double PONG_P2_Y = HEIGHT / 2;

void PONG_Render();
void PONG_Update();
void PONG_Initialize();

void PONG_Collision(int side);
double distance(double x1, double y1, double x2, double y2);

int PONG_Run()
{
  PONG_Initialize();
  while (running)
  {
    gettimeofday(&FRAME_begin, NULL);
    PONG_Render();
    PONG_Update();
    if (GetAsyncKeyState(VK_ESCAPE))
    {
      return 0;
    }
    if (GetAsyncKeyState(0x57)) // W
    {
      PONG_P1_Y -= PONG_PADDLE_SPEED * dt;
      PONG_P1_Y = ((PONG_P1_Y > 2) ? PONG_P1_Y : 1.5);
    }
    if (GetAsyncKeyState(0x53)) // S
    {
      PONG_P1_Y += PONG_PADDLE_SPEED * dt;
      PONG_P1_Y = ((PONG_P1_Y + PONG_PADDLE_SIZE < HEIGHT) ? PONG_P1_Y : HEIGHT - PONG_PADDLE_SIZE);
    }
    if (GetAsyncKeyState(0x26)) // UP
    {
      PONG_P2_Y -= PONG_PADDLE_SPEED * dt;
      PONG_P2_Y = ((PONG_P2_Y > 2) ? PONG_P2_Y : 1.5);
    }
    if (GetAsyncKeyState(0x28)) // DOWN
    {
      PONG_P2_Y += PONG_PADDLE_SPEED * dt;
      PONG_P2_Y = ((PONG_P2_Y + PONG_PADDLE_SIZE < HEIGHT) ? PONG_P2_Y : HEIGHT - PONG_PADDLE_SIZE);
    }
    dt=0;
    while (dt<=0)
    {
      gettimeofday(&FRAME_end, NULL);
      dt = ((FRAME_end.tv_sec - FRAME_begin.tv_sec) * 1000000 + (FRAME_end.tv_usec - FRAME_begin.tv_usec));
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

void PONG_Collision(int side)
{
  if (side == 1 || side == 3)
  {
    ballAngle -= ballAngle * 2;
  }
  else
  {
    ballAngle = side / 2 * M_PI + ((double)(rand() % 51) / 100) - 0.25;
  }
}

void PONG_Initialize()
{
  running = 1;
  free(buffer);
  buffer = malloc(sizeof(char *) * HEIGHT);
  for (int i = 0; i < HEIGHT; i++)
  {
    buffer[i] = malloc(sizeof(char) * WIDTH);
  }
  cls();
  srand(time(NULL));

  PONG_P1_Score = 0;
  PONG_P2_Score = 0;

  setConsoleColour(CYAN);
  setCursorPosition(WIDTH / 4, 1);
  printf("%d", PONG_P1_Score);
  setConsoleColour(BLUE);
  setCursorPosition(WIDTH - WIDTH / 4, 1);
  printf("%d", PONG_P2_Score);
  setConsoleColour(WHITE);
}

void PONG_Update()
{
  if (ballX + PONG_BALL_SPEED * cos(ballAngle) * dt >= WIDTH - 3 &&
    ballY >= PONG_P2_Y - 0.5 && ballY <= PONG_P2_Y + PONG_PADDLE_SIZE + 0.5)
  {
    PONG_Collision(2);
  }
  else
  {
    if (ballX + PONG_BALL_SPEED * cos(ballAngle) * dt >= WIDTH)
    {
      ballX = WIDTH / 2;
      ballY = HEIGHT / 2;
      ballAngle = (rand()%2)*M_PI;
      PONG_P1_Score++;
      setConsoleColour(CYAN);
      setCursorPosition(WIDTH / 4, 1);
      printf("%d", PONG_P1_Score);
      setConsoleColour(WHITE);
    }
  }
  if (ballX + PONG_BALL_SPEED * cos(ballAngle) * dt <= 2 && 
    ballY >= PONG_P1_Y - 0.5 && ballY <= PONG_P1_Y + PONG_PADDLE_SIZE + 0.5)
  {
    PONG_Collision(0);
  }
  else
  {
    if (ballX + PONG_BALL_SPEED * cos(ballAngle) * dt <= 0)
    {
      ballX = WIDTH / 2;
      ballY = HEIGHT / 2;
      ballAngle = (rand()%2)*M_PI;
      PONG_P2_Score++;
      setConsoleColour(BLUE);
      setCursorPosition(WIDTH - WIDTH / 4, 1);
      printf("%d", PONG_P2_Score);
      setConsoleColour(WHITE);
    }
  }
  if (ballY + PONG_BALL_SPEED * sin(ballAngle) * dt >= HEIGHT)
  {
    PONG_Collision(1);
  }
  if (ballY + PONG_BALL_SPEED * sin(ballAngle) * dt <= 2)
  {
    PONG_Collision(3);
  }
  ballX += PONG_BALL_SPEED * cos(ballAngle) * dt;
  ballY += PONG_BALL_SPEED * sin(ballAngle) * dt;
}

void PONG_Render()
{
  for (int y = 2; y < HEIGHT; y++)
  {
    for (int x = 0; x < WIDTH; x++)
    {
      if (distance(x, y, ballX, ballY) <= PONG_BALL_SIZE)
      {
        if (buffer[y][x] != '#')
        {
          setCursorPosition(x, y);
          printf("%c", BLOCK);
        }
        buffer[y][x] = '#';
      }
      else if (y >= PONG_P1_Y && y <= PONG_P1_Y + PONG_PADDLE_SIZE && x == 2)
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
      else if (y >= PONG_P2_Y && y <= PONG_P2_Y + PONG_PADDLE_SIZE && x == WIDTH - 3)
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