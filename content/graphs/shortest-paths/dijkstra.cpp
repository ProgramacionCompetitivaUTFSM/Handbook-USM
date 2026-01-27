/*
 *Author:* Antti Laaksonen
 *Description:* Computes shortest path in $O(V log (V + E) )$, does not allow negative weights
*/
for (int i = 1; i <= n; i++) distance[i] = INF;
distance[x] = 0;
q.push({0,x});
while (!q.empty()) {
  int a = q.top().second; q.pop();
  if (processed[a]) continue;
  processed[a] = true;
  for (auto u : adj[a]) {
    int b = u.first, w = u.second;
    if (distance[a]+w < distance[b]) {
      distance[b] = distance[a]+w;
      q.push({-distance[b],b});
    }
  }
}