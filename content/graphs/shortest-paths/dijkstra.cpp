/*
 *Author:* Antti Laaksonen
 *Description:* Computes shortest path in $O(V log (V + E) )$, does not allow negative weights
*/
struct Dijkstra {
  const ll INF = 1e18;
  int n;
  vector<ll> distance;

  Dijkstra(int n) : n(n) {
    distance.assign(n, INF);
  }

  Dijkstra(int start, vector<vector<pair<int, ll>>> &adj) : Dijkstra(adj.size()) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    vector<bool> processed(n, false);

    distance[start] = 0;
    q.push({0, start});
    while (!q.empty()) {
      int a = q.top().second;
      q.pop();
      if (processed[a])
        continue;
      processed[a] = true;
      for (auto u : adj[a]) {
        int b = u.first;
        ll w = u.second;
        if (distance[a] + w < distance[b]) {
          distance[b] = distance[a] + w;
          q.push({distance[b], b});
        }
      }
    }
  }
};