#include "../stuff.h"

struct card
{
  int value;
  char suit; // S H C D
};

struct card BJ_deck[52];
int BJ_deckIndex;
int BJ_bet;
int BJ_option;

void BJ_initialize();
void BJ_render();
int BJ_processInput();

struct card dealerCards[5];
struct card Cards[5];

int optionLeave();

int BJ_run()
{
  while (running)
  {
    if (optionLeave())
    {
      break;
    }
    while (1)
    {
      if (scanf("%d", &BJ_bet))
      {
        break;
      }
      else
      {
        scanf("%*s");
      }
      // do the betting
    }
    while (1)
    {
      setCursorPosition(0, 0);
      printf("Ws all aroundd");
      // play
    }
    // dealer does stuff
    // show outcome
  }
}

int optionLeave()
{
  int isLeaving = 0;
  while (1)
  {
    if (getKeyActuallyPressed(VK_SPACE))
    {
      if (!keyPressed)
      {
        if (isLeaving)
        {
          running = 0;
          return 1;
        }
        return 0;
      }
    }
    else if (getKeyActuallyPressed(0x25)) // left
    {
      isLeaving = 0;
    }
    else if (getKeyActuallyPressed(0x27)) // right
    {
      isLeaving = 1;
    }
    else
    {
      keyPressed = 0;
    }
  }
  return 0;
}

int BJ_play()
{
}

int BJ_processInput()
{
  if (getKeyActuallyPressed(VK_ESCAPE))
  {
    running = 0;
  }
  if (getKeyActuallyPressed(VK_SPACE))
  {
  }
  if (getKeyActuallyPressed(0x25))
  {
  }
  if (getKeyActuallyPressed(0x27))
  {
  }
  return 0;
}

void BJ_render()
{
}

void BJ_initialize()
{
  running = 1;
  disposeBuffer();
  cls();
  BJ_deckIndex = 0;
  BJ_bet = 0;
  BJ_option = 0;
  srand(time(NULL));
  struct card notShuffled[52];
  for (int v = 0; v < 13; v++)
  {
    for (int s = 0; s < 4; s++)
    {
      BJ_deck[v * 4 + s].value = 0;
      notShuffled[v * 4 + s].value = v + 1;

      if (s == 0)
        notShuffled[v * 4 + s].suit = 'S';
      if (s == 1)
        notShuffled[v * 4 + s].suit = 'H';
      if (s == 2)
        notShuffled[v * 4 + s].suit = 'C';
      if (s == 3)
        notShuffled[v * 4 + s].suit = 'D';
    }
  }
  int randPlace;
  for (int i = 0; i < 52; i++)
  {
    while (1)
    {
      randPlace = rand() % 52;
      if (BJ_deck[randPlace].value == 0)
      {
        BJ_deck[randPlace].value = notShuffled[i].value;
        BJ_deck[randPlace].suit = notShuffled[i].suit;
        break;
      }
    }
  }
}