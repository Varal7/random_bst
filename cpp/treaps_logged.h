#ifndef TREAPS_LOGGED_H_
#define TREAPS_LOGGED_H_

#include "dictionary.h"
#include "treaps.h"
#include "mem_log.h"


class TreapLogged : public Treap
{
public:
    TreapLogged();
    bool insert(int key, int value);
    bool remove(int key);
    TreapNode* search(int key);
    // Bookkeeping functions
    uint32_t height();
    // And the memory usage log
    static MemLog *log_;
};

#endif
