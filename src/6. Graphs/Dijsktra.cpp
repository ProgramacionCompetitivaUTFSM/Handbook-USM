void Dijsktra(int a) {
  D[a] = 0;
  priority_queue< pii, vpii, greater<pi>> PQ;
  PQ.push(pi(0, a));
  while(!PQ.empty()) {
    int u = PQ.top().second;
    int d = PQ.top().first;
    if(d > D[u]) continue;
    // only in case that final node exists
    if(u == f) continue 
    for(pi next : G[u]) {
      int v = next.first;
      int w = next.second;
      if(D[v] > D[u] + w) {
        D[v] = D[u] + w;
        PQ.push(pi(D[v], v));
      }
    }
  }
}
