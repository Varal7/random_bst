#ifndef ZIP_TREES_H
#define ZIP_TREES_H

struct ZipNode
{
    int elem, rank;
    ZipNode *left, *right;
};

class ZipTree {
public:
    void insert(int elem);
    void remove(int elem);
    void display();
    ZipNode* search(int elem);
    bool contains(int elem);
    void check();

    ZipTree() {
        nullnode = new ZipNode;
        nullnode->left = nullnode->right = nullnode;
        root = nullnode;
    }

private:
    ZipNode *root, *nullnode;
    int randomRank();
    ZipNode* search(ZipNode*& leaf, int elem);
    void display(ZipNode*& leaf, int indent);
    void check(ZipNode*& leaf, int, int);
};

#endif

