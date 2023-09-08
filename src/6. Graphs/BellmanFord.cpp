struct Edge { int from, to, weight; };
struct BellmanFord {
  int n, last_updated = -1; const int INF = 1e18;
  vector<int> p, dist;
  BellmanFord(vector<Edge> &G, int s) {
    n = G.size(); dist.assign(n+2, INF);
    p.assign(n+2, -1); dist[s] = 0;
    for (int i = 1; i <= n; i++) {
      last_updated = -1;
      for (Edge &e : G)
        if (dist[e.from] + e.weight < dist[e.to]) {
          dist[e.to] = dist[e.from] + e.weight;
          p[e.to] = e.from; last_updated = e.to;
        }
    }
  }
  bool getCycle(vector<int> &cycle) {
    if (last_updated == -1) return false;
    for (int i = 0; i < n-1; i++)
      last_updated = p[last_updated];
    for (int x = last_updated ;; x=p[x]) {
      cycle.push_back(x);
      if (x == last_updated and cycle.size() > 1) break;
    }
    reverse(cycle.begin(), cycle.end());
    return true;
  }
};
