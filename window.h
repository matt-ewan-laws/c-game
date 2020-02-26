enum ElementType { SPLIT_FIXED = 0, SPLIT_PERCENT = 1, PANE = 2, EMPTY = 3, ROOT = 4 };

enum BinaryItem { FIRST = 0, SECOND = 1 };

struct Element {
	enum ElementType type;
	void *element;
};

void init_windows();

struct Element * create_h_split_percent(int percent);
struct Element * create_pane();

struct Pane {
	int hasBorder;
	struct Window * win;
};

int get_max_of_strs(char* strs[], int start, int end);
int get_pane_width(struct Element * paneEl);
int get_pane_height(struct Element * paneEl);

void add_to_split(struct Element * el, struct Element * parent, enum BinaryItem item);

void add_str(char * str, struct Element * paneEl, int x, int y);

int display_element(struct Element * root, int x, int y, int width, int height);
void pause();
