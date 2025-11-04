/*
 *Author:* Abner Vidal
 *Description:* Computes maximal matching in  $O (|E| dot sqrt(|V|))$, faster than Dinic.
 *Status:* Tested on CSES
*/
struct HopcroftKarp {
  const int INF = 1e9;
  int n; vector<int> l, r, d, ptr, g_edges, g_start, q;
  int q_h, q_t;
  HopcroftKarp(int _n, const vector<vector<int>>& adj) : n(_n) {
    l.assign(2*n+1, 0); r.assign(2*n+1, 0); d.assign(2*n+1, 0); ptr.assign(2*n+1, 0);
    g_start.resize(n+2); q.resize(n+10); q_h = q_t = 0;
    for (int u = 1; u <= n; u++) {
      g_start[u] = g_edges.size();
      for (int b : adj[u]) g_edges.push_back(b+n);
    }
    g_start[n+1] = g_edges.size();
  }
  bool bfs() {
    q_h = q_t = 0;
    for (int u = 1; u <= n; u++) {
      if (!l[u]) { d[u] = 0; q[q_t++] = u; }
      else d[u] = INF;
    }
    d[0] = INF;
    while (q_h < q_t) {
      int u = q[q_h++];
      for (int i = g_start[u]; i < g_start[u+1]; i++) {
        int v = g_edges[i], nxt = r[v];
        if (d[nxt] == INF) {
          d[nxt] = d[u]+1;
          if (nxt) q[q_t++] = nxt;
          else d[0] = d[u]+1;
        }
      }
    }
    return d[0] != INF;
  }
  bool dfs(int u) {
    vector<pair<int,int>> st;
    int i = ptr[u];
    int u_start = g_start[u];
    int u_end = g_start[u+1];
    while (true) {
      if (i < u_end-u_start) {
        int v = g_edges[u_start+i];
        int nxt = r[v];
        if (!nxt) {
          l[u] = v; r[v] = u; ptr[u] = i+1;
          while (!st.empty()) {
            auto [pu, pi] = st.back(); st.pop_back();
            int pv = g_edges[g_start[pu]+pi];
            l[pu] = pv; r[pv] = pu; ptr[pu] = pi+1;
          }
          return true;
        } else if (d[nxt] == d[u]+1) {
          st.push_back({u, i}); u = nxt; i = ptr[u];
          u_start = g_start[u]; u_end = g_start[u+1];
        } else i++;
      } else {
        d[u] = INF;
        if (st.empty()) return false;
        auto [pu, pi] = st.back(); st.pop_back();
        u = pu; i = pi+1; ptr[u] = i;
        u_start = g_start[u]; u_end = g_start[u+1];
      }
    }
  }
  int maximum_matching(int want) {
    int match = 0;
    for (int u = 1; u <= n && match < want; u++) {
      if (!l[u]) {
        for (int i = g_start[u]; i < g_start[u+1]; i++) {
          int v = g_edges[i];
          if (!r[v]) { l[u] = v; r[v] = u; match++; break; }
        }
      }
    }
    while (match < want && bfs()) {
      for (int u = 1; u <= n; u++) ptr[u] = 0;
      for (int u = 1; u <= n && match < want; u++)
      if (!l[u] && dfs(u)) match++;
    }
    return match;
  }
};