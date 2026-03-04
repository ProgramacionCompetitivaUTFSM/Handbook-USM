/*
 *Description:* Finds an Eulerian trail/circuit in a directed graph using Hierholzer's algorithm. Handles self-loops and parallel edges.
 - A trail exists iff all vertices satisfy outdeg = indeg (circuit), or exactly one has outdeg - indeg = 1 (start) and one has indeg - outdeg = 1 (end), and the edge-set is weakly connected.
 - `vertices`: vertex sequence of size $m+1$.
 - `edges`: edge index sequence of size $m$.
 *Complexity:* $O(V + E)$
 *Status:* Tested on https://judge.yosupo.jp/problem/eulerian_trail_directed
*/
struct directed_euler_trail {
  ll n, m = 0;
  vector<vector<ll>> adj;
  vector<pair<ll, ll>> E;
  vector<ll> indeg, outdeg, vertices, edges;
  directed_euler_trail(ll n) : n(n), adj(n), indeg(n), outdeg(n) {}
  void add_edge(ll u, ll v) {
    adj[u].push_back(m);
    E.push_back({u, v});
    outdeg[u]++, indeg[v]++, m++;
  }
  ll find_start() {
    ll s = -1, cp = 0, cm = 0;
    for (ll v = 0; v < n; v++) {
      ll d = outdeg[v] - indeg[v];
      if (d == 1) cp++, s = v;
      else if (d == -1) cm++;
      else if (d != 0) return -2;
      if (outdeg[v] > 0 && s < 0) s = v;
    }
    if (cp == 0 && cm == 0) return s;
    return (cp == 1 && cm == 1) ? s : -2;
  }
  bool solve() {
    if (m == 0) { vertices = {0}; return true; }
    ll s = find_start();
    if (s == -2) return false;
    vector<ll> ep(n);
    edges.resize(m);
    ll pp = 0, pq = m, v = s;
    while (pp < pq) {
      if (ep[v] >= (ll)adj[v].size()) {
        if (pp == 0)
          return false;
        edges[--pq] = edges[--pp];
        v = E[edges[pq]].first;
      } else {
        ll e = adj[v][ep[v]++];
        edges[pp++] = e;
        v = E[e].second;
      }
    }
    vertices = {s};
    for (ll e : edges) vertices.push_back(E[e].second);
    return true;
  }
};
