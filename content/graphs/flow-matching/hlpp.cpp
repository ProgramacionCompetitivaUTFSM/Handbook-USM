/*
 *Author:* Abner Vidal
 *Description:* Flow algorithm with complexity  $O (|V|^2 dot sqrt(|E|))$
 *Status:* Tested on CSES
*/
template<class T>
struct hlpp {
  struct edge {int to,rev; T f,c;};
  vector<edge> g; vector<vector<int>> adj;
  vector<int> h,pt,cnt; vector<T> e;
  vector<vector<int>> q; int mx,n;
  hlpp(int _n) : adj(_n), h(_n,_n), pt(_n,0), cnt(2*_n+1,0), e(_n,0), q(2*_n), mx(-1), n(_n) {}
  void add_edge(int u, int v, T cap){
    int cur =  g.size();
    adj[u].push_back(cur); g.push_back({v,cur+1,0,cap});
    adj[v].push_back(cur+1); g.push_back({u,cur,0,0}); // use cap instead of 0, if bidirectional
  }
  void bfs(int s, int t){
    queue<int> qr; qr.push(t); h[t] = 0;
    while (!qr.empty()){
      int u = qr.front(); qr.pop();
      for (int ev : adj[u]) {
        int v = g[ev].to;
        if (h[v] == n && g[g[ev].rev].c-g[g[ev].rev].f > 0) {
          h[v] = h[u]+1; cnt[h[v]]++;
          qr.push(v);
        }
      }
    }
  }
  void push(int u, int ev) {
    auto [v,rev,fl,cap] = g[ev];
    T d = min(e[u],cap-fl);
    g[ev].f += d; g[rev].f -= d;
    e[u] -= d; e[v] += d;
    if (d != 0 && e[v] == d){
      q[h[v]].push_back(v);
      mx = max(mx,h[v]);
    } 
  }
  void relabel(int u) {
    cnt[h[u]]--;
    if (cnt[h[u]] == 0) {
      int gap = h[u];
      for (int v = 0; v < n; v++){
        if (h[v] > gap && h[v] < n) {
          cnt[h[v]]--;
          h[v] = n; 
        }
      }   
    }
    int d = 2*n;
    for (int ev : adj[u]) {
      auto& eg = g[ev];
      if (eg.c-eg.f > 0) d = min(d, h[eg.to]);
    }
    if (d < 2*n) h[u] = d+1, cnt[h[u]]++;
  }
  void discharge(int u) {
    while (e[u] > 0) {
      if (pt[u] < (int)adj[u].size()) {
        auto [v,rev,fl,cap] = g[adj[u][pt[u]]]; 
        if (cap-fl > 0 && h[u] > h[v]) push(u,adj[u][pt[u]]);
        else pt[u]++;
      } else {
        relabel(u); pt[u] = 0;
        if (h[u] >= n) break;
      }
    }
  }
  T max_flow(int s, int t){
    bfs(s,t); cnt[0] = n; 
    h[s] = n; e[s] = numeric_limits<T>::max();
    for (int to : adj[s]) push(s,to);
    while (mx != -1) {
      while (mx != -1 && q[mx].empty()) mx--;
      if (mx == -1) break;
      int u = q[mx].back(); q[mx].pop_back();
      if (u != s && u != t) discharge(u);
    }
    T ans = 0;
    for (int to : adj[t]) ans += g[g[to].rev].f;
    return ans;
  }
};