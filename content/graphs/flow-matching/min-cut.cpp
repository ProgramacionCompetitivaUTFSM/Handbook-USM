/*
 *Author:* Abner Vidal
 *Description:* Recovers the min-cut after running a max flow algorithm.
 *Status:* Tested on codeforces
*/
template<class Edge>
vector<array<int,2>> min_cut(int s, vector<vector<Edge>> &G){
  int n = G.size(); queue<int> q;
  vector<bool> vis(n,0);
  q.push(s); vis[s] = 1;
  while (!q.empty()){
    int p = q.front(); q.pop();
    for (auto & eg : G[p]){
      if (!vis[eg.to] && eg.c-eg.f > 0){
        q.push(eg.to);
        vis[eg.to] = 1;
      }
    }
  }
  vector<array<int,2>> res;
  for (int i = 0; i < n; i++){
    if (!vis[i]) continue;
    for (auto & eg : G[i]){
      if (vis[eg.to] || eg.r) continue;
      res.push_back({i,eg.to});
    }
  }
  return res;
}