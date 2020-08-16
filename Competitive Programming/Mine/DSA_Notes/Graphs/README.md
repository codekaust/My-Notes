# Graph Data Structure
Notes made from: [1](https://www.youtube.com/watch?v=gXgEDyodOJU&list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P&index=38), [2](https://www.youtube.com/watch?v=1n5XPFcvxds&list=PLqM7alHXFySEaZgcg7uRYJFBnYMLti-nh&t=18s)

Graph is a non-linear data structure where there are >=1 number of nodes connected using edges with no specific rule. Tree is a special graph with exactly *n-1 edges* and unique paths from root to every other node.

Formally, graph G is an ordered pair of a set V [vertices] and a set E [edges].

> **G = (V, E)** where V, E are sets.

Note: (...) represent ordered elements [like array], {...} represent unordered set.

So above G = (V, E) was ordered. V = {v1, v2, v3, v4} is ordered (order doesn't matter).  

E = Set of edges of following types **Directed Edges:** e.g. (v1, v2) v1 to v2., **Undirected Edges:** e.g. {v1, v2} or {v2, v1} i.e. link between v1 and v2.

Now, what are **directed and undirected graphs**? -> Ones having directed edges, undirected edges respectively.

Weighted and Unweighted: Are edges labeled with some kind of weight?

# Properties of Graphs

Self-loop, multi-edge!

Directed graph with no-self loop and multi-edge has max `n*(n-1)` edges. Undirected has half of it. Dense is too many edges [adjacency matrix used to store], sparse has few edges [adjacency list used to store].

1. **Walk / Path** in a graph is a *sequence* of vertices where each adjacent pair is connected by an edge. If the graph is directed, the edges must align.

2. **Simple Path** is a walk in which no vertices (thus no edges) repeat. **NOTE: *PATH* USUALLY REFERS TO SIMPLE PATH UNLESS STATED EXPLICITLY**. There will always be a simple path between two nodes between which a walk exists.

3. **Trail** is a walk in which edges aren't repeated, though vertices may.
---
1. **Connected Graphs**: Undirected graph where there is path between every two nodes.
Same property in directed graph -> **Strongly Connected**. If directed graph not strongly connected but can be converted to a connected graph by treating all its edges as undirected -> **Weakly Connected**.