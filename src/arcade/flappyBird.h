#include "../stuff.h"

#define FB_PIPE_GAP 6
#define FB_PIPE_SPEED 0.02
#define FB_PIPE_SIZE 6
#define FB_NUM_PIPES 3
#define FB_GRAVITY 0.0001
#define FB_JUMP_DELAY 100
#define FB_MAX_VELOCITY 0.035
#define FB_JUMP_HEIGHT 0.02

double FB_pipeY[FB_NUM_PIPES];
double FB_pipeX[FB_NUM_PIPES];
short FB_pipeCanScore[FB_NUM_PIPES];

double FB_playerY = HEIGHT / 2;
double FB_playerVelY = 0;

double FB_jumpCD = FB_JUMP_DELAY;
short FB_keyPressed = 0;

int FB_score = 0;

void FB_render();
void FB_update();
void FB_initialize();

int FB_run()
{
  FB_initialize();
  while (running)
  {
    gettimeofday(&begin, NULL);
    FB_update();
    FB_render();
    if (getKeyActuallyPressed(VK_ESCAPE))
    {
      return 0;
    }
    if (GetAsyncKeyState(0x20))
    {
      if (!FB_keyPressed)
      {
        FB_keyPressed = 1;

        if (FB_jumpCD <= 0)
        {
          FB_playerVelY = -FB_JUMP_HEIGHT;
          FB_jumpCD = FB_JUMP_DELAY;
        }
      }
    }
    else
    {
      FB_keyPressed = 0;
    }

    dt = 0;
    while (dt <= 0)
    {
      gettimeofday(&end, NULL);
      dt = ((end.tv_sec - begin.tv_sec) * 1000000 + (end.tv_usec - begin.tv_usec));
      dt /= 1000;
    }
    tempTime += dt;
    if (tempTime >= 1000)
    {
      tempTime -= 1000;
    }
    setCursorPosition(0, 0);
    printf("%f", FB_playerY);
  }
}

void FB_initialize()
{
  running = 1;
  disposeBuffer();
  cls();
  FB_playerY = HEIGHT / 2;
  FB_playerVelY = 0;
  FB_playerY = HEIGHT / 2;
  FB_playerVelY = 0;

  srand(time(NULL));

  for (int i = 0; i < FB_NUM_PIPES; i++)
  {
    FB_pipeX[i] = WIDTH + i * 40;
    FB_pipeY[i] = rand() % (HEIGHT - FB_PIPE_GAP - 8) + 4;
  }
}

void FB_update()
{
  for (int i = 0; i < FB_NUM_PIPES; i++)
  {
    FB_pipeX[i] -= FB_PIPE_SPEED * dt;
    if (FB_pipeX[i] <= -FB_PIPE_SIZE / 2)
    {
      FB_pipeX[i] = WIDTH + FB_PIPE_SIZE;
      FB_pipeY[i] = rand() % (HEIGHT - FB_PIPE_GAP - 8) + 4;
    }
  }

  if (FB_jumpCD > 0)
  {
    FB_jumpCD -= dt;
  }
  FB_playerVelY += FB_GRAVITY * dt;
  if (FB_playerVelY > FB_MAX_VELOCITY)
  {
    FB_playerVelY = FB_MAX_VELOCITY;
  }

  FB_playerY += FB_playerVelY * dt;
  if (FB_playerY <= 0)
  {
    FB_playerY = 0;
    FB_playerVelY = FB_MAX_VELOCITY;
  }
  if (FB_playerY >= HEIGHT - 1)
  {
    FB_playerVelY = 0;
    FB_playerY = HEIGHT - 1;
    printf("lolo bad");
  }
}

void FB_render()
{
  for (int y = 0; y < HEIGHT; y++)
  {
    for (int x = 0; x < WIDTH; x++)
    {
      if (x == 10 && y == (int)FB_playerY)
      {
        if (buffer[y][x] != '#')
        {
          setCursorPosition(x, y);
          printf("%c", BLOCK);
        }
        buffer[y][x] = '#';
      }
      else
      {
        short pipeHere = 0;
        for (int i = 0; i < FB_NUM_PIPES; i++)
        {
          if (x > FB_pipeX[i] - FB_PIPE_SIZE / 2 &&
              x <= FB_pipeX[i] + FB_PIPE_SIZE / 2)
          {
            if (y <= FB_pipeY[i] ||
                y > FB_pipeY[i] + FB_PIPE_GAP)
            {
              if (buffer[y][x] != '#')
              {
                setConsoleColour(LIGHTGREEN);
                setCursorPosition(x, y);
                printf("%c", BLOCK);
                setConsoleColour(WHITE);
              }
              buffer[y][x] = '#';
              pipeHere = 1;
              break;
            }
          }
        }
        if (!pipeHere)
        {
          if (buffer[y][x] == 'L')
          {
            setCursorPosition(x, y);
            printf(" ");
            buffer[y][x] = ' ';
          }
          if (buffer[y][x] == '#')
          {
            setCursorPosition(x, y);
            printf(" ");
            buffer[y][x] = 'L';
          }
        }
      }
    }
  }
  setCursorPosition(0, 0);
}