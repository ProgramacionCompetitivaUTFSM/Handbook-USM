/*
 *Description:* Max flow but with lowerbound of flow for each edge. To check is a feasible solution, all edges of super-sink (N) node should be saturated
 *Status:* Tested
*/
const ll inf = 1e15;
struct max_flow_edge_demands {
  Dinic mf;
  vector<ll> in, out;
  ll N;
  max_flow_edge_demands(ll N): N(N), mf(N+2), in(N), out(N) {}
  void add_edge(ll u, ll v, ll cap, ll dem = 0) {
    mf.add_edge(u, v, cap - dem);
    out[u] += dem, in[v] += dem;
  }
  ll max_flow(ll s, ll t) {
    mf.add_edge(t, s, inf);
    for (ll i = 0; i < N; i++) {
      mf.add_edge(N, i, in[i]);
      mf.add_edge(i, N+1, out[i]);
    }
    return mf.max_flow(N, N+1);
  }
};