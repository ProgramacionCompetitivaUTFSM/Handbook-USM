// Usando Kosaraju
template<typename T>
struct SCC {
    vector<vector<int>> GT, G, SCC_G, SCC_GT;
    vector<T> data, compressed_data;
    stack<int> order;
    vector<int> comp, dp;
    vector<bool> visited;
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
    }
 
    void compress_graph() {
        for (int u = 0; u < G.size(); u++)
            compressed_data[comp[u]] += data[u];
 
        for (int u = 0; u < G.size(); u++)
            for (int v : G[u])
                if (comp[u] != comp[v])
                    SCC_G[comp[u]].push_back(comp[v]);
         
    }
 
    T process(int cmp, T (*merge)(T a, T b)) {
        if (dp[cmp]) return dp[cmp];
        dp[cmp] = compressed_data[cmp];
        for (int u : SCC_G[cmp])
            dp[cmp] = merge(dp[cmp], process(u, merge) + compressed_data[cmp]);
        return dp[cmp];
    }
 
    SCC(vector<vector<int>> &G, vector<T> &data, T identity): G(G), data(data) {
        GT.resize(G.size());
        visited.assign(G.size(), 0);
        compressed_data.assign(G.size(), identity);
        comp.assign(G.size(), 0);
        SCC_G.resize(G.size());
        dp.assign(G.size(), identity);
 
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
