void BFS(int a) {
  queue<int> Q;
  D[a] = 0;
  Q.push(a);
  while(!Q.empty()) {
    int u = Q.front();
    Q.pop();
    for(int v : G[u]) {
      if(D[v] > D[u] + 1) {
        D[v] = D[u] + 1;
        Q.push(v);
      }
    }
  }
}
