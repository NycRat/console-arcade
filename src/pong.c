#include "pong.h"
#include "utils.h"
#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include <sys/time.h>
#define PONG_BALL_SPEED 80.0
#define PONG_BALL_SIZE 1
#define PONG_PADDLE_SPEED 80.0
#define PONG_PADDLE_SIZE 3

int PONG_run()
{
  PONG_initialize();
  while (running)
  {
    gettimeofday(&begin, NULL);
    PONG_processInput();
    PONG_update();
    PONG_render();

    avah_sleep(1);

    gettimeofday(&end, NULL);
    dt_seconds = end.tv_sec - begin.tv_sec + (end.tv_usec - begin.tv_usec) / 1000000.0;

    tempTime += dt_seconds;

    if (tempTime >= 1000)
    {
      tempTime -= 1000;
      mvprintw(0, 0, "FPS: %d", frames);
      frames = 0;
    }
    frames++;
  }
  return 0;
}

void PONG_processInput()
{
  int c = getch();
  if (c == 'q')
  {
    running = 0;
  }
  if (c == 'w')
  {
    PONG_p1Y -= PONG_PADDLE_SPEED * dt_seconds;
    PONG_p1Y = ((PONG_p1Y > 2) ? PONG_p1Y : 1.5);
  }
  if (c == 's')
  {
    PONG_p1Y += PONG_PADDLE_SPEED * dt_seconds;
    PONG_p1Y = ((PONG_p1Y + PONG_PADDLE_SIZE < HEIGHT) ? PONG_p1Y : HEIGHT - PONG_PADDLE_SIZE);
  }
  if (c == KEY_UP)
  {
    PONG_p2Y -= PONG_PADDLE_SPEED * dt_seconds;
    PONG_p2Y = ((PONG_p2Y > 2) ? PONG_p2Y : 1.5);
  }
  if (c == KEY_DOWN)
  {
    PONG_p2Y += PONG_PADDLE_SPEED * dt_seconds;
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
    PONG_ballAngle = side / 2.0 * M_PI + ((double)(rand() % 51) / 100) - 0.25;
    PONG_ballVel.x = cos(PONG_ballAngle);
    PONG_ballVel.y = sin(PONG_ballAngle);
  }
}

void PONG_initialize()
{
  running = 1;
  dispose_buffer();
  cls();
  srand(time(NULL));

  PONG_p1Score = 0;
  PONG_p2Score = 0;
  PONG_ballAngle = 0;

  PONG_ballPos.x = WIDTH / 2.0 - 30;
  PONG_ballPos.y = HEIGHT / 2.0;

  PONG_ballVel.x = 1;
  PONG_ballVel.y = 0;

  PONG_p1Y = HEIGHT / 2.0;
  PONG_p2Y = HEIGHT / 2.0;
  PONG_numRandSide[0] = 0;
  PONG_numRandSide[1] = 0;

  set_text_color(COLOR_CYAN);
  mvprintw(1, WIDTH * 0.25, "%d", PONG_p1Score);
  set_text_color(COLOR_GREEN);
  mvprintw(1, WIDTH * 0.75, "%d", PONG_p2Score);
  set_text_color(COLOR_WHITE);
}

void PONG_update()
{
  if (PONG_ballPos.x + PONG_BALL_SPEED * PONG_ballVel.x * dt_seconds >= WIDTH - 3 && PONG_ballPos.y >= PONG_p2Y - 0.5 &&
      PONG_ballPos.y <= PONG_p2Y + PONG_PADDLE_SIZE + 0.5)
  {
    PONG_collision(2);
  }
  else
  {
    if (PONG_ballPos.x + PONG_BALL_SPEED * PONG_ballVel.x * dt_seconds >= WIDTH)
    {
      int side = rand() % 2;
      if (PONG_numRandSide[side] >= 2)
      {
        PONG_numRandSide[side] = 0;
        side = !side;
      }
      PONG_numRandSide[!side] = 0;
      PONG_numRandSide[side]++;

      PONG_ballPos.x = WIDTH * 0.5 + ((side) ? 30 : -30);
      PONG_ballPos.y = HEIGHT * 0.5;
      PONG_ballAngle = side * M_PI;
      PONG_ballVel.x = cos(PONG_ballAngle);
      PONG_ballVel.y = sin(PONG_ballAngle);
      PONG_p1Score++;
      set_text_color(COLOR_CYAN);
      mvprintw(1, WIDTH * 0.25, "%d", PONG_p1Score);
      set_text_color(COLOR_WHITE);
    }
  }
  if (PONG_ballPos.x + PONG_BALL_SPEED * PONG_ballVel.x * dt_seconds <= 2 && PONG_ballPos.y >= PONG_p1Y - 0.5 &&
      PONG_ballPos.y <= PONG_p1Y + PONG_PADDLE_SIZE + 0.5)
  {
    PONG_collision(0);
  }
  else
  {
    if (PONG_ballPos.x + PONG_BALL_SPEED * PONG_ballVel.x * dt_seconds <= 0)
    {
      int side = rand() % 2;
      if (PONG_numRandSide[side] >= 2)
      {
        PONG_numRandSide[side] = 0;
        side = !side;
      }

      PONG_numRandSide[!side] = 0;
      PONG_numRandSide[side]++;

      PONG_ballPos.x = WIDTH * 0.5 + ((side) ? 30 : -30);
      PONG_ballPos.y = HEIGHT * 0.5;
      PONG_ballAngle = side * M_PI;
      PONG_ballVel.x = cos(PONG_ballAngle);
      PONG_ballVel.y = sin(PONG_ballAngle);
      PONG_p2Score++;
      set_text_color(COLOR_GREEN);
      mvprintw(1, WIDTH * 0.75, "%d", PONG_p2Score);
      set_text_color(COLOR_WHITE);
    }
  }
  if (PONG_ballPos.y + PONG_BALL_SPEED * PONG_ballVel.y * dt_seconds >= HEIGHT)
  {
    PONG_collision(1);
  }
  if (PONG_ballPos.y + PONG_BALL_SPEED * PONG_ballVel.y * dt_seconds <= 2)
  {
    PONG_collision(3);
  }
  PONG_ballPos.x += PONG_BALL_SPEED * PONG_ballVel.x * dt_seconds;
  PONG_ballPos.y += PONG_BALL_SPEED * PONG_ballVel.y * dt_seconds;
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
          mvprintw(y, x, "%c", BLOCK);
        }
        buffer[y][x] = '#';
      }
      else if (y >= PONG_p1Y && y < PONG_p1Y + PONG_PADDLE_SIZE && x == 2)
      {
        if (buffer[y][x] != '1')
        {
          set_text_color(COLOR_CYAN);
          mvprintw(y, x, "%c", BLOCK);
          set_text_color(COLOR_WHITE);
        }
        buffer[y][x] = '1';
      }
      else if (y >= PONG_p2Y && y < PONG_p2Y + PONG_PADDLE_SIZE && x == WIDTH - 3)
      {
        if (buffer[y][x] != '2')
        {
          set_text_color(COLOR_GREEN);
          mvprintw(y, x, "%c", BLOCK);
          set_text_color(COLOR_WHITE);
        }
        buffer[y][x] = '2';
      }
      else
      {
        if (buffer[y][x] == 'L')
        {
          mvprintw(y, x, " ");
          buffer[y][x] = ' ';
        }
        if (buffer[y][x] == '#' || buffer[y][x] == '1' || buffer[y][x] == '2')
        {
          mvprintw(y, x, " ");
          buffer[y][x] = 'L';
        }
      }
    }
  }
}

double distance(double x1, double y1, double x2, double y2)
{
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
