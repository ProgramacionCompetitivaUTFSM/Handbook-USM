/*
 *Description:* All shortest path, runs on $O(V^3)$
 *Status:* Tested
*/

// Create distance matrix
for (int i = 1; i <= n; i++) {
  for (int j = 1; j <= n; j++) {
    if (i == j) distance[i][j] = 0;
    else if (adj[i][j]) distance[i][j] = adj[i][j];
    else distance[i][j] = INF;
  }
}

// Floyd-Warshall
for (int k = 1; k <= n; k++) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      distance[i][j] = min(distance[i][j], distance[i][k]+distance[k][j]);
    }
  }
}
