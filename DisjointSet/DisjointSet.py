class DisjointSet:
    """ implement Disjoint Set """
    def __init__(self):
        self.__parent = {}
        self.__size = {}

    def make_set(self, v):
        self.__parent[v] = v
        self.__size[v] = 1

    def find_set(self, v):
        if(v == self.__parent[v]):
            return v
        else:
            self.__parent[v] = self.find_set(self.__parent[v])
            return self.__parent[v]
    
    def size(self, v):
        return self.__size[self.find_set(v)]

    def union_set(self, a, b):
        a = self.find_set(a)
        b = self.find_set(b)
        if( a != b):
            if( self.__size[a] < self.__size[b]):
                self.__parent[a] = b
                self.__size[b] += self.__size[a]
            else:
                self.__parent[b] = a
                self.__size[a] += self.__size[b]

