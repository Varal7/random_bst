#include "splay_tree.h"

int main() {

  SplayTree *s = new SplayTree();

  s->insert(0,0);
  s->insert(1,0);
  s->insert(4,0);
  s->insert(3,0);
  s->insert(2,0);
  s->remove(1);
  s->remove(4);
  s->remove(3);
  s->remove(0);
  s->remove(2);

  delete s;

}
