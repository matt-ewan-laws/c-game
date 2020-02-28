#ifndef DISPLAY_HEADER
#define DISPLAY_HEADER

#include "display.h"

#include <stdio.h>
#include <stdlib.h>


/**
 * function to add a list of strings
 */
void add_strs(char *strs[], int num, struct Element *paneEl, int start_point,
              int x, int y) {
  int height, width;
  int rows_to_display;
  int next_x;
  int i;
  int padding = 1;
  int gutter = 2;

  // WINDOW *win = pane->win;
  // mvprintw(2, 2, "rows_to_display", rows_to_display);
  if (num > 0) {
    height = get_pane_height(paneEl);
    width = get_pane_width(paneEl);
    if (height - y - padding > num) {
      rows_to_display = num;
    } else {
      rows_to_display = height - y - padding;
    }
    for (i = start_point; i < start_point + rows_to_display; i++) {
      add_str(strs[i], paneEl, x, i - start_point + y);
    }
    next_x =
        x + get_max_of_strs(strs, start_point, start_point + rows_to_display);
    // Good old recursive function kept things much simpler
    add_strs(strs, num - rows_to_display, paneEl, start_point + rows_to_display,
             next_x + gutter, y);
  } else {
    return;
  }
}

#endif
