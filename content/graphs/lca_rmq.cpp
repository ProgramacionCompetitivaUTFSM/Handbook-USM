/*
 *Description:* Computes lowest common ancestor, precomputed in $O(V log V)$, $O(1)$ per query. Rooted in 0
*/
struct lca_rmq {
  using pll = pair<ll, ll>;
  vector<vector<int>> T;
  vector<pll> linear;
  vector<int> in, out, depth;
  ll t = 0, n;
  static pll _min(pll a, pll b) { return min(a, b); }
  sparse_table<pll, lca_rmq::_min> st;
  lca_rmq(vector<vector<int>> &T): n(T.size()) {
    in = out = depth = vector<int>(n, -1);
    linear.resize(2*n);
    auto dfs = [&](int u, int d, auto&&dfs) -> void {
      linear[t] = {d, u}, in[u] = t++, depth[u] = d;
      for (int v : T[u]) {
        if (in[v] != -1) continue;
        dfs(v, d+1, dfs);
        linear[t++] = {d, u};
      }
      out[u] = t;
    };
    dfs(0, 0, dfs);
    st = sparse_table<pll, lca_rmq::_min>(linear);
  }
  ll query(int u, int v) {
    tie(u, v) = {in[u], in[v]};
    return st.query(min(u, v), max(u, v)).second;
  }
};
