/*
 *Description:* Finds articulation points in a graph using DFS. Runs on $O(V + E)$
 *Status:* Tested on CSES
*/
struct ArticulationPoints {
  int n, timer;
  vector <int> tin, low, vis;
  set <int> points;
  void dfs(int v, int p, vector<vector<int>> &adj) {
    vis[v] = true; tin[v] = low[v] = timer++;
    int child = 0;
    for (int to: adj[v]) {
      if (to == p) continue;
      if (vis[to]) low[v] = min(low[v], tin[to]);
      else {
        dfs(to, v, adj);
        low[v] = min(low[v], low[to]);
        if ((low[to] >= tin[v]) && (p != -1))
          points.insert(v);
        child++;
      }
    }
    if ((p == -1) && (child > 1)) points.insert(v);
  }
  ArticulationPoints(vector < vector < int >> & adj, int root = 0) {
    n = adj.size();
    vis.resize(n, false);
    tin.resize(n);
    low.resize(n);
    dfs(root, -1, adj);
  }
};