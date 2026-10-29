/*
 *Description:* 2D Range queries. Precomputed in $O(n dot m)$. Runs in $O(log n dot log m)$ per operation.
 *Status:* Tested on CSES
*/
struct fenwick_tree_2d {
  int N, M;
  vector<vector<ll>> BIT;
  fenwick_tree_2d(int N, int M) : N(N), M(M) {
      BIT.assign(N + 1, vector<ll>(M + 1, 0));
  }
  fenwick_tree_2d(vector<vector<ll>> &a) : fenwick_tree_2d(a.size(), a[0].size()) {
    for (size_t i = 1; i <= N; i++) {
      for (size_t j = 1; j <= M; j++) {
        BIT[i][j] += a[i - 1][j - 1];
        if (j + (j & -j) <= M)
          BIT[i][j + (j & -j)] += BIT[i][j];
      }
    }
    for (size_t j = 1; j <= M; j++) {
      for (size_t i = 1; i <= N; i++) {
        if (i + (i & -i) <= N)
          BIT[i + (i & -i)][j] += BIT[i][j];
      }
    }
  }
  void update(int x, int y, ll v) {
    for (int i = x; i <= N; i += (i & -i))
      for (int j = y; j <= M; j += (j & -j))
        BIT[i][j] += v;
  }
  ll sum(int x, int y) {
    ll s = 0;
    for (int i = x; i > 0; i -= (i & -i))
      for (int j = y; j > 0; j -= (j & -j))
        s += BIT[i][j];
    return s;
  }
  ll query(int x1, int y1, int x2, int y2) {
    return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
  }
};