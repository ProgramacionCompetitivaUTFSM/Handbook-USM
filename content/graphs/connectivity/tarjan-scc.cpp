/*
 *Description:* Finds SCC on a graph
 *Complexity:* $O(V+E)$
 *Status:* Tested on CSES
*/
struct tarjan {
  int n,timer;
  vector<bool> vis,ist;
  vector<int> tin,low,st,cmp;
  vector<vector<int>> scc; 
  void dfs(int u, vector<vector<int>> & adj){
    vis[u] = ist[u] = 1;
    st.push_back(u); tin[u] = low[u] = timer++;
    for (auto v : adj[u]){
      if (!vis[v]){
        dfs(v,adj);
        low[u] = min(low[u],low[v]);
      } else if (ist[v]){
        low[u] = min(low[u],tin[v]);
      }
    }
    if (low[u] == tin[u]){
      scc.emplace_back(); int cur;
      do {
        cur = st.back(); st.pop_back();
        ist[cur] = 0; scc.back().push_back(cur);
        cmp[cur] = (int)scc.size()-1;
      } while (cur != u);
    }
  }
  tarjan(vector<vector<int>> & adj){
    n = adj.size(); tin.resize(n); timer = 0; cmp.resize(n);
    low.resize(n); vis.resize(n,0); ist.resize(n,0); 
    for (int i = 0; i < n; i++) if (!vis[i]) dfs(i,adj);
  }
};