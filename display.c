#include "window.h"

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

int main(void) {
  init_windows();
  struct Element *main_split = create_h_split_percent(70);
  struct Element *top_pane = create_pane();
  struct Element *bottom_pane = create_pane();
  add_to_split(top_pane, main_split, FIRST);
  add_to_split(bottom_pane, main_split, SECOND);
  display_element(main_split, 2, 2, 100, 30);
  char *strs[4] = {"hello", "world", "test", "test"};
  add_strs(strs, 4, bottom_pane, 0, 1, 1);
  pause();
}
