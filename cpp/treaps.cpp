#include <iostream>
#include <cstdlib>
#include <limits>
#include <assert.h>
#include "treaps.h"

using namespace std;

Treap::Treap() {
    root = nullptr;
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


bool Treap::insert(int key, int value) { return insert(root, key, value); }
bool Treap::remove(int key) { return remove(root, key); }

bool Treap::insert(TreapNode*& leaf, int key, int value) {
    if (leaf == nullptr) {
        leaf = new TreapNode;
        leaf->left = leaf->right = nullptr;
        leaf->key = key;
        leaf->value = value;
        leaf->priority = rand();
        return true;
    }
    if (key == leaf->key) {
        leaf->value = value;  // Update value if already in treap
        return false;
    } else if (key < leaf->key) {
        insert(leaf->left, key, value);
        if (leaf->left->priority > leaf->priority) { left_rot(leaf); }
    } else {
        insert(leaf->right, key, value);
        if (leaf->right->priority > leaf->priority) { right_rot(leaf); }
    }
    return true;
}

bool Treap::remove(TreapNode*& leaf, int key) {
    if (leaf == nullptr) { return false; }
    if (key == leaf->key) { return remove(leaf); }
    else if (key < leaf->key) { return remove(leaf->left, key); }
    else { return remove(leaf->right, key); }
}

bool Treap::remove(TreapNode*& leaf) {
    if (leaf->left == nullptr && leaf->right == nullptr) {
        delete leaf;
        leaf = nullptr;
    } else if (leaf->left == nullptr) {
        TreapNode *tmp = leaf;
        leaf = leaf->right;
        delete tmp;
    } else if (leaf->right == nullptr) {
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
    return true;
}

TreapNode* Treap::search(int key) {
    return search(root, key);
}

TreapNode* Treap::search(TreapNode*& leaf, int key) {
    if (leaf == nullptr) {
        return nullptr;
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
    if (leaf != nullptr) {
        printf("(%d, %d)\n", leaf->key, leaf->priority);
        display(leaf->left, indent + 1);
        display(leaf->right, indent + 1);
    } else {
        printf("null\n");
    }
}

void Treap::check() {
    check(root, numeric_limits<int>::min(), numeric_limits<int>::max());
}

void Treap::check(TreapNode*& leaf, int min_bound, int max_bound) {
    if (leaf == nullptr) { return; }
    assert (min_bound < leaf->key);
    assert (max_bound > leaf->key);
    if (leaf->left != nullptr) {
        assert(leaf->priority > leaf->left->priority);
        check(leaf->left, min_bound, leaf->key);
    }
    if (leaf->right != nullptr) {
        assert(leaf->priority > leaf->right->priority);
        check(leaf->right, leaf->key, max_bound);
    }
}

int Treap::height() {
    return height(root);
}


int Treap::height(TreapNode*& leaf) {
    if (leaf == nullptr) { return 0; }
    return 1 + max(height(leaf->left), height(leaf->right));
}

void Treap::clear() {
    clear(root);
    root = nullptr;
}

void Treap::clear(TreapNode*& leaf) {
    if (leaf == nullptr) {
        return;
    }
    clear(leaf->left);
    clear(leaf->right);
    delete leaf;
}

