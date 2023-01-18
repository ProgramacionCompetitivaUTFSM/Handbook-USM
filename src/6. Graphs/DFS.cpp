void DFS(int u) {
  visited[u] = 1;
  for(int v : G[u]) {
    if(!visited[v]) {
      DFS(v);
    }
  }
}
