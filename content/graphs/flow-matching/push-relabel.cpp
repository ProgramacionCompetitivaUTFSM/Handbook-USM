/*
 *Author:* Abner Vidal
 *Description:* Flow algorithm with complexity  $O (|E| dot |V|^2)$
 *Status:* Tested on CSES
*/
template<class T>
struct push_relabel {
  struct edge {int to,rev; T f,c;};
  vector<edge> g; vector<vector<int>> adj;
  vector<int> h,pt; vector<T> e; queue<int> q;
  push_relabel(int n) : adj(n), h(n,0), e(n,0), pt(n,0) {}
  void add_edge(int u, int v, T cap){
    int cur =  g.size();
    adj[u].push_back(cur); g.push_back({v,cur+1,0,cap});
    adj[v].push_back(cur+1); g.push_back({u,cur,0,0});
  }
  void push(int u, int ev) {
    auto [v,rev,fl,cap] = g[ev];
    T d = min(e[u],cap-fl);
    g[ev].f += d; g[rev].f -= d;
    e[u] -= d; e[v] += d;
    if (d != 0 && e[v] == d) q.push(v);
  }
  void relabel(int u) {
    int d = INT_MAX;
    for (int to : adj[u]) {
      int v = g[to].to; T cap = g[to].c, fl = g[to].f;
      if (cap-fl > 0) d = min(d,h[v]);
    }
    if (d < INT_MAX) h[u] = d+1;
  }
  void discharge(int u) {
    while (e[u] > 0) {
      if (pt[u] < (int)adj[u].size()) {
        auto [v,rev,fl,cap] = g[adj[u][pt[u]]]; 
        if (cap-fl > 0 && h[u] > h[v]) push(u,adj[u][pt[u]]);
        else pt[u]++;
      } else {
        relabel(u); pt[u] = 0;
      }
    }
  }
  T max_flow(int s, int t){
    h[s] = (int)adj.size(); e[s] = numeric_limits<T>::max();
    for (int to : adj[s]) push(s,to);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (u != s && u != t)
      discharge(u);
    }
    T ans = 0;
    for (int to : adj[t]) ans += g[g[to].rev].f;
    return ans;
  }
};