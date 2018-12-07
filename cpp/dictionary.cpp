#include "dictionary.h"

bool Dictionary::contains(int search_key) {
  Item *result = search(search_key);
  return (result != nullptr && result->key == search_key);
}


void Dictionary::emplace(int search_key, int new_value) {
  insert(search_key, new_value);
}


void Dictionary::erase(int search_key) {
  remove(search_key);
}


Item* Dictionary::find(int search_key) {
  return search(search_key);
}
