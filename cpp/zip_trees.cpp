#include <iostream>
#include <cstdlib>
#include <limits>
#include <assert.h>
#include "zip_trees.h"
#include <math.h>

using namespace std;

ZipTree::ZipTree(float prob, bool update_rank, bool frac_rank, bool find_before_insert)
    : prob_(prob), update_rank_(update_rank), frac_rank_(frac_rank), find_before_insert_(find_before_insert) {
    root = nullptr;
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

bool ZipTree::insert(int key, int value) {
    if (find_before_insert_) {
        ZipNode* ans = search(key);
        if (ans != nullptr) {
            ans->value = value;
            return false;
        }
    }
    return insert_(key, value);
}

bool ZipTree::insert_(int key, int value) {
    int rank = randomRank();
    ZipNode* x = new ZipNode;
    x->rank = rank;
    x->key = key;
    x->value = value;
    ZipNode* cur = root;
    ZipNode* prev;
    ZipNode* fix;

    // Find where to add x
    while ((cur != nullptr) && ((rank < cur->rank) or ((rank == cur->rank) && key > cur->key))) {
        prev = cur;
        cur = (key < cur->key) ? cur->left : cur->right;
    }

    // Either the tree was empty, so cur is root, and x becomes the new root
    // Otherwise, the rank of x is larger than rank of cur, so we should add x as child of cur
    // add x as child of prev (it replaces cur)
    if (cur == root) {
        root = x;
    } else if (key < prev->key) {
        prev->left = x;
    } else { // key >= prev->key
        prev->right = x;
    }

    // x is now a leaf, no merge to be done
    if (cur == nullptr) {
        x->left = x->right = nullptr;
        return true;
    }

    // otherwise, add back cur as a child of x
    if (key < cur->key) {
        x->right = cur;
    } else {
        x->left = cur;
    }

    // The actual unzipping
    prev = x; // The unzipping starts with x (who misses a child)

    while (cur != nullptr) {
        // `fix` holds the node to which the unzipping will continue
        // adding nodes
        fix = prev;
        if (cur->key < key) {
            // Traverse the right spine of cur until we hit the point where
            // we need to unzip a node
            while ((cur != nullptr) && (cur->key < key)) {
                prev = cur;
                cur = cur->right;
            }
        } else {
            // Traverse the left spine
            while ((cur != nullptr) && (cur->key > key)) {
                prev = cur;
                cur = cur->left;
            }
        }

        // If we hit a point where the current node has same key, we can finish unzipping
        // by assigning the children of cur to where they belong
        if ((cur != nullptr) && (cur->key == key)) {
            if (prev->right == cur) {
                printf("needs zipping. aborting\n"); //TODO
                assert(false);
                fix->right = cur->right;
                delete cur;
            } else if (prev->left == cur) {
                printf("needs zipping. aborting\n"); //TODO
                assert(false);
                fix->left = cur->left;
                delete cur;
            } else { assert(false);}
            return false;
        }
        // Unzip the current node and transfer the path to the other side
        if ((fix->key > key) || ((fix == x) && (prev->key > key))) {
            fix->left = cur;
        } else if ((fix->key < key) || ((fix == x) && (prev->key < key))) {
            fix->right = cur;
        } else { // fix->key = key
            assert(false);
        }
        // Continue the unzipping, starting from the current node in the
        // path, using as fix point the parent of cur (that just lost a child)
    }
    return true;
}

bool ZipTree::remove(int key) {
    ZipNode* cand = root;
    ZipNode* prev;

    // Find the node with key
    while (key != cand->key) {
        prev = cand;
        cand = (key < cand->key) ? cand->left : cand->right;
        // TODO: raise error when not found
    }

    ZipNode* left = cand->left;
    ZipNode* right = cand->right;
    ZipNode* cur;


    // Choose the child with higher rank
    if (left == nullptr) {
        cur = right;
    } else if (right == nullptr) {
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

    // Delete the node
    delete cand;

    // The actual zipping
    while ((left != nullptr) && (right != nullptr)) {
        // The if block and the else block will run alternatively;
        // which one is first depends on which child has been added
        if (left->rank >= right->rank) {
            do {
                // Traverse the right spine of left until we find where
                // to zip in right
                prev = left;
                left = left->right;
            } while ((left != nullptr) && (left->rank >= right->rank));
            prev->right = right; // Zip in right
        } else {
            do {
                // Traverse left spine of current node
                prev = right;
                right = right->left;
            } while ((right != nullptr) && (left->rank < right->rank));
            prev->left = left; // Zip in left
        }
    }
    // TODO: handle case where node is not found.
    return true;
}

ZipNode* ZipTree::search(int key) {
    return search(root, key);
}

ZipNode* ZipTree::search(ZipNode*& leaf, int key) {
    if (leaf == nullptr) {
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
        if (update_rank_ && (ans != nullptr) && (leaf->rank <= ans->rank)) {
            assert(leaf->left == ans);
            left_rot(leaf);
        }
        return ans;
    } else if (key > leaf->key) {
        ZipNode* ans =  search(leaf->right, key);
        if (update_rank_ && (ans != nullptr) && (leaf->rank < ans->rank)) {
            assert(leaf->right == ans);
            right_rot(leaf);
        }
        return ans;
    } else { assert(false); }
}

int ZipTree::height() {
    return height(root);
}


int ZipTree::height(ZipNode*& leaf) {
    if (leaf == nullptr) { return 0; }
    return 1 + max(height(leaf->left), height(leaf->right));
}

int ZipTree::count_nodes() {
    return count_nodes(root);
}


int ZipTree::count_nodes(ZipNode*& leaf) {
    if (leaf == nullptr) { return 0; }
    return 1 + count_nodes(leaf->left) +  count_nodes(leaf->right);
}


int ZipTree::sum_depths(ZipNode*& leaf, int depth) {
    int left_depths = 0;
    int right_depths = 0;
    if (leaf->left != nullptr) {
        left_depths = sum_depths(leaf->left, depth + 1);
    }
    if (leaf->right != nullptr) {
        right_depths = sum_depths(leaf->right, depth + 1);
    }
    return depth + left_depths + right_depths;
}

int ZipTree::sum_depths() {
    if (root == nullptr) {
        return 0;
    }
    return sum_depths(root, 0);
}

double ZipTree::potential() {
    return potential(root).second;
}

pair<int, double> ZipTree::potential(ZipNode*& leaf) {
    if (leaf == nullptr) { return make_pair(0, 0); }
    pair<int, double> left = potential(leaf->left);
    pair<int, double> right = potential(leaf->right);
    int count = 1 + left.first + right.first;
    double pot = log2(double(count) + left.second + right.second);
    return make_pair(count, pot);
}



void ZipTree::display() {
    display(root, 0);
}

void ZipTree::display(ZipNode*& leaf, int indent) {
    for (int i = 0; i < indent; i++) { printf(" "); }
    if (leaf != nullptr) {
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
    if (leaf == nullptr) { return; }
    assert (min_bound < leaf->key);
    assert (max_bound > leaf->key);
    if (leaf->left != nullptr) {
        assert(leaf->rank > leaf->left->rank);
        check(leaf->left, min_bound, leaf->key);
    }
    if (leaf->right != nullptr) {
        assert(leaf->rank >= leaf->right->rank);
        check(leaf->right, leaf->key, max_bound);
    }
}

int ZipTree::randomRank() {
    if (frac_rank_) {
        return rand();
    }
    int height = 1;
    while ((float) rand()/(float) RAND_MAX < prob_)
      height++;
    return height;
}


void ZipTree::clear() {
    clear(root);
    root = nullptr;
}

void ZipTree::clear(ZipNode*& leaf) {
    if (leaf == nullptr) {
        return;
    }
    clear(leaf->left);
    clear(leaf->right);
    delete leaf;
}

void ZipTree::flatten() {
    if (root != nullptr) {
        flatten(root);
    }
    cout << "\n";
}

void ZipTree::flatten(ZipNode*& leaf) {
    if (leaf->left != nullptr) {
        flatten(leaf->left);
    }
    printf("(%d, %d)\t", leaf->key, leaf->rank);
    if (leaf->right != nullptr) {
        flatten(leaf->right);
    }
}
