from rtreelib import RTree, Rect, RStarTree
from rtreelib.util.diagram import create_rtree_diagram
import random


# Create an RTree instance with some sample data
t = RStarTree()

if __name__ == "__main__":

    qntRet = int(input("Rectangle Numbers: "))

    for i in range(qntRet):
        min_x = random.randint(0, 10)
        min_y = random.randint(0, 10)
        width = random.randint(1, 5)
        height = random.randint(1, 5)

        t.insert("Ret" + str(i + 1), Rect(min_x, min_y, min_x + width, min_y + height))

# Create a diagram of the R-tree structure
create_rtree_diagram(t)
