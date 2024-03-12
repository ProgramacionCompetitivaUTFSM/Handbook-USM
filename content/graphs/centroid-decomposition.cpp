/*
 *Description:* centroid decomposition algorithm
 *Status:* Partially Tested
*/
struct centroid_decomp {
  int n, centroid;
  vector<bool> vis;
  vector<int> subtr;
  void dfs(int v, vector< vector< int > > & adj){
    vis[v] = 1;
    subtr[v]++;
    for (int to : adj[v])
      if (!vis[to]){
        dfs(to,adj);
        subtr[v] += subtr[to];
      }
  }
  int get_centroid(int v, int p, vector< vector< int > > &adj){
    for (int to : adj[v]) {
      if (to == p) continue;
      if (subtr[to] > n/2) return get_centroid(to,v,adj);
    }
    return v;
  }
  centroid_decomp(vector< vector< int > > &adj){
    n = adj.size();
    subtr.resize(n,0);
    parent.resize(n,-1);
    vis.resize(n,0);
    dfs(0,adj);
    centroid = get_centroid(0,0,adj);
  }
};
