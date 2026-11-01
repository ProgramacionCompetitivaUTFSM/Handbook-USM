/*
 *Author:* Antti Laaksonen
 *Description:* Computes shortest path in $O(E log (V) )$, does not allow negative weights
 *Status:* Tested on CSES
*/
struct dijkstra {
  const ll INF = 1e18; vector<ll> distance;
  dijkstra(int start, vector<vector<pair<int, ll>>> &adj) : distance(adj.size(), INF) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    distance[start] = 0;
    q.push({0, start});
    while (!q.empty()) {
      auto [d, a] = q.top(); q.pop();
      if (d != distance[a]) continue;
      for (auto [b, w] : adj[a])
        if (d + w < distance[b])
          distance[b] = d + w, q.push({distance[b], b});
    }
  }
};