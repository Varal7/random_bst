#include <iostream>
#include <cstdlib>
#include <limits>
#include <assert.h>

using namespace std;

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


void Treap::left_rot(Node*& tree) {
    Node *left = tree->left;
    tree->left = left->right;
    left->right = tree;
    tree = left;
}

void Treap::right_rot(Node*& tree) {
    Node *right = tree->right;
    tree->right = right->left;
    right->left = tree;
    tree = right;
}


void Treap::insert(int elem) { insert(root, elem); }
void Treap::remove(int elem) { remove(root, elem); }

void Treap::insert(Node*& leaf, int elem) {
    if (leaf == nullnode) {
        leaf = new Node;
        leaf->left = leaf->right = nullnode;
        leaf->elem = elem;
        leaf->priority = rand();
        return;
    }
    if (elem == leaf->elem) {
        return;  // Not adding duplicates
    }
    if (elem < leaf->elem) {
        insert(leaf->left, elem);
        if (leaf->left->priority > leaf->priority) { left_rot(leaf); }
    } else {
        insert(leaf->right, elem);
        if (leaf->right->priority > leaf->priority) { right_rot(leaf); }
    }
}

void Treap::remove(Node*& leaf, int elem) {
    if (leaf == nullnode) { return; }
    if (elem == leaf->elem) { remove(leaf); }
    else if (elem < leaf->elem) { remove(leaf->left, elem); }
    else { remove(leaf->right, elem); }
}

void Treap::remove(Node*& leaf) {
    if (leaf->left == nullnode && leaf->right == nullnode) {
        delete leaf;
        leaf = nullnode;
    } else if (leaf->left == nullnode) {
        Node *tmp = leaf;
        leaf = leaf->right;
        delete tmp;
    } else if (leaf->right == nullnode) {
        Node *tmp = leaf;
        leaf = leaf->left;
        delete tmp;
    } else {
        if (leaf->left->priority > leaf->right->priority) {
            left_rot(leaf);
            remove(leaf->right);
        } else {
            right_rot(leaf);
            remove(leaf->left);
        }
    }
}

Node* Treap::search(int elem) {
    return search(root, elem);
}

Node* Treap::search(Node*& leaf, int elem) {
    if (leaf == nullnode) {
        return nullnode;
    }
    if (elem == leaf->elem) {
        return leaf;
    }
    if (elem < leaf->elem) {
        return search(leaf->left, elem);
    }
    return search(leaf->right, elem);
}

void Treap::display() {
    display(root, 0);
}

void Treap::display(Node*& leaf, int indent) {
    for (int i = 0; i < indent; i++) { printf(" "); }
    if (leaf != nullnode) {
        printf("(%d, %d)\n", leaf->elem, leaf->priority);
        display(leaf->left, indent + 1);
        display(leaf->right, indent + 1);
    } else {
        printf("null\n");
    }
}

void Treap::check() {
    check(root, numeric_limits<int>::min(), numeric_limits<int>::max());
}

void Treap::check(Node*& leaf, int min_bound, int max_bound) {
    if (leaf == nullnode) { return; }
    assert (min_bound < leaf->elem);
    assert (max_bound > leaf->elem);
    assert (max_bound > leaf->elem);
    if (leaf->left != nullnode) {
        assert(leaf->priority > leaf->left->priority);
        check(leaf->left, min_bound, leaf->elem);
    }
    if (leaf->right != nullnode) {
        assert(leaf->priority > leaf->right->priority);
        check(leaf->right, leaf->elem, max_bound);
    }
}


int main() {
    srand(time(0));
    Treap t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.check();
    t.display();
    printf("\n");

    t.remove(2);
    t.display();
    t.check();
}
