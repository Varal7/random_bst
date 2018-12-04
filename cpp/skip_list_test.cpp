/*
A very primitive test suite for the skip_list class. To compile, run
$ g++ skip_list_test.cpp skip_list.cpp
*/

#include <iostream>
#include "skip_list.h"

int main()
{
  node *n = new node(1, 10, 4);
  std::cout << "Node level is " << n->level << ".\n";

  skip_list *list = new skip_list(16, 0.5);
  std::cout << "INT_MIN is " << INT_MAX << ".\n";


  //std::cout << list->header_->value << std::endl;
  //std::cout << list->header_->key << std::endl;
  node* nil_ptr = list->search(INT_MAX);

  if (nil_ptr == nullptr)
    std::cout << "Pointer is null." << std::endl;
  else
    std::cout << "Header value is " << nil_ptr->value << std::endl;

    std::cout << "Here are some random levels: "
    << list->random_level() << " "
    << list->random_level() << " "
    << list->random_level() << " "
    << list->random_level() << " "
    << list->random_level() << " "
    << list->random_level() << " "
    << list->random_level() << " "
    << list->random_level() << " "
    << list->random_level() << " "
    << list->random_level() << " "
    << list->random_level() << " "
    << list->random_level() << " "
    << list->random_level() << " "
    << list->random_level() << " "
    << list->random_level() << ". Does that distribution look right?"
    << std::endl;

  list->insert(2, 20);
  list->insert(4, 40);
  list->insert(3, 30);
  list->insert(1, 10);
  list->insert(5, 50);

  std::cout << "Value at key 3 is " << list->search(3)->value << std::endl;
  std::cout << "Value at key 2 is " << list->search(2)->value << std::endl;
  std::cout << "Value at key 4 is " << list->search(4)->value << std::endl;
  std::cout << "Value at key 1 is " << list->search(1)->value << std::endl;
  std::cout << "Value at key 5 is " << list->search(5)->value << std::endl;

  std::cout << "Level at key 3 is " << list->search(3)->level << std::endl;
  std::cout << "Level at key 2 is " << list->search(2)->level << std::endl;
  std::cout << "Level at key 4 is " << list->search(4)->level << std::endl;
  std::cout << "Level at key 1 is " << list->search(1)->level << std::endl;
  std::cout << "Level at key 5 is " << list->search(5)->level << std::endl;

  // Insert some new values
  list->insert(4, 400);
  list->insert(3, 300);
  list->insert(5, 500);
  list->insert(2, 200);
  list->insert(1, 100);

  std::cout << "Ok, now some values have been changed." << std::endl;
  std::cout << "Value at key 1 is " << list->search(1)->value << std::endl;
  std::cout << "Value at key 2 is " << list->search(2)->value << std::endl;
  std::cout << "Value at key 3 is " << list->search(3)->value << std::endl;
  std::cout << "Value at key 4 is " << list->search(4)->value << std::endl;
  std::cout << "Value at key 5 is " << list->search(5)->value << std::endl;

  // Delete some stuff
  list->del(3);
  std::cout << "Ok, now some stuff has been deleted." << std::endl;
  //std::cout << "Level at key 3 is " << list->search(3)->level << std::endl;
  std::cout << "Level at key 2 is " << list->search(2)->level << std::endl;
  std::cout << "Level at key 4 is " << list->search(4)->level << std::endl;
  std::cout << "Level at key 1 is " << list->search(1)->level << std::endl;
  std::cout << "Level at key 5 is " << list->search(5)->level << std::endl;

  delete n;
  delete list;
}
