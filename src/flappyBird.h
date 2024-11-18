#include "utils.h"

#define FB_PIPE_GAP 6
#define FB_PIPE_SPEED 20.0
#define FB_PIPE_SIZE 6
#define FB_NUM_PIPES 3
#define FB_GRAVITY 15.0
#define FB_JUMP_DELAY 0.5
#define FB_MAX_VELOCITY 25.0
#define FB_JUMP_VELOCITY 15.0

double FB_pipeY[FB_NUM_PIPES];
double FB_pipeX[FB_NUM_PIPES];
short FB_pipeCanScore[FB_NUM_PIPES];

double FB_playerY = HEIGHT / 2.0;
double FB_playerVelY = 0;

double FB_jumpCD = FB_JUMP_DELAY;
short FB_keyPressed = 0;

int FB_score = 0;

void FB_render();
void FB_update();
void FB_initialize();

int FB_run() {
  FB_initialize();
  while (running) {
    gettimeofday(&begin, NULL); // get begin of frame
    FB_update();
    FB_render();

    int c = getch();
    if (c == 'q') {
      return 0;
    }
    if (c == ' ') {
      if (!FB_keyPressed) {
        FB_keyPressed = 1;

        if (FB_jumpCD <= 0) {
          FB_playerVelY = -FB_JUMP_VELOCITY;
          FB_jumpCD = FB_JUMP_DELAY;
        }
      }
    } else {
      FB_keyPressed = 0;
    }

    avah_sleep(1000.0 / 240.0);

    gettimeofday(&end, NULL);

    dt_seconds =
        end.tv_sec - begin.tv_sec + (end.tv_usec - begin.tv_usec) / 1000000.0;
    mvprintw(1, 0, "dt in seconds: %f", dt_seconds);
  }

  mvprintw(0, 0, "Your Score: %d\n", FB_score);
  mvprintw(1, 0, "Press [R] to play again");
  mvprintw(2, 0, "Press [Q] to quit");
  while (1) {
    int c = getch();
    if (c == 'r') {
      break;
    }
    if (c == 'q') {
      return 0;
    }
    avah_sleep(1);
  }
  FB_run();
  return 0;
}

void FB_initialize() {
  running = 1;
  disposeBuffer();
  cls();
  FB_playerY = HEIGHT / 2.0;
  FB_playerVelY = 0;
  FB_playerY = HEIGHT / 2.0;
  FB_playerVelY = 0;
  FB_score = 0;

  srand(time(NULL));

  for (int i = 0; i < FB_NUM_PIPES; i++) {
    FB_pipeX[i] = WIDTH + i * 40;
    FB_pipeY[i] = rand() % (HEIGHT - FB_PIPE_GAP - 8) + 4;
    FB_pipeCanScore[i] = 1;
  }
  mvprintw(0, 0, "Your Score: 0");
}

void FB_update() {
  for (int i = 0; i < FB_NUM_PIPES; i++) {
    FB_pipeX[i] -= FB_PIPE_SPEED * dt_seconds;
    if (FB_pipeX[i] <= -FB_PIPE_SIZE / 2.0) {
      FB_pipeX[i] = WIDTH + FB_PIPE_SIZE;
      FB_pipeY[i] = rand() % (HEIGHT - FB_PIPE_GAP - 8) + 4;
      FB_pipeCanScore[i] = 1;
    }
  }

  if (FB_jumpCD > 0) {
    FB_jumpCD -= dt_seconds;
  }
  FB_playerVelY += FB_GRAVITY * dt_seconds;
  if (FB_playerVelY > FB_MAX_VELOCITY) {
    FB_playerVelY = FB_MAX_VELOCITY;
  }

  FB_playerY += FB_playerVelY * dt_seconds;
  if (FB_playerY <= 0) {
    FB_playerY = 0;
    FB_playerVelY = FB_MAX_VELOCITY;
  }
  if (FB_playerY >= HEIGHT - 1) {
    FB_playerVelY = 0;
    FB_playerY = HEIGHT - 1;
    running = 0;
  }
  for (int i = 0; i < 3; i++) {
    if (FB_pipeX[i] - FB_PIPE_SIZE / 2.0 <= 10) {
      if (FB_pipeX[i] + FB_PIPE_SIZE / 2.0 > 10) {
        if (FB_playerY <= FB_pipeY[i] ||
            FB_playerY > FB_pipeY[i] + FB_PIPE_GAP) {
          running = 0;
        } else {
          if (FB_pipeCanScore[i]) {
            FB_score++;
            FB_pipeCanScore[i] = 0;
          }
        }
        break;
      }
    }
  }
}

void FB_render() {
  cls();
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (x == 10 && y == (int)FB_playerY) {
        mvprintw(y, x, "%c", BLOCK);
      } else {
        short pipeHere = 0;
        for (int i = 0; i < FB_NUM_PIPES; i++) {
          if (x > FB_pipeX[i] - FB_PIPE_SIZE / 2.0 &&
              x <= FB_pipeX[i] + FB_PIPE_SIZE / 2.0) {
            if (y <= FB_pipeY[i] || y > FB_pipeY[i] + FB_PIPE_GAP) {
              setConsoleColor(GREEN);
              mvprintw(y, x, "%c", BLOCK);
              setConsoleColor(WHITE);
              pipeHere = 1;
              break;
            }
          }
        }
      }
    }
  }
  mvprintw(0, 0, "Your Score: %d", FB_score);
}
