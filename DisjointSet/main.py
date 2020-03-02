import sys
sys.stdin = open('input.txt', 'r')
#sys.stdout = open('output.txt', 'w')
from Kruskal import KruskalMST

#input Graph G=(V, E)
line = input()
NV, NE = tuple(map(lambda x : int(x), line.split(' ')))

E = []
for i in range(NE):
    line = input()
    edge = tuple(map(lambda x : int(x), line.split(' '))) # edge[0] - first vertex, edge[1] - second vertex, edge[3] - weight
    if edge[0] > NV or edge[1] > NV or edge[2] < 0:
        raise 'Wrong input'
    E.append(edge)

"""print('Input graph')
for edge in E: 
    print('{0}-{1}:{2}'.format(edge[0], edge[1], edge[2]))
"""
dotfile = open('graph.gv', 'w')
dotfile.write('graph {\n')
for i in range(1, NV+1):
    dotfile.write('{0} [pos="{1},{2}"];\n'.format(i, (i-1) // 2 * 100, i % 2 * 100))
for edge in E: 
    dotfile.write('{0}--{1} [label="{2}"];\n'.format(edge[0], edge[1], edge[2]))

MST = KruskalMST(NV, E)

"""print('Minimum spanning tree')
sum = 0
for edge in MST: 
    print('{0}-{1}:{2}'.format(edge[0], edge[1], edge[2]))
    sum += edge[2]
print('MST Total={}'.format(sum))
"""
sum = 0
for edge in MST: 
    dotfile.write('{0}--{1} [color=blue];\n'.format(edge[0], edge[1]))
    sum += edge[2]
dotfile.write('graph [label="Sum={0}"]\n'.format(sum))

''' Travelling Salesman Problem (Approximate using MST) '''
# build AdjacencyList graph
class Node:
    """helper structure for the SegmentTree """
    def __init__(self):
        self.Visited = False
        self.AdjacencyList = []

N = [Node() for i in range(NV + 1)] #index from 1, visited and AdjacencyList for each node
for edge in MST:
    N[edge[0]].AdjacencyList.append(edge[1])
    N[edge[1]].AdjacencyList.append(edge[0])

def PreorderDFS(N, node, Result):
    Result.append(node)
    N[node].Visited = True
    for edge in N[node].AdjacencyList:
        if(not N[edge].Visited):
            PreorderDFS(N, edge, Result)

def TSPApproximation(N):
    Result = []
    PreorderDFS(N, 1, Result)
    Result.append(1)
    return Result

''' List vertices visited in preorder walk of the constructed MST and add 1 at the end. '''
TSPSolution = TSPApproximation(N)

"""print('Travelling Salesman Problem (Approximate using MST)')
print(TSPSolution) """
for i in range(len(TSPSolution)-1): 
    dotfile.write('{0}--{1} [color=red];\n'.format(TSPSolution[i], TSPSolution[i+1]))
dotfile.write('}\n')
dotfile.close()