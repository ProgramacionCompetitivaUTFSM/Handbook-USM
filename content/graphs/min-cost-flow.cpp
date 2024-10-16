/*
 *Author:* Abner Vidal
 *Description:* Minimun cost flow with complexity  $O (F(|E||V|log(|E|)))$
 *Status:* Tested on CSES
*/
template<class T1, class T2>
struct min_cost_flow {
  struct edge {int v; T1 c,f; T2 w; };
  vvi g; vector<T2> dist,pot; vector<T1> fl;
  vector<bool> vis; vector<int> par; vector<edge> e;
  min_cost_flow(int n):g(n),dist(n),pot(n),fl(n),vis(n),par(n){}
  void add_edge(int u, int v, T1 c, T2 w){
    int k = e.size();
    e.push_back({v,c,0,w}); e.push_back({u,c,c,-w});
    g[u].push_back(k); g[v].push_back(k^1);
  }
  using pli = pair<T2,int>;
  void dijk(int s){
    fill(dist.begin(),dist.end(),numeric_limits<T2>::max());
    fill(vis.begin(),vis.end(),0); fl[s] = numeric_limits<T1>::max();
    priority_queue<pli,vector<pli>,greater<pli>> q;
    q.push({0,s}); dist[s] = 0; 
    while (!q.empty()){
      pli p = q.top(); q.pop(); int x = p.second;
      if (vis[x]) continue; vis[x] = 1;
      for (int to : g[x]){
        T2 d2 = p.first+e[to].w+pot[x]-pot[e[to].v];
        if (!vis[e[to].v] && e[to].f < e[to].c && d2 < dist[e[to].v]){
          dist[e[to].v] = d2; fl[e[to].v] = min(fl[x],e[to].c-e[to].f);
          par[e[to].v] = to; q.push({d2,e[to].v});
        }
      }
    }
  }
  T2 calc_flow(int s, int t, T1 _f){
    T2 cost = 0;
    while (1){
      dijk(s);    
      if (!vis[t]) return -1;
      for (int i = 0; i < g.size(); i++)
        dist[i] += pot[i]-pot[s];
      T1 mnf = min(_f,fl[t]);
      cost += dist[t]*mnf;
      int cur = t;
      while (cur != s){
        e[par[cur]].f += mnf;
        e[par[cur]^1].f -= mnf;
        cur = e[par[cur]^1].v;
      }
      dist.swap(pot);
      _f -= mnf;
      if (!_f) break;
    }
    return cost;
  }
};