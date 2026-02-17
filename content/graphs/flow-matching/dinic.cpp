/*
*Author:* Pablo Messina
*Source:* https://github.com/PabloMessina/Competitive-Programming-Material
*Description:* Flow algorithm with complexity  $O (|E| dot |V|^2)$
*Status:* Not tested
*/
template<class T>
struct Dinic {
  struct Edge { int to, rev; T f, c; bool r; };
  ll n, t_; vector<vector<Edge>> G;
  vector<ll> D, q, W;
  bool bfs(ll s, ll t) {
    W.assign(n, 0); D.assign(n, -1); D[s] = 0;
    ll f = 0, l = 0; q[l++] = s;
    while (f < l) {
      ll u = q[f++];
      for (const Edge &e : G[u]) if (D[e.to] == -1 && e.f < e.c)
      D[e.to] = D[u] + 1, q[l++] = e.to;
    }
    return D[t] != -1;
  }
  ll dfs(ll u, ll f) {
    if (u == t_) return f;
    for (ll &i = W[u]; i < (ll)G[u].size(); ++i) {
      Edge &e = G[u][i]; ll v = e.to;
      if (e.c <= e.f || D[v] != D[u] + 1) continue;
      ll df = dfs(v, min(f, e.c - e.f));
      if (df > 0) { e.f += df, G[v][e.rev].f -= df; return df; }
    }
    return 0;
  }
  Dinic(ll N) : n(N), G(N), D(N), q(N) {}
  void add_edge(int u, int v, T cap) {
    G[u].push_back({v, (int)G[v].size(), 0, cap,0});
    G[v].push_back({u, (int)G[u].size()-1, 0, 0,1}); // Use cap instead of 0 if bidirectional
  }
  ll max_flow(ll s, ll t) {
    t_ = t; ll ans = 0;
    while (bfs(s, t)) while (ll dl = dfs(s, numeric_limits<T>::max())) ans += dl;
    return ans;
  }
};