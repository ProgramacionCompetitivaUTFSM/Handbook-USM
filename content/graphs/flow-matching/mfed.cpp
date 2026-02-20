/*
 *Description:* Max flow but with lowerbound of flow for each edge. To check is a feasible solution, all edges of super-sink (N) node should be saturated
 *Status:* Tested
*/
const ll inf = 1e15;
template<typename MF>
struct max_flow_edge_demands : MF {
  vector<ll> in, out, dem;
  vector<array<int,2>> eloc;
  int N;
  max_flow_edge_demands(int N): MF(N+2), N(N), in(N, 0), out(N, 0) {}
  void add_edge(int u, int v, ll cap, ll d = 0) {
    eloc.push_back({u, (int)MF::G[u].size()});
    dem.push_back(d);
    MF::add_edge(u, v, cap - d);
    out[u] += d; in[v] += d;
  }
  bool feasible() {
    ll total = 0;
    for (int i = 0; i < N; i++) {
      if (in[i])  MF::add_edge(N, i, in[i]),  total += in[i];
      if (out[i]) MF::add_edge(i, N+1, out[i]);
    }
    return MF::max_flow(N, N+1) == total;
  }
  ll flow(int e) {
    auto &[u, idx] = eloc[e];
    return dem[e] + MF::G[u][idx].f;
  }
  int size() { return eloc.size(); }
};
