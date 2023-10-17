struct Bridges {
  int n, timer;
  vector <int> tin, low, vis;
  vector <pair<int, int>> bridges;
  Bridges(vector <vector<int>> &adj, int root = 0) {
    n = adj.size();
    timer = 0;
    vis.resize(n, false);
    tin.resize(n);
    low.resize(n);
    dfs(root, root, adj);
  }
  void dfs(int v, int p, vector <vector<int>> &adj) {
    vis[v] = 1; tin[v] = low[v] = timer++;
    for (int to: adj[v]) {
      if (to == p) continue;
      if (vis[to]) low[v] = min(low[v], tin[to]);
      else {
        dfs(to, v, adj);
        low[v] = min(low[v], low[to]);
        if (low[to] > tin[v]) bridges.push_back({v,to});
      }
    }
  }
};
