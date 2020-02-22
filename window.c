#include "window.h"

#include  <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

enum SplitType { HORIZONTAL = 0, VERTICAL = 1 };

enum Cardinal { NORTH = 0, SOUTH = 2, EAST = 3, WEST = 4 };

enum BinaryItem { FIRST = 0, SECOND = 1 };

enum ElementType { SPLIT_FIXED = 0, SPLIT_PERCENT = 1, PANE = 2, EMPTY = 3, ROOT = 4 };

struct Element {
	enum ElementType type;
	void *element;
};

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

struct Pane {
	int hasBorder;
	WINDOW * win;
};

int init_ncurses()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	refresh();
	return 1;
}

void init_windows()
{
	init_ncurses();
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
int display_element(struct Element * root, int x, int y, int width, int height);
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
		pane->win = newwin(height, width, y, x);
	}
	box(pane->win, 0,0);
	wrefresh(pane->win);
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
	return NULL;
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
 *
Window *window_create_bottom(int height, int width, int starty, int startx) {
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);
	wrefresh(local_win);

	return local_win;
}
*/

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

int main(void) {
	init_windows();
	struct Element *main_split = create_h_split_percent(70);
	struct Element *top_pane = create_pane();
	struct Element *bottom_pane = create_pane();
	add_to_split(top_pane, main_split, FIRST);
	add_to_split(bottom_pane, main_split, SECOND);
	display_element(main_split, 2, 2, 100, 30);
	getch();
	endwin();
}
