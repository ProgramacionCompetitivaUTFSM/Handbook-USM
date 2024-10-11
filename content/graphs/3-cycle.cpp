/*
 *Description:* Given a simple undirected graph with n nodes and m edges with no self loops or multiple edges find the number of 4 length cycles.
  Two cycles are different if their edge collections are different. Runs on $O(m sqrt(m))$ where $m$ is the number of edges.
 *Status:* Tested on Codeforces
*/
ll count_cycle_4(const vector<vector<ll>>& g) {
  ll n = g.size(), w = 0;
  vector<ll> val(n, 0), deg(n);
  vector<vector<ll>> G(n);

  for (ll i = 0; i < n; i++) deg[i] = g[i].size();
  for (ll i = 0; i < n; i++) {
    for (auto e : g[i]) {
      if (e < i) continue;
      if (deg[i] <= deg[e]) G[i].push_back(e);
      else G[e].push_back(i);
    }
  }
  for (ll i = 0; i < n; i++) {
    for (auto u : g[i]) {
      for (auto v : G[u]) {
        if (deg[v] > deg[i] || (deg[v] == deg[i] && v > i))
          w += val[v]++;
      }
    }
    for (auto u : g[i]) {
      for (auto v : G[u]) {
        val[v] = 0;
      }
    }
  }
  return w;
}