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

    // Find where to add x
    while ((cur != nullnode) && ((rank < cur->rank) or ((rank == cur->rank) && elem > cur->elem))) {
        prev = cur;
        cur = (elem < cur->elem) ? cur->left : cur->right;
    }

    // Either the tree was empty, so cur is root, and x becomes the new root
    // Otherwise, add x as child of prev (it replaces cur)
    if (cur == root) {
        root = x;
    } else if (elem < prev->elem) {
        prev->left = x;
    } else {
        prev->right = x;
    }

    // x is now a leaf, no merge to be done
    if (cur == nullnode) {
        x->left = x->right = nullnode;
        return;
    }

    // otherwise, add back cur as a child of x
    if (elem < cur->elem) {
        x->right = cur;
    } else {
        x->left = cur;
    }

    // The acutal unzipping
    prev = x; // The unzipping starts with x (who misses a child)

    while (cur != nullnode) {
        // `fix` holds the node to which the unzipping will continue
        // adding nodes
        fix = prev;
        if (cur->elem < elem) {
            // Traverse the right spine of cur until we hit the point where
            // we need to unzip a node
            do {
                prev = cur;
                cur = cur->right;
            } while ((cur != nullnode) && (cur->elem < elem));
        } else {
            do {
            // Traverse the left spine
                prev = cur;
                cur = cur->left;
            } while ((cur != nullnode) && (cur->elem > elem));
        }
        // Unzip the current node and transfer the path to the other side
        if ((fix->elem > elem) || ((fix == x) && (prev->elem > elem))) {
            fix->left = cur;
        } else {
            fix->right = cur;
        }
        // Continue the unzipping, starting from the current node in the
        // path, using as fix point the parent of cur (that just lost a child)
    }
}

void ZipTree::remove(int elem) {
    ZipNode* cur = root;
    ZipNode* prev;

    // Find the node with elem
    while (elem != cur->elem) {
        prev = cur;
        cur = (elem < cur->elem) ? cur->left : cur->right;
        // TODO: raise error when not found
    }

    ZipNode* left = cur->left;
    ZipNode* right = cur->right;

    // Delete the node
    delete cur;

    // Choose the child with higher rank
    if (left == nullnode) {
        cur = right;
    } else if (right == nullnode) {
        cur = left;
    } else if (left->rank >= right->rank) {
        cur = left;
    } else {
        cur = right;
    }

    // Replace the deleted node with that child
    if (root->elem == elem) {
        root = cur;
    } else if (elem < prev->elem) {
        prev->left = cur;
    } else {
        prev->right = cur;
    }

    // The actual zipping
    while ((left != nullnode) && (right != nullnode)) {
        // The if block and the else block will run alternatively;
        // which one is first depends on which child has been added
        if (left->rank >= right->rank) {
            do {
                // Traverse the right spine of left until we find where
                // to zip in right
                prev = left;
                left = left->right;
            } while ((left != nullnode) && (left->rank >= right->rank));
            prev->right = right; // Zip in right
        } else {
            do {
                // Traverse left spine of current node
                prev = right;
                right = right->left;
            } while ((right != nullnode) && (left->rank < right->rank));
            prev->left = left; // Zip in left
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
    while ((float) rand()/(float) RAND_MAX < prob_)
      height++;
    return height;
}

bool ZipTree::contains(int elem) {
    return (search(elem) != nullnode);
}
