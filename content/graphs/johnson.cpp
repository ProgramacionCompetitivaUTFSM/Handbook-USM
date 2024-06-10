/*
 *Author:* Abner Vidal
 *Description:* Minimun cost flow with complexity  $O (|E||V|log(|E|))$
 *Status:* Partially tested
*/
struct edge {
  int u,v,rev,cap,cost;
};
int johnson(vector<vector<int>> & adj, vector<edge> & edges, int k, int s, int t){
  vector<int> dist(adj.size()),par(adj.size());
  vector<bool> vis(adj.size());
  int f = 0, ans = 0;
  while (f < k){
    fill(dist.begin(),dist.end(),inf);
    fill(vis.begin(),vis.end(),0);
    priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> q;
    q.push({0,s});
    dist[s] = 0;
    while (!q.empty()){
      pair<int,int> p = q.top();
      q.pop();
      vis[p.second] = 0;
      for (int to : adj[p.second])
        if (!vis[edges[to].v] && edges[to].cap && dist[edges[to].v] > dist[p.second]+edges[to].cost){
          dist[edges[to].v] = dist[p.second]+edges[to].cost;
          par[edges[to].v] = to;
          if (!vis[edges[to].v]){
            vis[edges[to].v];
            q.push({dist[edges[to].v],edges[to].v});
          }
        }
    }
    if (dist[t] == inf) break;
    int mn = k-f, cur = t;
    while (cur != s){
      mn = min(mn,edges[par[cur]].cap);
      cur = edges[par[cur]].u;
    }
    f += mn;
    ans += mn*dist[t];
    cur = t;
    while (cur != s){
      edges[par[cur]].cap -= mn;
      edges[edges[par[cur]].rev].cap += mn;
      cur = edges[par[cur]].u;
    }
  }
  if (f < k) return -1;
  return ans;
}