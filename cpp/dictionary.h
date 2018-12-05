#ifndef DICTIONARY_H_
#define DICTIONARY_H_

struct Item
{
  int key;
  int value;
};

class Dictionary
{
public:
  virtual void insert(int search_key, int new_value) =0;
  virtual void remove(int search_key) =0;
  virtual Item* search(int search_key) =0;
  virtual bool contains(int search_key) =0;
  virtual void check() =0;
  virtual ~Dictionary() { };
};

#endif
