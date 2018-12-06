#include "dictionary.h"

bool Dictionary::contains(int search_key) {
  return !(search(search_key) != nullptr);
}
