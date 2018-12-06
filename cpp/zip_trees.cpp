#include <iostream>
#include <cstdlib>
#include <limits>
#include <assert.h>
#include "zip_trees.h"

using namespace std;

ZipTree::ZipTree(float prob, bool frac, bool update_rank)
    : prob_(prob), frac_(frac), update_rank_(update_rank) {
    nullnode = new ZipNode;
    nullnode->left = nullnode->right = nullnode;
    root = nullnode;
}

void ZipTree::left_rot(ZipNode*& tree) {
    ZipNode *left = tree->left;
    tree->left = left->right;
    left->right = tree;
    tree = left;
}

void ZipTree::right_rot(ZipNode*& tree) {
    ZipNode *right = tree->right;
    tree->right = right->left;
    right->left = tree;
    tree = right;
}


void ZipTree::insert(int key, int value) {
    int rank = randomRank();
    ZipNode* x = new ZipNode;
    x->rank = rank;
    x->key = key;
    x->value = value;
    ZipNode* cur = root;
    ZipNode* prev;
    ZipNode* fix;

    // Find where to add x
    while ((cur != nullnode) && ((rank < cur->rank) or ((rank == cur->rank) && key > cur->key))) {
        prev = cur;
        cur = (key < cur->key) ? cur->left : cur->right;
    }

    // Either the tree was empty, so cur is root, and x becomes the new root
    // Otherwise, add x as child of prev (it replaces cur)
    if (cur == root) {
        root = x;
    } else if (key < prev->key) {
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
    if (key < cur->key) {
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
        if (cur->key < key) {
            // Traverse the right spine of cur until we hit the point where
            // we need to unzip a node
            do {
                prev = cur;
                cur = cur->right;
            } while ((cur != nullnode) && (cur->key < key));
        } else {
            do {
            // Traverse the left spine
                prev = cur;
                cur = cur->left;
            } while ((cur != nullnode) && (cur->key > key));
        }
        // Unzip the current node and transfer the path to the other side
        if ((fix->key > key) || ((fix == x) && (prev->key > key))) {
            fix->left = cur;
        } else {
            fix->right = cur;
        }
        // Continue the unzipping, starting from the current node in the
        // path, using as fix point the parent of cur (that just lost a child)
    }
}

void ZipTree::remove(int key) {
    ZipNode* cur = root;
    ZipNode* prev;

    // Find the node with key
    while (key != cur->key) {
        prev = cur;
        cur = (key < cur->key) ? cur->left : cur->right;
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
    if (root->key == key) {
        root = cur;
    } else if (key < prev->key) {
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

ZipNode* ZipTree::search(int key) {
    return search(root, key);
}

ZipNode* ZipTree::search(ZipNode*& leaf, int key) {
    if (leaf == nullnode) {
        return nullptr;
    }
    if (key == leaf->key) {
        if (update_rank_) {
            leaf->rank = max(leaf->rank, randomRank());
        }
        return leaf;
    }
    if (key < leaf->key) {
        ZipNode* ans =  search(leaf->left, key);
        if (update_rank_ && leaf->rank <= ans-> rank) {
            assert(leaf->left == ans);
            left_rot(leaf);
        }
        return ans;
    } else if (key > leaf->key) {
        ZipNode* ans =  search(leaf->right, key);
        if (update_rank_ && leaf->rank < ans-> rank) {
            assert(leaf->right == ans);
            right_rot(leaf);
        }
        return ans;
    } else { assert(false); }
}

void ZipTree::display() {
    display(root, 0);
}

void ZipTree::display(ZipNode*& leaf, int indent) {
    for (int i = 0; i < indent; i++) { printf(" "); }
    if (leaf != nullnode) {
        printf("(%d, %d)\n", leaf->key, leaf->rank);
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
    assert (min_bound < leaf->key);
    assert (max_bound > leaf->key);
    if (leaf->left != nullnode) {
        assert(leaf->rank > leaf->left->rank);
        check(leaf->left, min_bound, leaf->key);
    }
    if (leaf->right != nullnode) {
        assert(leaf->rank >= leaf->right->rank);
        check(leaf->right, leaf->key, max_bound);
    }
}

int ZipTree::randomRank() {
    int height = 1;
    while ((float) rand()/(float) RAND_MAX < prob_)
      height++;
    if (update_rank_) {
        height += ((double) rand() / (RAND_MAX));
    }
    return height;
}
