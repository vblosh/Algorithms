""" SegmentTree for sum of elements implementation """
class Node:
    """helper structure for the SegmentTree """
    left = None
    right = None
    tree_el = None


class SegmentTree:
    """segment tree is a tree data structure for storing intervals, or segments 
        Conbine is the fuction that is used to combine elements
        For instance for sum tree Combine is lambda a,b : a+b 
    """
    def __init__(self, combine_func, assign_func = lambda x : x):
        """
        combine_func is used to combine to tree element together,
	    for instance for sum of array elements tree combine_func is [](int a, int b) { return a+b; },
	    for min of array elements tree combine_func is [](int a, int b) { return __min(a, b); }
	    for max of array elements tree combine_func is [](int a, int b) { return __max(a, b); }
	     
	    assign_func is used to assign an array element to an tree element,
	    default implementation returns array element and can be used then 
	    tree element type is the same as array element type
        """
        self.__root = Node()
        self.__size = 0
        self.__combine = combine_func
        self.__assign = assign_func

    def build(self, array):
        """ build a segment tree from array """
        self.__size = len(array)
        self.__do_build(array, self.__root, 0, self.__size - 1)

    def query(self, left, right):
        """ query tree element for array elements from left to rigth indexes inclusive """
        return self.__do_query(self.__root, 0, self.__size - 1, left, right)

    def update(self, position, new_value):
        """ update tree according new_value of array element in position """
        self.__do_update(self.__root, 0, self.__size - 1, position, new_value)

    def __do_build(self, array, node, left_idx, right_idx):
        if left_idx == right_idx:
            node.tree_el = self.__assign(array[left_idx])
        else:
            middle = (left_idx + right_idx) // 2
            node.left = Node()
            self.__do_build(array, node.left, left_idx, middle)
            node.right = Node()
            self.__do_build(array, node.right, middle + 1, right_idx)
            node.tree_el = self.__combine(node.left.tree_el, node.right.tree_el)

    def __do_query(self, node, left_idx, right_idx, left, right):
        if  left_idx == left and right_idx == right:
            return node.tree_el
        else:
            middle = (left_idx + right_idx) // 2
            if(left <= min(right, middle) and max(left, middle + 1) <= right):
                ltree_el = self.__do_query(node.left, left_idx, middle, left, min(right, middle))
                rtree_el = self.__do_query(node.left, middle + 1, right_idx, max(left, middle + 1), right)
                return self.__combine(ltree_el, rtree_el)
            elif (left <= min(right, middle)):
                return self.__do_query(node.left, left_idx, middle, left, min(right, middle))
            return self.__do_query(node.right, middle + 1, right_idx, max(left, middle + 1), right)

    def __do_update(self, node, left_idx, right_idx, position, new_value):
        if left_idx == right_idx:
            node.tree_el = new_value
        else:
            middle = (left_idx + right_idx) // 2
            if position <= middle:
                self.__do_update(node.left, left_idx, middle, position, new_value)
            else:
                self.__do_update(node.right, middle + 1, right_idx, position, new_value)
            node.tree_el = self.__combine(node.left.tree_el, node.right.tree_el)
