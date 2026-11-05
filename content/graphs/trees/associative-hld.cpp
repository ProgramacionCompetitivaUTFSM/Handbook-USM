/*
  *Author:* Javier Oliva
  *Description:* Same complexity of HLD, but with worst constant. This implementation only uses asociativity
  *Status:* Partially tested
*/
template < class DS, class T, T merge(T, T), int IN_EDGES >
  struct associative_heavy_light {
    vector <int> parent, depth, heavy, head, pos_up, pos_down;
    int n, cur_pos_up, cur_pos_down;
    DS ds_up, ds_down;
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
      const & adj, vector < T > & a_up, vector < T > & a_down, vector < T > & values) {
      head[v] = h, pos_up[v] = cur_pos_up--, pos_down[v] = cur_pos_down++;
      a_up[pos_up[v]] = values[v];
      a_down[pos_down[v]] = values[v];
      if (heavy[v] != -1)
        decompose(heavy[v], h, adj, a_up, a_down, values);
      for (int c: adj[v]) {
        if (c != parent[v] && c != heavy[v])
          decompose(c, c, adj, a_up, a_down, values);
      }
    }
    associative_heavy_light(vector < vector < int > >
      const & adj, vector < T > & values) {
      n = adj.size(); parent.resize(n);
      depth.resize(n); heavy.resize(n, -1);
      head.resize(n); pos_up.resize(n);
      pos_down.resize(n);
      vector <T> a_up(n), a_down(n);
      cur_pos_up = n - 1;
      cur_pos_down = 0;
      dfs(0, adj);
      decompose(0, 0, adj, a_up, a_down, values);
      ds_up = DS(a_up);
      ds_down = DS(a_down);
    }
    void update(int a, int b, T x) {
      while (head[a] != head[b]) {
        if (depth[head[a]] < depth[head[b]])
          swap(a, b);
        ds_up.update(pos_up[a], pos_up[head[a]], x);
        ds_down.update(pos_down[head[a]], pos_down[a], x);
        a = parent[head[a]];
      }
      if (depth[a] < depth[b])
        swap(a, b);
      if (pos_up[a] > pos_up[b] - IN_EDGES)
        return;
      ds_up.update(pos_up[a], pos_up[b] - IN_EDGES, x);
      ds_down.update(pos_down[b] + IN_EDGES, pos_down[a], x);
    }
    void update(int a, T x) {
      ds_up.update(pos_up[a], x);
      ds_down.update(pos_down[a], x);
    }
    T query(int a, int b) {
      T ansL, ansR;
      bool hasL = 0, hasR = 0;
      while (head[a] != head[b]) {
        if (depth[head[a]] > depth[head[b]]) {
          hasL ? ansL = merge(ansL, ds_up.query(pos_up[a], pos_up[head[a]])) : ansL = ds_up.query(pos_up[a], pos_up[head[a]]), hasL = 1;
          a = parent[head[a]];
        } else {
          hasR ? ansR = merge(ds_down.query(pos_down[head[b]], pos_down[b]), ansR) : ansR = ds_down.query(pos_down[head[b]], pos_down[b]), hasR = 1;
          b = parent[head[b]];
        }
      }
      if (depth[a] > depth[b] && pos_up[a] <= pos_up[b] - IN_EDGES)
        hasL ? ansL = merge(ansL, ds_up.query(pos_up[a], pos_up[b] - IN_EDGES)) : ansL = ds_up.query(pos_up[a], pos_up[b] - IN_EDGES), hasL = 1;
      else if (depth[a] <= depth[b] && pos_down[a] + IN_EDGES <= pos_down[b])
        hasR ? ansR = merge(ds_down.query(pos_down[a] + IN_EDGES, pos_down[b]), ansR) : ansR = ds_down.query(pos_down[a] + IN_EDGES, pos_down[b]), hasR = 1;

      return (!hasL) ? ansR : (!hasR ? ansL : merge(ansL, ansR));
    }
  };