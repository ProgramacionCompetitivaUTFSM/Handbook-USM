struct FenwickTree2D {
  int N, M;
  vector < vector < int >> BIT;

  FenwickTree2D(int N, int M): N(N), M(M) {
    BIT.assign(N + 1, vector < int > (M + 1, 0));
  }

  void update(int x, int y, int v) {
    for (int i = x; i <= N; i += (i & -i))
      for (int j = y; j <= M; j += (j & -j))
        BIT[i][j] += v;
  }

  int sum(int x, int y) {
    int s = 0;
    for (int i = x; i > 0; i -= (i & -i))
      for (int j = y; j > 0; j -= (j & -j))
        s += BIT[i][j];
    return s;
  }

  int query(int x1, int y1, int x2, int y2) {
    return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
  }
};
