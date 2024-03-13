/*
 *Description:* centroid decomposition algorithm
 *Status:* No Tested
*/
struct centroid_decomp {
    int n;
    vector<bool> vis;
    vector<int> subtr, parent;
    vector<vector<int>> adj;
    // Opcional
    // ----------
    void dfs(int v,int p = -1){
        for(int u: adj[v]){
            if(u != p && !vis[u]) dfs(u,v);
        }
    }
    // ----------

    int calculate_subtree(int v, int p){
        subtr[v] = 1;
        for (int to : adj[v]){
            if (to == p || vis[to]) continue;
            subtr[v] += calculate_subtree(to,v);
        }
        return subtr[v];
    }
    int get_centroid(int v, int p, int sz){
        for (int to : adj[v]){
            if (to == p || vis[to]) continue;
            if (subtr[to]*2 > sz) return get_centroid(to,v,sz);
        }
        return v;
    }
    int build(int v = 0){
        int centroid = get_centroid(v,v,calculate_subtree(v,v));
        // Opcional
        // ----------
        dfs(centroid);
        // ----------
        vis[centroid] = 1;
        for (int to : adj[centroid]){
            if (vis[to]) continue;
            parent[build(to)] = centroid;
        }
        return centroid;
    }
    centroid_decomp(vector<vector<int>> &_adj){
        adj = _adj;
        n = adj.size();
        subtr.resize(n,0);
        parent.resize(n,-1);
        vis.resize(n,0);
        build();
    }
};
