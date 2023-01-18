void BellmanFord(int s) {
  D[s] = 0;
  for(int i = 0; i < n - 1; i++) {
    for(auto e : edges) {
      int a, b, w;
      a = e.a;
      b = e.b;
      w = e.w;
      D[b] = min(D[b], D[a] + w);
    }
  }
  // to check negative cycle
  bool flag = false;
  for(auto e : edges) {
    int a, b, w;
    a = e.a;
    b = e.b;
    w = e.w;
    int old = D[b];
    D[b] = min(D[b], D[a] + w);
    if(old > D[b]) {
      flag = true;
      break;
    }
  }
}
