#include <vector>

#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

// A simple struct for nodes of a skip list.
struct node
{
  int key;
  // Can we safely make assumptions such as 'values are all nonnegative'?
  int value;
  // Number of forward pointers
  int level;
  // Following nodes
  // Are dynamic arrays admissible in this sort of application?
  std::vector<node*> forward;
  node(int k, const int v, int level);
};

// The Skip List class proper
class skip_list
{
public:
  skip_list(int max_level, float prob);
  ~skip_list();
  // methods of the data structure
  void insert(int search_key, int new_value);
  void del(int search_key);
  node* search(int search_key);
private:
  int max_level_;     // Maximum admissible level
  int level_;         // Actual level: highest level of any node
  float prob_;        // Node level ratio
  node* header_;
  node* nil_;
  int random_level(); // Calculates level of a node.
};

#endif  // SKIP_LIST_H_
