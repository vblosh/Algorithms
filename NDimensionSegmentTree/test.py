from SegmentTree import SegmentTree

array = [x for x in range(10, 0, -1)]

tree = SegmentTree(lambda a,b: a + b)
tree.build(array)
s1 = tree.query(0, 3)
s2 = tree.query(0, 1)
tree.update(0, 10)
s3 = tree.query(0, 3)
s4 = tree.query(0, 1)


def merge(llist, rlist):
    ret = []
    lidx, ridx = 0, 0
    while(lidx < len(llist) and ridx < len(rlist)):
        if (llist[lidx] < rlist[ridx]):
            ret.append(llist[lidx])
            lidx += 1
        else:
            ret.append(rlist[ridx])
            ridx += 1

    while(lidx < len(llist)):
        ret.append(llist[lidx])
        lidx += 1

    while(ridx < len(rlist)):
        ret.append(rlist[ridx])
        ridx += 1

    return ret


arrTree = SegmentTree(merge, lambda x: [x])
arrTree.build(array)

end = 1
