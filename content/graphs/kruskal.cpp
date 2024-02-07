/*
 *Description:* Minimum spanning tree in $O(E log E)$
 *Status:* Tested, but needs to be re-written
*/struct Edge {
  int a; int b; int w;
  Edge(int a_, int b_, int w_) : a(a_), b(b_), w(w_) {}
}
bool c_edge(Edge &a, Edge &b) { return a.w < b.w;  }
int Kruskal() {
  int n = G.size();
  UnionFind sets(n);
  vector< Edge > edges;
  for(int i = 0; i < n; i++) {
    for(pi eg : G[i]) {
      // node i to node eg.first with cost eg.second
      Edge e(i, eg.first, eg.second);
      edges.push_back(e);
    }
  }
  sort(edges.begin(), edges.end(), c_edge);
  int min_cost = 0;
  for(Edge e : Edges) {
    if(sets.find(e.a, e.b) != true) {
      tree.push_back(Edge(e.a, e.b, e.w));
      min_cost += e.w;
      sets.union(e.a, e.b);
    }
  }
  return min_cost;
}