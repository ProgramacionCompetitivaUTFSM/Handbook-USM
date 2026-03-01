/*
 *Author:* KACTL Based
 *Description:* Solves a general linear maximization problem:
 maximize $c^T x$ subject to $A x <= b$, $x >= 0$.
 Returns $-infinity$ if infeasible, $infinity$ if unbounded,
 or the maximum value of $c^T x$ otherwise.
 The input vector is set to an optimal $x$ (or in the unbounded
 case, an arbitrary solution fulfilling the constraints).
 Numerical stability is not guaranteed. For better performance,
 define variables such that $x = 0$ is viable.
 *Time:* $O(n m dot "pivots")$ per pivot. $O(2^n)$ worst case,
 fast in practice.
 *Usage:*
    `lp_solver<double> lp(A, b, c);`
    `vector<double> x;`
    `double val = lp.solve(x);`
 *Status:* Tested
*/
template<class T>
struct lp_solver {
  T eps = 1e-8, inf = 1e18;
  int m, n;
  vector<int> N, B;
  vector<vector<T>> D;

  lp_solver(vector<vector<T>> A, vector<T> b, vector<T> c)
      : m(b.size()), n(c.size()),
        N(n + 1), B(m), D(m + 2, vector<T>(n + 2)) {
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
        D[i][j] = A[i][j];
    for (int i = 0; i < m; i++)
      B[i] = n + i, D[i][n] = -1, D[i][n + 1] = b[i];
    iota(N.begin(), N.end() - 1, 0);
    for (int j = 0; j < n; j++)
      D[m][j] = -c[j];
    N[n] = -1;
    D[m + 1][n] = 1;
  }

  void pivot(int r, int s) {
    T *a = D[r].data(), inv = 1 / a[s];
    for (int i = 0; i < m + 2; i++) {
      if (i == r || abs(D[i][s]) <= eps) continue;
      T *b = D[i].data(), inv2 = b[s] * inv;
      for (int j = 0; j < n + 2; j++)
        b[j] -= a[j] * inv2;
      b[s] = a[s] * inv2;
    }
    for (int j = 0; j < n + 2; j++)
      if (j != s) D[r][j] *= inv;
    for (int i = 0; i < m + 2; i++)
      if (i != r) D[i][s] *= -inv;
    D[r][s] = inv;
    swap(B[r], N[s]);
  }

  int sel(int lo, int hi, vector<T> &row, int phase = 0) {
    int s = -1;
    for (int j = lo; j < hi; j++)
      if (N[j] != -phase)
        if (s == -1 || pair{row[j], N[j]} < pair{row[s], N[s]})
          s = j;
    return s;
  }

  bool simplex(int phase) {
    int x = m + phase - 1;
    for (;;) {
      int s = sel(0, n + 1, D[x], phase);
      if (D[x][s] >= -eps) return true;
      int r = -1;
      for (int i = 0; i < m; i++) {
        if (D[i][s] <= eps) continue;
        if (r == -1 ||
            pair{D[i][n+1] / D[i][s], B[i]} <
            pair{D[r][n+1] / D[r][s], B[r]})
          r = i;
      }
      if (r == -1) return false;
      pivot(r, s);
    }
  }

  T solve(vector<T> &x) {
    int r = 0;
    for (int i = 1; i < m; i++)
      if (D[i][n + 1] < D[r][n + 1]) r = i;
    if (D[r][n + 1] < -eps) {
      pivot(r, n);
      if (!simplex(2) || D[m + 1][n + 1] < -eps)
        return -inf;
      for (int i = 0; i < m; i++)
        if (B[i] == -1)
          pivot(i, sel(0, n + 1, D[i]));
    }
    bool ok = simplex(1);
    x.assign(n, 0);
    for (int i = 0; i < m; i++)
      if (B[i] < n)
        x[B[i]] = D[i][n + 1];
    return ok ? D[m][n + 1] : inf;
  }
};