// Kosaraju, en O(V + E)
template<typename T>
struct SCC {
    vector<vector<int>> GT, G, SCC_G, SCC_GT, comp_nodes;
    vector<T> data, compressed_data;
    stack<int> order;
    vector<int> comp, dp;
    vector<bool> visited;
    T (*compress_func)(T, T);
    int comp_count = 0;
 
    void topsort(int u) {
        visited[u] = true;
        for (int v : G[u])
            if (!visited[v])
                topsort(v);
        order.push(u);
    }
 
    void build_component(int u) {
        visited[u] = true;
        for (int v : GT[u])
            if (!visited[v])
                build_component(v);
        comp[u] = comp_count;
        comp_nodes[comp_count].push_back(u);
    }
 
    void compress_graph() {
        for (int u = 0; u < G.size(); u++)
            compressed_data[comp[u]] = compress_func(compressed_data[comp[u]], data[u]);
 
        for (int u = 0; u < G.size(); u++)
            for (int v : G[u])
                if (comp[u] != comp[v]) {
                    SCC_G[comp[u]].push_back(comp[v]);
                    SCC_GT[comp[v]].push_back(comp[u]);                    
                }
         
    }
 
    T process(int cmp, T (*func)(T a, T b), T (*merge)(T a, T b)) {
        if (dp[cmp]) return dp[cmp];
        dp[cmp] = compressed_data[cmp];
        for (int u : SCC_G[cmp])
            dp[cmp] = merge(dp[cmp], func(process(u, func, merge), compressed_data[cmp]));
        return dp[cmp];
    }
 
    SCC(vector<vector<int>> &G, vector<T> &data, T (*compress_func)(T a, T b), T comp_identity, T dp_identity): compress_func(compress_func), G(G), data(data) {
        GT.resize(G.size());
        comp_nodes.resize(G.size());
        visited.assign(G.size(), 0);
        compressed_data.assign(G.size(), comp_identity);
        comp.assign(G.size(), 0);
        SCC_G.resize(G.size());
        SCC_GT.resize(G.size());
        dp.assign(G.size(), dp_identity);
 
        for (int u = 0; u < G.size(); u++)
            for (int v : G[u])
                GT[v].push_back(u);
 
        for (int u = 0; u < G.size(); u++)
            if (!visited[u])
                topsort(u);
        
        visited.assign(G.size(), 0);
        while (!order.empty()) {
            int u = order.top();
            order.pop();
            if (visited[u]) continue;
 
            build_component(u);
            comp_count++;
        }
 
        compress_graph();
    }
};
