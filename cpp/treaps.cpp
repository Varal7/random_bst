#include <iostream>
#include <cstdlib>
#include <limits>
#include <assert.h>
#include "treaps.h"

using namespace std;

Treap::Treap() {
    nullnode = new TreapNode;
    nullnode->left = nullnode->right = nullnode;
    root = nullnode;
}

void Treap::left_rot(TreapNode*& tree) {
    TreapNode *left = tree->left;
    tree->left = left->right;
    left->right = tree;
    tree = left;
}

void Treap::right_rot(TreapNode*& tree) {
    TreapNode *right = tree->right;
    tree->right = right->left;
    right->left = tree;
    tree = right;
}


void Treap::insert(int key, int value) { insert(root, key, value); }
void Treap::remove(int key) { remove(root, key); }

void Treap::insert(TreapNode*& leaf, int key, int value) {
    if (leaf == nullnode) {
        leaf = new TreapNode;
        leaf->left = leaf->right = nullnode;
        leaf->key = key;
        leaf->value = value;
        leaf->priority = rand();
        return;
    }
    if (key == leaf->key) {
        leaf->value = value;  // Update value if already in treap
    } else if (key < leaf->key) {
        insert(leaf->left, key, value);
        if (leaf->left->priority > leaf->priority) { left_rot(leaf); }
    } else {
        insert(leaf->right, key, value);
        if (leaf->right->priority > leaf->priority) { right_rot(leaf); }
    }
}

void Treap::remove(TreapNode*& leaf, int key) {
    if (leaf == nullnode) { return; }
    if (key == leaf->key) { remove(leaf); }
    else if (key < leaf->key) { remove(leaf->left, key); }
    else { remove(leaf->right, key); }
}

void Treap::remove(TreapNode*& leaf) {
    if (leaf->left == nullnode && leaf->right == nullnode) {
        delete leaf;
        leaf = nullnode;
    } else if (leaf->left == nullnode) {
        TreapNode *tmp = leaf;
        leaf = leaf->right;
        delete tmp;
    } else if (leaf->right == nullnode) {
        TreapNode *tmp = leaf;
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

TreapNode* Treap::search(int key) {
    return search(root, key);
}

TreapNode* Treap::search(TreapNode*& leaf, int key) {
    if (leaf == nullnode) {
        return nullnode;
    }
    if (key == leaf->key) {
        return leaf;
    }
    if (key < leaf->key) {
        return search(leaf->left, key);
    }
    return search(leaf->right, key);
}

void Treap::display() {
    display(root, 0);
}

void Treap::display(TreapNode*& leaf, int indent) {
    for (int i = 0; i < indent; i++) { printf(" "); }
    if (leaf != nullnode) {
        printf("(%d, %d)\n", leaf->key, leaf->priority);
        display(leaf->left, indent + 1);
        display(leaf->right, indent + 1);
    } else {
        printf("null\n");
    }
}

bool Treap::contains(int key) {
    return (search(key) != nullnode);
}

void Treap::check() {
    check(root, numeric_limits<int>::min(), numeric_limits<int>::max());
}

void Treap::check(TreapNode*& leaf, int min_bound, int max_bound) {
    if (leaf == nullnode) { return; }
    assert (min_bound < leaf->key);
    assert (max_bound > leaf->key);
    if (leaf->left != nullnode) {
        assert(leaf->priority > leaf->left->priority);
        check(leaf->left, min_bound, leaf->key);
    }
    if (leaf->right != nullnode) {
        assert(leaf->priority > leaf->right->priority);
        check(leaf->right, leaf->key, max_bound);
    }
}
