#include "../stuff.h"

void ARCADE_render();
void ARCADE_initialize();
void ARCADE_processInput();
int ARCADE_executeOption();

int PONG_run();
int FB_run();
int SNAKE_run();

int ARCADE_run()
{
  ARCADE_initialize();
  while (running)
  {
    ARCADE_processInput();
    ARCADE_render();
    setCursorPosition(0, 0);
    printf("%d", option);
  }
  return 0;
}

void ARCADE_processInput()
{
  if (getKeyActuallyPressed(VK_SPACE))
  {
    if (!keyPressed)
    {
      keyPressed = 1;
      if (ARCADE_executeOption() == 1)
      {
        running = 0;
        return;
      }
      ARCADE_initialize();
    }
  }
  else if (getKeyActuallyPressed(0x26)) // UP
  {
    if (!keyPressed)
    {
      if (option > 0)
      {
        option--;
      }
      keyPressed = 1;
    }
  }
  else if (getKeyActuallyPressed(0x28)) // DOWN
  {
    if (!keyPressed)
    {
      if (option < 3) // idk, 3 for now
      {
        option++;
      }
      keyPressed = 1;
    }
  }
  else
  {
    keyPressed = 0;
  }
}

int ARCADE_executeOption()
{
  if (option == 0)
  {
    return PONG_run();
  }
  else if (option == 1)
  {
    return FB_run();
  }
  else if (option == 2)
  {
  }
  else if (option == 3)
  {
    return 1;
  }
  return -1;
}

void ARCADE_initialize()
{
  option = 0;
  running = 1;
  disposeBuffer();
  cls();
  /*
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

"
             #             ############        ########              #            ######       #########\n
            # #            #           #      #        #            # #           #     ##     #\n
           #   #           #            #    #                     #   #          #       #    #\n
          #     #          #           #    #                     #     #         #        #   #\n
         #       #         ############     #                    #       #        #        #   #\n
        ###########        #  ###           #                   ###########       #        #   ########\n
       #           #       #    ###         #                  #           #      #        #   #\n
      #             #      #     ###        #                 #             #     #        #   #\n
     #               #     #       ###      #                #               #    #       #    #\n
    #                 #    #         ###     #         #    #                 #   #     ##     #\n
   #                   #   #           ###    #########    #                   #  ######       #########\n
"

AISJIDJANCOANSONACINICSNAOSCNOICNCSAOCINCASNCASNCOSNACONAsoase

  */
  setConsoleColour(CYAN);
  setCursorPosition(0, 2);

  // xd
  printf(
      "           %c             %c%c%c%c%c%c%c%c%c%c%c%c        %c%c%c%c%c%c%c%c              %c            %c%c%c%c%c%c       %c%c%c%c%c%c%c%c%c\n"
      "          %c %c            %c           %c      %c        %c            %c %c           %c     %c%c     %c\n"
      "         %c   %c           %c            %c    %c                     %c   %c          %c       %c    %c\n"
      "        %c     %c          %c           %c    %c                     %c     %c         %c        %c   %c\n"
      "       %c       %c         %c%c%c%c%c%c%c%c%c%c%c%c     %c                    %c       %c        %c        %c   %c\n"
      "      %c%c%c%c%c%c%c%c%c%c%c        %c  %c%c%c           %c                   %c%c%c%c%c%c%c%c%c%c%c       %c        %c   %c%c%c%c%c%c%c%c\n"
      "     %c           %c       %c    %c%c%c         %c                  %c           %c      %c        %c   %c\n"
      "    %c             %c      %c     %c%c%c        %c                 %c             %c     %c        %c   %c\n"
      "   %c               %c     %c       %c%c%c      %c                %c               %c    %c       %c    %c\n"
      "  %c                 %c    %c         %c%c%c     %c         %c    %c                 %c   %c     %c%c     %c\n"
      " %c                   %c   %c           %c%c%c    %c%c%c%c%c%c%c%c%c    %c                   %c  %c%c%c%c%c%c       %c%c%c%c%c%c%c%c%c\n",
      BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK);
  // no way this is the only solution

  setConsoleColour(WHITE);
  setCursorPosition(WIDTH / 3 + 3, 15);
  printf("PONG");
  setCursorPosition(WIDTH / 3 - 1, 19);
  printf("FLAPPY BIRD");
  setCursorPosition(WIDTH / 3 + 2, 23);
  printf("SNAKE");
  setCursorPosition(WIDTH / 3 - 2, 27);
  printf("EXIT");
}

void ARCADE_render()
{
  for (int b = 0; b < 4; b++)
  {
    char tempColour = 'W';
    if (b == option)
    {
      tempColour = 'G';
      setConsoleColour(GREEN);
    }

    if (buffer[15 + b * 4][WIDTH / 4] != tempColour)
    {
      setCursorPosition(WIDTH / 4, 15 + b * 4);
      printf("%c", BLOCK);
    }
    buffer[15 + b * 4][WIDTH / 4] = tempColour;

    if (buffer[15 + b * 4][WIDTH - WIDTH / 4 - 1] != tempColour)
    {
      setCursorPosition(WIDTH - WIDTH / 4 - 1, 15 + b * 4);
      printf("%c", BLOCK);
    }
    buffer[15 + b * 4][WIDTH - WIDTH / 4 - 1] = tempColour;

    for (int y = 14 + b * 4; y < b * 4 + 17; y += 2)
    {
      for (int x = WIDTH / 4; x < WIDTH - WIDTH / 4; x++)
      {
        if (buffer[y][x] != tempColour)
        {
          setCursorPosition(x, y);
          printf("%c", BLOCK);
        }
        buffer[y][x] = tempColour;
      }
    }
    setConsoleColour(WHITE);
  }
  setCursorPosition(0, 0);
}