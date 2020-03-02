from DisjointSet import DisjointSet

def KruskalMST(NV, E):
    """ Kruskal's algorithm is a minimum-spanning-tree algorithm which finds an edge of the least possible weight that connects any two trees in the forest.
    It is a greedy algorithm in graph theory as it finds a minimum spanning tree for a connected weighted graph adding increasing cost arcs at each step.
    This means it finds a subset of the edges that forms a tree that includes every vertex, where the total weight of all the edges in the tree is minimized. 
    If the graph is not connected, then it finds a minimum spanning forest (a minimum spanning tree for each connected component). 
    Algorithm
    1 create a graph F (a set of trees), where each vertex in the graph is a separate tree
    2 create a set S containing all the edges in the graph
    3 while S is nonempty and F is not yet spanning
        3.1 remove an edge with minimum weight from S
        3.2 if the removed edge connects two different trees then add it to the forest F, combining two trees into a single tree
    At the termination of the algorithm, the forest forms a minimum spanning forest of the graph. 
    If the graph is connected, the forest has a single component and forms a minimum spanning tree
    """ 
    #A = ?
    A = []
    V = DisjointSet()
    # foreach v ? G.V:    MAKE-SET(v)
    for i in range(1, NV+1):
        V.make_set(i)
    # foreach (u, v) in G.E ordered by weight(u, v), increasing:
    #   if FIND-SET(u) ? FIND-SET(v):
    #       A = A ? {(u, v)}
    #       UNION(u, v)
    E.sort(key = lambda edge: edge[2])
    for edge in E:
        if V.find_set(edge[0]) != V.find_set(edge[1]):
            A.append(edge)
            V.union_set(edge[0], edge[1])
    # return A
    return A