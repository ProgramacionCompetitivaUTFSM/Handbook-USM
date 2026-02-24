/*
 *Description:* Computes the virtual tree given the nodes in $O(K log V)$, uses binary lifting and works for directed and undirected graphs.
 *Status:* Tested
*/
struct virtual_tree {
  int n,timer,lg;
  vector<int> tin,tout,dep;
  vector<vector<int>> up,adj_vt;
  void dfs(int u, int p, vector<vector<int>> & adj){
    tin[u] = ++timer;
    up[u][0] = p;
    for (int i = 1; i <= lg; i++)
      up[u][i] = up[up[u][i-1]][i-1];
    for (int v : adj[u]){
      if (v == p) continue;
      dep[v] = dep[u]+1;
      dfs(v,u,adj);
    }
    tout[u] = timer;
  }
  bool is_ancestor(int u, int v) { 
    return (tin[u] <= tin[v] && tout[u] >= tout[v]); 
  }
  int lca(int u, int v){
    if (is_ancestor(u,v)) return u;
    if (is_ancestor(v,u)) return v;
    for (int i = lg; i >= 0; i--)
      if (!is_ancestor(up[u][i],v))
        u = up[u][i];
    return up[u][0];
  }
  virtual_tree(vector<vector<int>> & adj, int logn = 20){
    n = adj.size(); timer = 0; lg = logn;
    tin.resize(n); tout.resize(n); dep.resize(n,0);
    up.assign(n,vector<int>(lg+1));
    adj_vt.resize(n); dfs(0,0,adj);
  }
  // builds the virtual tree in adj_vt, and returns the root
  int build(vector<int> nodes){
    assert(!nodes.empty());
    auto cmp = [&](int u, int v){ return (tin[u] < tin[v]); };
    sort(nodes.begin(),nodes.end(),cmp);
    int k = nodes.size();
    for (int i = 1; i < k; i++)
      nodes.push_back(lca(nodes[i-1],nodes[i]));
    sort(nodes.begin(),nodes.end(),cmp);
    nodes.erase(unique(nodes.begin(),nodes.end()),nodes.end());
    for (int v : nodes) adj_vt[v].clear();
    vector<int> st = {nodes[0]};
    for (int i = 1; i < nodes.size(); i++){
      int u = nodes[i];
      while (st.size() >= 2 && !is_ancestor(st.back(),u)){
        adj_vt[st[st.size()-2]].push_back(st.back());
        st.pop_back();
      } 
      st.push_back(u);
    }
    while (st.size() >= 2){
      adj_vt[st[st.size()-2]].push_back(st.back());
      st.pop_back();
    }
    return nodes[0];
  }
};