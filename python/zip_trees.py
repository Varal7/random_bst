""" Zip tree Implementation in Python
"""
import os
from random import Random

# TODO: Remove self.parent

class _ZipNode:
    """Zip Node"""
    def __init__(self, elem, rank,
                 parent=None, left=None, right=None):
        self.elem = elem
        self.rank = rank
        self.parent = parent
        self.left = left
        self.right = right

    def __repr__(self):
        return str((self.elem, self.rank))

class ZipTree:
    """
    ZipTree
    """
    def __init__(self, seed=0):
        self.random = Random(seed)
        self.root = None

    def insert(self, elem):
        rank = self.randomRank()
        x = _ZipNode(elem, rank)
        cur = self.root

        while cur is not None and (rank < cur.rank or (rank == cur.rank and elem > cur.elem)):
            prev = cur
            cur = cur.left if elem < cur.elem else cur.right

        if cur is self.root:
            self.root = x
        elif elem < prev.elem:
            prev.left = x
        else:
            prev.right = x

        if cur is None:
            x.left = x.right = None
            return

        if elem < cur.elem:
            x.right = cur
        else:
            x.left = cur

        prev = x

        while cur is not None:
            fix = prev
            if cur.elem < elem:
                done = False
                while not done:
                    prev = cur
                    cur = cur.right
                    if cur is None or cur.elem > elem:
                        done = True
            else:
                done = False
                while not done:
                    prev = cur
                    cur = cur.left
                    if cur is None or cur.elem < elem:
                        done = True

            if fix.elem > elem or (fix == x and prev.elem > elem):
                fix.left = cur
            else:
                fix.right = cur

    def delete(self, elem):
        cur = self.root

        while elem != cur.elem:
            prev = cur
            cur = cur.left if elem < cur.elem else cur.right

        left = cur.left
        right = cur.right

        if left is None:
            cur = right
        elif right is None:
            cur = left
        elif left.rank >= right.rank:
            cur = left
        else:
            cur = right

        if self.root.elem == elem:
            self.root = cur
        elif elem < prev.elem:
            prev.left = cur
        else:
            prev.right = cur

        while left is not None and right is not None:
            if left.rank >= right.rank:
                done = False
                while not done:
                    prev = left
                    left = left.right
                    if left is None or left.rank < right.rank:
                        done = True
                prev.right = right
            else:
                done = False
                while not done:
                    prev = right
                    right = right.left
                    if right is None or left.rank >= right.rank:
                        done = True
                prev.left = left


    def randomRank(self):
        height = 1
        while self.random.randint(1, 2) != 1:
            height += 1
        return height

    def _find_node(self, elem, node, parent=None):
        while True:
            if node is None or elem == node.elem:
                return node, parent
            elif elem < node.elem:
                node, parent = node.left, node
            else:
                node, parent = node.right, node


    def __contains__(self, elem):
        """Return True iff elem is found in tree, else False."""
        node = self._find_node(elem, self.root)[0]
        return node is not None


    def check(self):
        """Check zip tree invariants."""
        nodes = [(self.root, None, None)]
        while nodes:
            node, min_bound, max_bound = nodes.pop()
            if node:
                if min_bound: assert min_bound < node.elem
                if max_bound: assert node.elem < max_bound
                if node.left:
                    assert node.elem > node.left.elem
                    assert node.rank > node.left.rank
                if node.right:
                    assert node.elem < node.right.elem
                    assert node.rank >= node.right.rank
                if node.parent:
                    parent = node.parent
                    assert parent.left == node or parent.right == node
                nodes.append((node.left, min_bound, node.elem))
                nodes.append((node.right, node.elem, max_bound))

    def __repr__(self):
        """Return a string representation of treap."""
        lines = []
        nodes = [(self.root, 0)]
        while nodes:
            node, indent = nodes.pop()
            name = str(node) if node else 'None'
            lines.append(' ' * indent + name)
            if node:
                nodes.append((node.right, indent + 1))
                nodes.append((node.left, indent + 1))
        return os.linesep.join(lines)
