#pragma once

#define FB_PIPE_GAP 6
#define FB_PIPE_SPEED 20.0
#define FB_PIPE_SIZE 6
#define FB_NUM_PIPES 3
#define FB_GRAVITY 15.0
#define FB_JUMP_DELAY 0.5
#define FB_MAX_VELOCITY 25.0
#define FB_JUMP_VELOCITY 15.0

extern double FB_pipeY[FB_NUM_PIPES];
extern double FB_pipeX[FB_NUM_PIPES];
extern short FB_pipeCanScore[FB_NUM_PIPES];
extern double FB_playerY;
extern double FB_playerVelY;
extern double FB_jumpCD;
extern short FB_keyPressed;
extern int FB_score;

void FB_render();
void FB_update();
void FB_initialize();

int FB_run();
