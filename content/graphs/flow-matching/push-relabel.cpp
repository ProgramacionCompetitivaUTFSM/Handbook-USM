/*
 *Author:* Abner Vidal
 *Description:* Flow algorithm with complexity  $O (|E| dot |V|^2)$
 *Status:* Tested on CSES
*/
template<class T>
struct push_relabel {
  struct Edge {int to,rev; T f,c; bool r; };
  vector<vector<Edge>> G;
  vector<int> h,pt; vector<T> e; queue<int> q;
  push_relabel(int n) : G(n), h(n,0), e(n,0), pt(n,0) {}
  void add_edge(int u, int v, T cap){
    G[u].push_back({v,(int)G[v].size(),0,cap,0});
    G[v].push_back({u,(int)G[u].size()-1,0,0,1});
  }
  void push(int u, int ev) {
    auto [v,rev,fl,cap,r] = G[u][ev];
    T d = min(e[u],cap-fl);
    G[u][ev].f += d; G[v][rev].f -= d;
    e[u] -= d; e[v] += d;
    if (d != 0 && e[v] == d) q.push(v);
  }
  void relabel(int u) {
    int d = INT_MAX;
    for (auto &eg : G[u]) 
    if (eg.c-eg.f > 0) d = min(d,h[eg.to]);
    if (d < INT_MAX) h[u] = d+1;
  }
  void discharge(int u) {
    while (e[u] > 0) {
      if (pt[u] < (int)G[u].size()) {
        auto [v,rev,fl,cap,r] = G[u][pt[u]]; 
        if (cap-fl > 0 && h[u] > h[v]) push(u,pt[u]);
        else pt[u]++;
      } else {
        relabel(u); pt[u] = 0;
      }
    }
  }
  T max_flow(int s, int t){
    h[s] = (int)G.size(); e[s] = numeric_limits<T>::max();
    for (int i = 0; i < G[s].size(); i++) push(s,i);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (u != s && u != t) discharge(u);
    }
    T ans = 0;
    for (auto & eg : G[t]) ans += G[eg.to][eg.rev].f;
    return ans;
  }
};