/*
 *Author:* Pablo Messina
 *Source:* https://github.com/PabloMessina/Competitive-Programming-Material
 *Description:* Flow algorithm with complexity  $O (|E| dot |V|^2)$
 *Status:* Not tested
*/
struct Dinic {
  struct Edge { ll to, rev; ll f, c; };
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
  void add_edge(ll u, ll v, ll cap) {
    G[u].push_back({v, (ll)G[v].size(), 0, cap});
    G[v].push_back({u, (ll)G[u].size() - 1, 0, 0}); // Use cap instead of 0 if bidirectional
  }
  ll max_flow(ll s, ll t) {
    t_ = t; ll ans = 0;
    while (bfs(s, t)) while (ll dl = dfs(s, LLONG_MAX)) ans += dl;
    return ans;
  }
};