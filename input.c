#include  <stdlib.h>

enum ActionType  { KEY = 0, ACTION = 1 };

union Action {
  struct KeyCombinations ** key_combinations;
  void (*action)(void);
};

struct KeyCombinations {
  int key_code;
  enum ActionType action_type;
  union Action action;
};

struct KeyCombinations * init_key_combinations();

void add_key_combinations(struct KeyCombinations key_combinations, int ** keys, void (*action)(void));

struct KeyCombinations ** next_action(struct KeyCombinations ** key_combinations, int key_pressed);
