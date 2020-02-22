
// #include "SDL.h"
#include  <stdio.h>
#include  <unistd.h>

#define DELAY 30000
#define CH_POINTER '+'

void init() {
}

void update() {
}

void draw(struct GameData * gameData) {
}


int main(int argc, char *argv[]) {
  int ch;
  initscr();
  while((ch = getch()) != KEY_F(1))
    {
      update();
      draw();
    }
  endwin();
  return 0;
}

/* int main(int argc, char *argv[]) { */
/*   printf("Initialising SDL.\n"); */
/*   if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)) { */
/*     printf("Could not initialize SDL: %s.\n", SDL_GetError()); */
/*     exit(-1); */
/*   } */
/*   printf("SDL Initialized.\n"); */
/*   printf("Quitting SDL. \n"); */
/*   /\* Shutdown all subsystems *\/ */
/*   SDL_Quit(); */
/*   printf("Quiting... \n"); */
/*   exit(0); */
/* } */

