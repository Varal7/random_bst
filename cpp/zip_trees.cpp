#include <iostream>
#include <cstdlib>
#include <limits>
#include <assert.h>
#include "zip_trees.h"

using namespace std;

// TODO: call "delete" on deleted nodes

void ZipTree::insert(int elem) {
    int rank = randomRank();
    ZipNode* x = new ZipNode;
    x->rank = rank;
    x->elem = elem;
    ZipNode* cur = root;
    ZipNode* prev;
    ZipNode* fix;

    while ((cur != nullnode) && ((rank < cur->rank) or ((rank == cur->rank) && elem > cur->elem))) {
        prev = cur;
        cur = (elem < cur->elem) ? cur->left : cur->right;
    }

    if (cur == root) {
        root = x;
    } else if (elem < prev->elem) {
        prev->left = x;
    } else {
        prev->right = x;
    }

    if (cur == nullnode) {
        x->left = x->right = nullnode;
        return;
    }

    if (elem < cur->elem) {
        x->right = cur;
    } else {
        x->left = cur;
    }

    prev = x;

    while (cur != nullnode) {
        fix = prev;
        if (cur->elem < elem) {
            do {
                prev = cur;
                cur = cur->right;
            } while ((cur != nullnode) && (cur->elem <= elem));
        } else {
            do {
                prev = cur;
                cur = cur->left;
            } while ((cur != nullnode) && (cur->elem >= elem));
        }
        if ((fix->elem > elem) || ((fix == x) && (prev->elem > elem))) {
            fix->left = cur;
        } else {
            fix->right = cur;
        }
    }
}

void ZipTree::remove(int elem) {
    ZipNode* cur = root;
    ZipNode* prev;
    while (elem != cur->elem) {
        prev = cur;
        cur = (elem < cur->elem) ? cur->left : cur->right;
    }

    ZipNode* left = cur->left;
    ZipNode* right = cur->right;

    if (left == nullnode) {
        cur = right;
    } else if (right == nullnode) {
        cur = left;
    } else if (left->rank >= right->rank) {
        cur = left;
    } else {
        cur = right;
    }

    if (root->elem == elem) {
        root = cur;
    } else if (elem < prev->elem) {
        prev->left = cur;
    } else {
        prev->right = cur;
    }

    while ((left != nullnode) && (right != nullnode)) {
        if (left->rank >= right->rank) {
            do {
                prev = left;
                left = left->right;
            } while ((left != nullnode) && (left->rank >= right->rank));
            prev->right = right;
        } else {
            do {
                prev = right;
                right = right->left;
            } while ((right != nullnode) && (left->rank < right->rank));
            prev->left = left;
        }
    }
}

ZipNode* ZipTree::search(int elem) {
    return search(root, elem);
}

ZipNode* ZipTree::search(ZipNode*& leaf, int elem) {
    if (leaf == nullnode) {
        return nullnode;
    }
    if (elem == leaf->elem) { return leaf; }
    if (elem < leaf->elem) {
        return search(leaf->left, elem);
    }
    return search(leaf->right, elem);
}

void ZipTree::display() {
    display(root, 0);
}

void ZipTree::display(ZipNode*& leaf, int indent) {
    for (int i = 0; i < indent; i++) { printf(" "); }
    if (leaf != nullnode) {
        printf("(%d, %d)\n", leaf->elem, leaf->rank);
        display(leaf->left, indent + 1);
        display(leaf->right, indent + 1);
    } else {
        printf("null\n");
    }
}

void ZipTree::check() {
    check(root, numeric_limits<int>::min(), numeric_limits<int>::max());
}

void ZipTree::check(ZipNode*& leaf, int min_bound, int max_bound) {
    if (leaf == nullnode) { return; }
    assert (min_bound < leaf->elem);
    assert (max_bound > leaf->elem);
    if (leaf->left != nullnode) {
        assert(leaf->rank > leaf->left->rank);
        check(leaf->left, min_bound, leaf->elem);
    }
    if (leaf->right != nullnode) {
        assert(leaf->rank >= leaf->right->rank);
        check(leaf->right, leaf->elem, max_bound);
    }
}

int ZipTree::randomRank() {
    int height = 1;
    while (rand() % 2 == 0) {
        height += 1;
    }
    return height;
}

