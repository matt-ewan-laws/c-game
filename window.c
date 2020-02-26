#include  <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include  "window.h"

enum SplitType { HORIZONTAL = 0, VERTICAL = 1 };

enum Cardinal { NORTH = 0, SOUTH = 2, EAST = 3, WEST = 4 };

struct SplitPercent {
	enum SplitType direction;
	int percent;
	struct Element *first;
	struct Element *second;
};

struct SplitFixed {
	enum SplitType direction;
	enum Cardinal anchor_point;
	int size;
	struct Element *first;
	struct Element *second;
};

struct RootWindow {
	struct Element *child;
};

struct Window {
	WINDOW * win;
};

int init_ncurses()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	nodelay(stdscr, TRUE);
	refresh();
	return 1;
}


int get_latest_ch()
{
	int ch;
	if ((ch = getch()) == ERR) {
		return -1;
	}
	else {
		return ch;
	}
}

void init_windows()
{
	init_ncurses();
}

void destroy_windows()
{
	endwin();
}

struct Element * create_empty_element()
{
	struct Element *el = malloc(sizeof(struct Element));
	el->type = EMPTY;
	return el;
}

struct Element * create_h_split_percent(int percent)
{
	struct SplitPercent *split = malloc(sizeof(struct SplitPercent));
	split->direction = HORIZONTAL;
	split->percent = percent;
	split->first = create_empty_element();
	split->second = create_empty_element();
	struct Element * element = malloc(sizeof(struct Element));
	element->type = SPLIT_PERCENT;
	element->element = split;
	return element;
}

void add_to_split(struct Element * el, struct Element * parent, enum BinaryItem item)
{
	struct SplitPercent *split = (struct SplitPercent*)parent->element;
	switch (item) {
		case FIRST: split->first = el; return;
		case SECOND: split->second = el; return;
	}
}

void display_pane(struct Pane * pane, int x, int y, int width, int height);
void display_split_percent(struct SplitPercent * split, int x, int y, int width, int height);


struct Element * create_pane()
{
	struct Element *el = malloc(sizeof(struct Element));
	struct Pane *pane = malloc(sizeof(struct Pane));
	el->type = PANE;
	el->element = pane;
	return el;
}

void display_pane(struct Pane * pane, int x, int y, int width, int height)
{
	if (pane->win == NULL) {
		WINDOW *win = newwin(height, width, y, x);
		struct Window *container = malloc(sizeof(struct Window));
		container->win = win;
		pane->win = container;
	}
	box(pane->win->win, 0,0);
	wrefresh(pane->win->win);
}

int display_element(struct Element * root, int x, int y, int width, int height)
{
	switch (root->type) {
		case SPLIT_PERCENT:
			display_split_percent((struct SplitPercent*)root->element, x, y, width, height); break;
		case PANE:
			display_pane((struct Pane*)root->element, x, y, width, height); break;
		case EMPTY: return 1;
	}
	return 1;
}

void display_split_percent(struct SplitPercent * split, int x, int y, int width, int height)
{
	int first_num_lines, first_num_cols, first_x, first_y, second_num_lines, second_num_cols, second_x, second_y;

	first_x = x;
	first_y = y;
	switch (split->direction) {
		case HORIZONTAL:
			first_num_lines = ((height * split->percent) / 100);
			first_num_cols = width;
			second_x = x;
			second_y = first_num_lines + 2;
			second_num_lines = height - first_num_lines - 1;
			second_num_cols = width;
			break;
		case VERTICAL:
			first_num_lines = height;
			first_num_cols = ((width * split->percent) / 100);
			second_x = first_num_cols + 1;
			second_y = y;
			second_num_lines = height;
			second_num_cols = width - first_num_cols - 1;
			break;
	}
	display_element(split->first, first_x, first_y, first_num_cols, first_num_lines);
	display_element(split->second, second_x, second_y, second_num_cols, second_num_lines);
}

/**
 * +---------------------+
 * |                     |
 * |                     |
 * +---------------------+
 * | +-----------------+ |
 * | |                 | |
 * | |                 | |
 * | +-----------------+ |
 * +---------------------+
 */

int get_pane_height(struct Element * paneEl)
{
	int height, width;
	struct Pane *pane = (struct Pane*)paneEl->element;
	getmaxyx(pane->win->win, height, width);
	return height;
}

int get_pane_width(struct Element * paneEl)
{
	int height, width;
	struct Pane *pane = (struct Pane*)paneEl->element;
	getmaxyx(pane->win->win, height, width);
	return width;
}

void add_str(char * str, struct Element * paneEl, int x, int y)
{
	struct Pane *pane = (struct Pane*)paneEl->element;
	WINDOW *win = pane->win->win;
	mvwaddstr(win, y, x, str);
	wrefresh(win);
}

int get_max_of_strs(char* strs[], int start, int end)
{
	int cur_len, max_len = 0;
	int i;
	for (i = start; i < end; i++) {
		cur_len = strlen(strs[i]);
		if (cur_len > max_len) {
			max_len = cur_len;
		}
	}
	return max_len;
}

void pause()
{
  getch();
  endwin();
}
