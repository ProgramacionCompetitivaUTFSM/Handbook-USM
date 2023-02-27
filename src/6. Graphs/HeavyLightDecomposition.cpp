template<class EST, class NODE, NODE merge(NODE, NODE)>
struct HeavyLight{
    vector<int> parent, depth, heavy, head, pos_up, pos_down;
    int n, cur_pos_up, cur_pos_down;
    EST est_up, est_down;
 
    int dfs(int v, vector<vector<int>> const& adj) {
        int size = 1;
        int max_c_size = 0;
        for (int c : adj[v]) if (c != parent[v]){
            parent[c] = v, depth[c] = depth[v] + 1;
            int c_size = dfs(c, adj);
            size += c_size;
            if (c_size > max_c_size)
                max_c_size = c_size, heavy[v] = c;
        }
        return size;
    }
 
    void decompose(int v, int h, vector<vector<int>> const& adj, vector<NODE>& a_up, vector<NODE>& a_down, vector<NODE>& values) {
        head[v] = h, pos_up[v] = cur_pos_up--, pos_down[v] = cur_pos_down++;
        a_up[pos_up[v]] = values[v];
        a_down[pos_down[v]] = values[v];
        if (heavy[v] != -1)
            decompose(heavy[v], h, adj, a_up, a_down, values);
        for (int c : adj[v]) {
            if (c != parent[v] && c != heavy[v])
                decompose(c, c, adj, a_up, a_down, values);
        }
    }
 
    HeavyLight(vector<vector<int> > const& adj, vector<NODE>& values){
        n = adj.size();
        parent.resize(n);
        depth.resize(n);
        heavy.resize(n, -1);
        head.resize(n);
        pos_up.resize(n);
        pos_down.resize(n);
        vector<NODE> a_up(n), a_down(n);
        cur_pos_up = n - 1;
        cur_pos_down = 0;
 
        dfs(0, adj);
        decompose(0, 0, adj, a_up, a_down, values);
 
        est_up = EST(a_up);
        est_down = EST(a_down);
    }
 
    void update(int a, int b, NODE x){
    	while(head[a] != head[b]) {
    		if (depth[head[a]] > depth[head[b]]){
    			est_up.update(pos_up[a], pos_up[head[a]], x);
    			est_down.update(pos_down[head[a]], pos_down[a], x);
    			a = parent[head[a]];
    		}
    		else{
    			est_down.update(pos_down[head[b]], pos_down[b], x);
    			est_up.update(pos_up[b], pos_up[head[b]], x);
    			b = parent[head[b]];
    		}
    	}
    	if (depth[a] > depth[b]){
    		est_up.update(pos_up[a], pos_up[b], x);
    		est_down.update(pos_down[b], pos_down[a], x);
    	}
    	else{
    		est_down.update(pos_down[a], pos_down[b], x);
    		est_up.update(pos_up[b], pos_up[a], x);
    	}
    }
 
    void update(int a, NODE x){
        est_up.update(pos_up[a], x);
        est_down.update(pos_down[a], x);
    }
 
    NODE query(int a, int b) {
        NODE ansL, ansR; bool hasL = 0, hasR = 0;
        while (head[a] != head[b]) {
            if (depth[head[a]] > depth[head[b]]){
                hasL ? ansL = merge(ansL, est_up.query(pos_up[a], pos_up[head[a]])) : ansL = est_up.query(pos_up[a], pos_up[head[a]]), hasL = 1;
                a = parent[head[a]];
            }
            else{
                hasR ? ansR = merge(est_down.query(pos_down[head[b]], pos_down[b]), ansR) : ansR = est_down.query(pos_down[head[b]], pos_down[b]), hasR = 1;
                b = parent[head[b]];
            }
        }
        if (depth[a] > depth[b])
            hasL ? ansL = merge(ansL, est_up.query(pos_up[a], pos_up[b])) : ansL = est_up.query(pos_up[a], pos_up[b]), hasL = 1;
        else
            hasR ? ansR = merge(est_down.query(pos_down[a], pos_down[b]), ansR) : ansR = est_down.query(pos_down[a], pos_down[b]), hasR = 1;
        
        return (!hasL) ? ansR : (!hasR ? ansL : merge(ansL, ansR));
    }
};

// example
HeavyLight<SegmentTreeLazy<int, int, merge, pushUpd, applyUpd>, int, merge> hld(G, arr);
