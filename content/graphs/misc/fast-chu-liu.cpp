/*
 *Description:* Minimum spanning arborescence (directed MST), optimized Edmonds/Chu-Liu algorithm
  using lazy skew heaps Complexity:* $O(E \log V)$,
  returns \{-1, \{\}\} if not reachable
*Status:* Tested
 */
template <class T> struct fast_chu_liu {
  struct edge {
    int u, v;
    T len;
  };
  struct node {
    edge key;
    node *l = nullptr, *r = nullptr;
    T delta = 0;
    node(edge e) : key(e) {}
    void prop() {
      key.len += delta;
      if (l) l->delta += delta;
      if (r) r->delta += delta;
      delta = 0;
    }
    edge top() {
      prop();
      return key;
    }
  };
  int n;
  vector<edge> e;
  fast_chu_liu(int n) : n(n) {}
  void add_edge(int x, int y, T w) { e.push_back({x, y, w}); }
  node *merge(node *a, node *b) {
    if (!a || !b)
      return a ? a : b;
    a->prop(), b->prop();
    if (a->key.len > b->key.len)
      swap(a, b);
    swap(a->l, (a->r = merge(b, a->r)));
    return a;
  }
  void pop(node *&a) {
    a->prop();
    a = merge(a->l, a->r);
  }
  pair<T, vector<int>> solve(int root) {
    union_find_rb uf(n);
    vector<node *> heap(n, nullptr);
    for (edge &ed : e)
      heap[ed.v] = merge(heap[ed.v], new node(ed));
    T ans = 0;
    vector<int> seen(n, -1), path(n), par(n);
    seen[root] = root;
    vector<edge> Q(n), in(n, {-1, -1, 0});
    deque<tuple<int, int, vector<edge>>> cycs;
    for (int s = 0; s < n; s++) {
      int u = s, qi = 0, w;
      while (seen[u] < 0) {
        if (!heap[u])
          return {-1, {}};
        edge ed = heap[u]->top();
        heap[u]->delta -= ed.len, pop(heap[u]);
        Q[qi] = ed, path[qi++] = u, seen[u] = s;
        ans += ed.len, u = uf.findSet(ed.u);
        if (seen[u] == s) {
          node *cyc = nullptr;
          int end = qi, t = (int)uf.ops.size();
          do
            cyc = merge(cyc, heap[w = path[--qi]]);
          while (uf.unionSet(u, w));
          u = uf.findSet(u), heap[u] = cyc, seen[u] = -1;
          cycs.push_front({u, t, {&Q[qi], &Q[end]}});
        }
      }
      for (int i = 0; i < qi; i++)
        in[uf.findSet(Q[i].v)] = Q[i];
    }
    for (auto &[u, t, comp] : cycs) {
      while ((int)uf.ops.size() > t)
        uf.rb();
      edge inEdge = in[u];
      for (auto &ed : comp)
        in[uf.findSet(ed.v)] = ed;
      in[uf.findSet(inEdge.v)] = inEdge;
    }
    for (int i = 0; i < n; i++)
      par[i] = in[i].u;
    return {ans, par};
  }
};
