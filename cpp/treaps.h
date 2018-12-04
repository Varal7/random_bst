#ifndef TREAPS_H
#define TREAPS_H

struct Node
{
    int elem, priority;
    Node *left, *right;
};



class Treap {
public:
    void insert(int elem);
    void remove(int elem);
    void display();
    Node* search(int elem);
    void check();

    Treap() {
        nullnode = new Node;
        nullnode->left = nullnode->right = nullnode;
        root = nullnode;
    }
private:
    Node *root, *nullnode;
    void insert(Node*& leaf, int elem);
    void remove(Node*& leaf, int elem);
    void remove(Node*& leaf);
    void left_rot(Node*& leaf);
    void right_rot(Node*& leaf);
    Node* search(Node*& leaf, int elem);
    void display(Node*& leaf, int indent);
    void check(Node*& leaf, int, int);
};

#endif
