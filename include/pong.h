#pragma once

#include "utils.h"

#define PONG_BALL_SPEED 80.0
#define PONG_BALL_SIZE 1
#define PONG_PADDLE_SPEED 80.0
#define PONG_PADDLE_SIZE 3

double PONG_ballAngle;
struct Vector2f PONG_ballPos;
struct Vector2f PONG_ballVel;
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
