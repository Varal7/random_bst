#ifndef DICTIONARY_H_
#define DICTIONARY_H_

struct Item
{
  int key;
  int value;
  //Item();
  //Item(const Item &obj);
  virtual ~Item() {};
};

class Dictionary
{
public:
  virtual bool insert(int search_key, int new_value) =0;
  virtual bool remove(int search_key) =0;
  virtual Item* search(int search_key) =0;
  bool contains(int search_key);
  virtual void display();
  virtual void check() =0;
  virtual void clear() =0;
  virtual int height() =0;
  virtual int count_nodes();
  virtual int sum_depths();
  virtual double potential();
  virtual ~Dictionary() {};
  void emplace(int search_key, int new_value);
  void erase(int search_key);
  Item* find(int search_key);
};

#endif
