void BellmanFord(int s) {
  // remember to assign INF in vector D
  D[s] = 0;
  bool flag = false;
  for(int i = 0; i < n; i++) {
    for(int a = 0; a < n; a++) {
      for(pi e : G[a]) {
        b = e.first;
        w = e.second;
        // this is to check negative cycle
        if(i == n - 1) flag = (D[b] > D[a] + w ? true : false); 
        else D[b] = min(D[b], D[a] + w);
      }
    }
  }
}
