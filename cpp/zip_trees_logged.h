#ifndef ZIP_TREES_LOGGED_H_
#define ZIP_TREES_LOGGED_H_

#include "dictionary.h"
#include "zip_trees.h"
#include "mem_log.h"


class ZipTreeLogged : public ZipTree
{
public:
    ZipTreeLogged(float prob=0.5, bool update_rank_on_access=false, bool use_frac_rank=false);
    bool insert(int key, int value);
    bool remove(int key);
    ZipNode* search(int key);
    // Bookkeeping functions
    //uint32_t height();
    // And the memory usage log
    static MemLog *log_;
};

#endif
