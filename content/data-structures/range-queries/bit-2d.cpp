/*
 *Description:* 2D Range queries. 0-Indexed. Precomputed in $O(n dot m)$. Runs in $O(log n dot log m)$ per operation.
 *Status:* Tested on CSES
*/
struct fenwick_tree_2d {
  int N, M;
  vector<vector<ll>> BIT;
  fenwick_tree_2d(int N, int M) : N(N), M(M) {
      BIT.assign(N, vector<ll>(M, 0));
  }
  fenwick_tree_2d(vector<vector<ll>> &a) : fenwick_tree_2d(a.size(), a[0].size()) {
    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < M; j++) {
        BIT[i][j] += a[i][j];
        if ((j | (j + 1)) < M)
          BIT[i][j | (j + 1)] += BIT[i][j];
      }
    }
    for (size_t j = 0; j < M; j++) {
      for (size_t i = 0; i < N; i++) {
        if ((i | (i + 1)) < N)
          BIT[i | (i + 1)][j] += BIT[i][j];
      }
    }
  }
  void update(int x, int y, ll delta) {
    for (int i = x; i < N; i = (i | (i + 1)))
      for (int j = y; j < M; j = (j | (j + 1)))
        BIT[i][j] += delta;
  }
  ll sum(int x, int y) {
    ll s = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
      for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
        s += BIT[i][j];
    return s;
  }
  ll query(int x1, int y1, int x2, int y2) {
    return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
  }
};