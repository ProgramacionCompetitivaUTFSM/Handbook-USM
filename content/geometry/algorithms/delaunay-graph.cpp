/*
 *Description:* Planar graph of a Delaunay Triangulation with greedy walk. Walk finds nearest site by the empty-circle property.
 *Time:* Build $O(n log n)$ expected | Walk $O(sqrt(n))$ expected
 *Status:* Tested
 *Dependencies:* point3d, convex_hull_3d, delaunay
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
        adj[t[i]].push_back(t[j]);
        adj[t[j]].push_back(t[i]);
      }
    for (auto &v : adj) {
      sort(v.begin(), v.end());
      v.erase(unique(v.begin(), v.end()), v.end());
    }
  }

  int walk(vector<T> &px, vector<T> &py, T qx, T qy) const {
    auto d2 = [&](int i) { return (qx-px[i])*(qx-px[i]) + (qy-py[i])*(qy-py[i]); };
    int cur = 0; T best = d2(0);
    for (bool ok = true; ok; ) {
      ok = false;
      for (int nb : adj[cur]) {
        T d = d2(nb);
        if (d < best) { best = d; cur = nb; ok = true; break; }
      }
    }
    return cur;
  }
};