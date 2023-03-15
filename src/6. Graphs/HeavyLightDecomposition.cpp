template < class DS, class T, T merge(T, T), int IN_EDGES >
  struct heavy_light {
    vector < int > parent, depth, heavy, head, pos_down;
    int n, cur_pos_down;
    DS ds_down;

    int dfs(int v, vector < vector < int >>
      const & adj) {
      int size = 1;
      int max_c_size = 0;
      for (int c: adj[v])
        if (c != parent[v]) {
          parent[c] = v, depth[c] = depth[v] + 1;
          int c_size = dfs(c, adj);
          size += c_size;
          if (c_size > max_c_size)
            max_c_size = c_size, heavy[v] = c;
        }
      return size;
    }

    void decompose(int v, int h, vector < vector < int >>
      const & adj, vector < T > & a_down, vector < T > & values) {
      head[v] = h, pos_down[v] = cur_pos_down++;
      a_down[pos_down[v]] = values[v];
      if (heavy[v] != -1)
        decompose(heavy[v], h, adj, a_down, values);
      for (int c: adj[v]) {
        if (c != parent[v] && c != heavy[v])
          decompose(c, c, adj, a_down, values);
      }
    }

    heavy_light(vector < vector < int > >
      const & adj, vector < T > & values) {
      n = adj.size();
      parent.resize(n);
      depth.resize(n);
      heavy.resize(n, -1);
      head.resize(n);
      pos_down.resize(n);
      vector < T > a_down(n);
      cur_pos_down = 0;

      dfs(0, adj);
      decompose(0, 0, adj, a_down, values);

      ds_down = DS(a_down);
    }

    void update(int a, int b, T x) {
      while (head[a] != head[b]) {
        if (depth[head[a]] < depth[head[b]])
          swap(a, b);
        ds_down.update(pos_down[head[a]], pos_down[a], x);
        a = parent[head[a]];
      }
      if (depth[a] < depth[b])
        swap(a, b);
      if (pos_down[b] + IN_EDGES > pos_down[a])
        return;
      ds_down.update(pos_down[b] + IN_EDGES, pos_down[a], x);
    }

    void update(int a, T x) {
      ds_down.update(pos_down[a], x);
    }

    T query(int a, int b) {
      T ans;
      bool has = 0;
      while (head[a] != head[b]) {
        if (depth[head[a]] < depth[head[b]])
          swap(a, b);
        ans = has ? merge(ans, ds_down.query(pos_down[head[a]], pos_down[a])) : ds_down.query(pos_down[head[a]], pos_down[a]);
        has = 1;
        a = parent[head[a]];
      }
      if (depth[a] < depth[b])
        swap(a, b);
      if (pos_down[b] + IN_EDGES > pos_down[a])
        return ans;
      return has ? merge(ans, ds_down.query(pos_down[b] + IN_EDGES, pos_down[a])) : ds_down.query(pos_down[b] + IN_EDGES, pos_down[a]);
    }
  };
