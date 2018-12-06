#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

#include <vector>
#include "dictionary.h"

// A simple struct for SkipNodes of a skip list.
struct SkipNode : public Item
{
  int key, value;
  // Number of forward pointers
  int level;
  // Following SkipNodes
  // Are dynamic arrays admissible in this sort of application?
  std::vector<SkipNode*> forward;
  SkipNode(int k, int v, int level);
};

// The Skip List class proper
class SkipList : public Dictionary
{
public:
  SkipList(int max_level, float prob);
  ~SkipList();
  // methods of the data structure
  void insert(int search_key, int new_value);
  void remove(int search_key);
  SkipNode* search(int search_key);
  bool contains(int search_key);
  void check();
private:
  int max_level_;     // Maximum admissible level
  int level_;         // Actual level: highest level of any SkipNode
  float prob_;        // SkipNode level ratio
  SkipNode* header_;
  SkipNode* nil_;
  int random_level(); // Calculates level of a SkipNode.
};

#endif  // SkipList_H_
