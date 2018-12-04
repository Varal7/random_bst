struct Item;
{
  int key;
  int value;
};

class Dictionary
{
public:
  void insert(int search_key, int new_value);
  void remove(int search_key);
  Item* search(int search_key);
  bool contains(int search_key);
};
