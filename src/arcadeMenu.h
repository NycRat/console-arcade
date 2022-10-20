#include "utils.h"

void ARCADE_initialize();

int PONG_run();
int FB_run();
int SNAKE_run();

int ARCADE_run()
{
  ARCADE_initialize();
  while (running)
  {
    if (MENU_processInput(PONG_run, FB_run, SNAKE_run))
    {
      ARCADE_initialize();
    }
    // ARCADE_processInput();
    MENU_render();
  }
  cls();
  return 0;
}

void ARCADE_initialize()
{
  MENU_initialize("PONG", "FLAPPY BIRD", "SNAKE");
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
      "           %c             %c%c%c%c%c%c%c%c%c%c%c%c        %c%c%c%c%c%c%c%c              %c            "
      "%c%c%c%c%c%c       %c%c%c%c%c%c%c%c%c\n"
      "          %c %c            %c           %c      %c        %c            %c %c           %c     %c%c     %c\n"
      "         %c   %c           %c            %c    %c                     %c   %c          %c       %c    %c\n"
      "        %c     %c          %c           %c    %c                     %c     %c         %c        %c   %c\n"
      "       %c       %c         %c%c%c%c%c%c%c%c%c%c%c%c     %c                    %c       %c        %c        %c   "
      "%c\n"
      "      %c%c%c%c%c%c%c%c%c%c%c        %c  %c%c%c           %c                   %c%c%c%c%c%c%c%c%c%c%c       %c   "
      "     %c   %c%c%c%c%c%c%c%c\n"
      "     %c           %c       %c    %c%c%c         %c                  %c           %c      %c        %c   %c\n"
      "    %c             %c      %c     %c%c%c        %c                 %c             %c     %c        %c   %c\n"
      "   %c               %c     %c       %c%c%c      %c                %c               %c    %c       %c    %c\n"
      "  %c                 %c    %c         %c%c%c     %c         %c    %c                 %c   %c     %c%c     %c\n"
      " %c                   %c   %c           %c%c%c    %c%c%c%c%c%c%c%c%c    %c                   %c  %c%c%c%c%c%c   "
      "    %c%c%c%c%c%c%c%c%c\n",
      BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK,
      BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK,
      BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK,
      BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK,
      BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK,
      BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK,
      BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK,
      BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK,
      BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK,
      BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK,
      BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK,
      BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK,
      BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK, BLOCK);
  // no way this is the only solution
  setConsoleColour(WHITE);
  setCursorPosition(WIDTH - 32, HEIGHT - 1);
  printf("Press ESCAPE to exit any game");
}
