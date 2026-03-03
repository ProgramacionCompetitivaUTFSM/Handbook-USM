/*
 *Description:* Planar graph of a Delaunay Triangulation with greedy walk and locate. `walk` finds nearest site. `locate` finds all equidistant nearest sites via BFS: 1 site $=$ Voronoi region, 2 $=$ edge, 3+ $=$ vertex (cocircular).
 *Time:* Build $O(n log n)$ | Walk $O(sqrt(n))$ expected | Locate $O(sqrt(n))$ expected
 *Status:* Tested
 *Dependencies:* point2d, delaunay
 */
template <typename T> struct delaunay_graph : delaunay<T> {
  vector<vector<int>> adj;
  delaunay_graph() {}
  delaunay_graph(vector<T> &px, vector<T> &py) { build(px, py); }
  void build(vector<T> &px, vector<T> &py) {
    delaunay<T>::build(px, py);
    adj.assign(this->n, {});
    for (auto &t : this->tri)
      for (int i = 0; i < 3; i++) for (int j = i+1; j < 3; j++) {
        adj[t[i]].push_back(t[j]); adj[t[j]].push_back(t[i]);
      }
    for (auto &v : adj) { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); }
  }
  int walk(vector<T> &px, vector<T> &py, T qx, T qy) const {
    auto d2 = [&](int i) { return (qx-px[i])*(qx-px[i]) + (qy-py[i])*(qy-py[i]); };
    int cur = 0; T best = d2(0);
    for (bool ok = true; ok; ) { ok = false;
      for (int nb : adj[cur]) { T d = d2(nb); if (d < best) { best=d; cur=nb; ok=true; break; } }
    }
    return cur;
  }
  vector<int> locate(vector<T> &px, vector<T> &py, T qx, T qy) const {
    auto d2 = [&](int i) { return (qx-px[i])*(qx-px[i]) + (qy-py[i])*(qy-py[i]); };
    int v = walk(px, py, qx, qy);
    T best = d2(v);
    vector<int> res = {v};
    vector<bool> vis(this->n, false);
    vis[v] = true;
    for (int qi = 0; qi < (int)res.size(); qi++)
      for (int nb : adj[res[qi]])
        if (!vis[nb]) { vis[nb] = true; if (d2(nb) == best) res.push_back(nb); }
    sort(res.begin(), res.end());
    return res;
  }
};