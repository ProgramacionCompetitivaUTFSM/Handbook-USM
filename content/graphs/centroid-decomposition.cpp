/*
 *Description:* centroid decomposition algorithm
 *Status:* Partially tested
*/
struct centroid_decomp {
    int n;
    vector<bool> vis;
    vector<int> subtr, parent;
    vector<vector<int>> adj;
    // Optional
    // Here you can insert the functions for traversing the partition
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
            if (subtr[to]*2> sz) return get_centroid(to,v,sz);
        }
        return v;
    }
    int build(int v = 0){
        int centroid = get_centroid(v,v,calculate_subtree(v,v));
        // Optional
        // Here you can call functions for traversing the partition
        // ----------
        dfs(centroid);
        // ----------
        vis[centroid] = 1;
        for (int to : adj[centroid]){
            if (vis[to]) continue;
            build(to);
            // Optional
            // ----------
            // Save parent centroid (Optional)
            parent[build(to)] = centroid;
            // ----------
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
