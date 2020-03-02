Counting triplets with red edges in each pair

Given a tree having N vertices and N-1 edges where each edges is having one of either red(r) or black(b) color. I need to find how many triplets(a,b,c) of vertices are there, such that on the path from vertex a to b, vertex b to c and vertex c to a there is atleast one edge having red color.

It should be noted that (a,b,c), (b,a,c) and all such permutation will be considered as the same triplets.

EXAMPLE : Let N=5 and edges with colors are as follow :

1 2 b
2 3 r
3 4 r
4 5 b
Here answer will be 4.

EXPLANATION : (2,3,4) is one such triplet because on all paths i.e 2 to 3, 3 to 4 and 2 to 4 there is atleast one edge having read color. (2,3,5), (1,3,4) and (1,3,5) are such other triplets.

Let's call triplets having your property good triplets, and those that don't bad. Let's count the bad triplets. Let {T1,T2,…,Tm}{T1,T2,…,Tm} be the maximal subtrees with all black edges, and suppose these trees have t1,t2,…,tmt1,t2,…,tm vertices, respectively. For each TiTi, the number of bad triplets with all three vertices among V(Ti)V(Ti) is (ti3)(ti3). The number of bad triplets having two vertices among V(Ti)V(Ti), and one vertex among the remaining vertices is (ti2)(N−ti)(ti2)(N−ti). All bad triplets are of one of these forms. So we have that the number of good triplets is:

(N3)−∑i=1tom((ti3)+(ti2)(N−ti))
(N3)−∑i=1tom((ti3)+(ti2)(N−ti))
=N(N−1)(N−2)6−∑i=1m(ti(ti−1)(ti−2)6+ti(ti−1)2(N−ti))
=N(N−1)(N−2)6−∑i=1m(ti(ti−1)(ti−2)6+ti(ti−1)2(N−ti))
=1/6*(N(N−1)(N−2)−∑i=1mti(ti−1)(3N−2ti−2))
=1/6*(N(N−1)(N−2)−∑i=1mti(ti−1)(3N−2ti−2))
