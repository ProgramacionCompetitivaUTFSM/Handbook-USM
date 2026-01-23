/*
 *Description:* Solve k-shortest path problem
 *Status:* Tested on josupo.jp and CSES
*/
struct Eppstein {
  #define x first
  #define y second
  using T = ll; const T INF = 1e15;
  using Edge = pair<int, T>;
  struct Node { int E[2] = {}, s{0};  Edge x;  };
  T shortest;
  priority_queue<pair<T, int>> Q;
  vector<Node> P{1}; vector<int> h;
  Eppstein(vector<vector<Edge>>& G, int s, int t) {
    int n = G.size(); 
    vector<vector<Edge>> H(n);
    for(int i = 0; i < n; i++) 
      for (Edge &e : G[i]) 
        H[e.x].push_back({i, e.y});
    vector<int> ord, par(n, -1); 
    vector<T> d(n, -INF);
    Q.push({d[t] = 0, t});
    while (!Q.empty()) {
      auto v = Q.top(); Q.pop();
      if (d[v.y] == v.x) {
        ord.push_back(v.y);
        for (Edge &e : H[v.y]) 
          if (v.x-e.y > d[e.x]) {
            Q.push({d[e.x] = v.x-e.y, e.x});
            par[e.x] = v.y;
          }
      }
    }
    if ((shortest = -d[s]) >= INF) return;
    h.resize(n);
    for (int v : ord) {
      int p = par[v];
      if (p+1) h[v] = h[p];
      for (Edge &e : G[v])
        if (d[e.x] > -INF) {
          T k = e.y - d[e.x] + d[v];
          if (k or e.x != p) h[v] = push(h[v], {e.x, k});
          else p = -1;
        }
    }
    P[0].x.x = s; 
    Q.push({0, 0});
  }
  int push(int t, Edge x) {
    P.push_back(P[t]);
    if (!P[t = int(P.size())-1].s or P[t].x.y >= x.y)
      swap(x, P[t].x);
    if (P[t].s) {
      int i = P[t].E[0], j = P[t].E[1];
      int d = P[i].s > P[j].s;
      int k = push(d ? j : i, x);
      P[t].E[d] = k;
    }
    P[t].s++;
    return t;
  }
  int nextPath() {
    if (Q.empty()) return -1;
    auto v = Q.top(); Q.pop();
    for (int i : P[v.y].E) if (i)
        Q.push({ v.x-P[i].x.y+P[v.y].x.y, i });
    int t = h[P[v.y].x.x];
    if (t) Q.push({ v.x - P[t].x.y, t });
    return shortest - v.x;
  }
};