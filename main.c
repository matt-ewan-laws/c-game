#include  <stdio.h>
#include  <unistd.h>
#include  <stdlib.h>

#ifndef WINDOW_HEADER
#define WINDOW_HEADER

#include "window.h"

#endif

#ifndef DISPLAY_HEADER
#define DISPLAY_HEADER

#include "display.h"

#endif

struct Element *top_pane;

void init() {
  init_windows();
  struct Element *main_split = create_h_split_percent(70);
  top_pane = create_pane();
  struct Element *bottom_pane = create_pane();
  add_to_split(top_pane, main_split, FIRST);
  add_to_split(bottom_pane, main_split, SECOND);
  display_element(main_split, 2, 2, 100, 30);
  char *strs[4] = {"hello", "world", "test", "test"};
  add_strs(strs, 4, bottom_pane, 0, 1, 1);
}

void update() {
  char *display = (char*)malloc(20 * sizeof(char));
  int ch;
  if ((ch = get_latest_ch()) != -1) {
    sprintf(display, "You typed: %d   ", ch);
    add_str(display, top_pane, 10, 10);
    if (ch == 113) {
      destroy_windows();
      exit(0);
    }
  }
}

void draw() {
}


int main(void) {

  init();

  while (1) {
    update();
  }
}
