import zip_trees
import imp
imp.reload(zip_trees)


z = zip_trees.ZipTree()

z.insert(1)
z.insert(2)
z.insert(3)
z.insert(4)
z.insert(5)
z.insert(6)
z.insert(7)

z.delete(4)
z.delete(5)


z.check()

