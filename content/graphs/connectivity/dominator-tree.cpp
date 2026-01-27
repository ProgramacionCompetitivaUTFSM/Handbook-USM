/*
  *Description:* Computes the inmediate dominator of every node in a directed graph in O((|E|+|V|)log(|V|)).
  *Status:* Tested on CSES
*/
struct dominator_tree {
    int n,l,s;
    vector<int> tin,par,vis_ord, dsu_mn, dsu_par, sdom, dep,rdom,idom;
    vector<bool> vis;
    vector<vector<int>> up;
    vector<vector<pair<int,int>>> up_mn;
    void dfs(int u, int p, vector<vector<int>> & adj){
        if (vis[u]) return;
        vis[u] = 1;
        dep[u] = dep[p]+1;
        tin[u] = vis_ord.size();
        vis_ord.push_back(u);
        par[u] = p;
        for (int v : adj[u]) dfs(v,u,adj);
    }
    int find(int x){
        if (dsu_par[x] == -1) return x;
        if (dsu_par[dsu_par[x]] != -1){
            int res = find(dsu_par[x]);
            if (tin[res] < tin[dsu_mn[x]]) 
				dsu_mn[x] = res;
			dsu_par[x] = dsu_par[dsu_par[x]];
        }
        assert(dsu_mn[x] != INT32_MAX);
        return dsu_mn[x];
    }
    void get_sdom(vector<vector<int>> & rev){
        for (int i = vis_ord.size()-1; i >= 0; i--){
            int c = vis_ord[i];
            if (c == s) continue;
            for (int to : rev[c]){
                int res = find(to);
                if (sdom[c] == -1 || tin[res] < tin[sdom[c]])
                    sdom[c] = res;
            }
            dsu_par[c] = par[c];
            dsu_mn[c] = sdom[c];
            if (sdom[c] == -1) cerr << c << endl;
        }
    }
    void init_up(){
        for (int i = 0; i < n; i++){
            if (!vis[i]) continue;
            up[i][0] = par[i];
            up_mn[i][0] = {tin[sdom[i]],i};
        }
        for (int i = 1; i < l; i++) {
			for (int j = 0; j < n; j++) {
                if (!vis[j]) continue;
				int h = up[j][i-1];
				if (h == -1) {
					up[j][i] = -1;
					up_mn[j][i] = up_mn[j][i-1];
				} else {
					up[j][i] = up[h][i-1];
					up_mn[j][i] = min(up_mn[j][i-1], up_mn[h][i-1]);
				}
			}
		}
    }
    int get_min(int v, int u){
        int dist = dep[u]-dep[v];
        pair<int,int> ret = up_mn[u][0];
        int w = u;
        for (int i = 0; i < l; i++)
            if (dist&(1<<i)){
                ret = min(ret,up_mn[w][i]);
                w = up[w][i];
            }
        assert(w == v);
        return ret.second;
    }
    void get_idom(){
        for (int c : vis_ord){
            if (c == s) continue;
            rdom[c] = get_min(sdom[c],c);
        }
        for (int c : vis_ord)
            if (c != s)
                idom[c] = ((rdom[c] == c)?sdom[c]:idom[rdom[c]]);
    }
    dominator_tree(vector<vector<int>> & adj, vector<vector<int>> & rev, int _s = 0, int logn = 20){
        n = adj.size(); l = logn; s = _s;
        tin.resize(n,INT32_MAX);
        par.resize(n,-1);
        vis.resize(n,0);
        dep.resize(n,0);
        dfs(s,-1,adj);
        dsu_par.resize(n,-1);
        dsu_mn.resize(n,INT32_MAX);
        sdom.resize(n,-1);
        rdom.resize(n,-1);
        idom.resize(n,-1);
        get_sdom(rev);
        up.assign(n,vector<int>(logn));
        up_mn.assign(n,vector<pair<int,int>>(logn));
        init_up();
        get_idom();
    }
};