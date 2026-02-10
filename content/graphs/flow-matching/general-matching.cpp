/*
 *Description:* General graph matching via randomized Tutte matrix. Fails with probability $N / "mod"$. $O(N^3)$.
 *Status:* KACTL based, not self tested
*/
const ll MOD = 998244353;
ll pw(ll b, ll e, ll m = MOD) {
  ll r = 1; for (b %= m; e > 0; e >>= 1, b = b*b%m)
    if (e & 1) r = r*b%m; return r;
}
int matInv(vector<vector<ll>>& A) {
  int n = A.size(); vector<int> col(n);
  vector<vector<ll>> tmp(n, vector<ll>(n));
  for (int i = 0; i < n; i++) tmp[i][i] = 1, col[i] = i;
  for (int i = 0; i < n; i++) {
    int r = i, c = i;
    for (int j = i; j < n; j++) for (int k = i; k < n; k++)
      if (A[j][k]) { r = j; c = k; goto found; }
    return i;
    found:
    swap(A[i], A[r]); swap(tmp[i], tmp[r]);
    for (int j = 0; j < n; j++)
      swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
    swap(col[i], col[c]);
    ll v = pw(A[i][i], MOD - 2);
    for (int j = i+1; j < n; j++) {
      ll f = A[j][i] * v % MOD;
      A[j][i] = 0;
      for (int k = i+1; k < n; k++)
        A[j][k] = (A[j][k] - f*A[i][k]) % MOD;
      for (int k = 0; k < n; k++)
        tmp[j][k] = (tmp[j][k] - f*tmp[i][k]) % MOD;
    }
    for (int j = i+1; j < n; j++) A[i][j] = A[i][j]*v%MOD;
    for (int j = 0; j < n; j++) tmp[i][j] = tmp[i][j]*v%MOD;
    A[i][i] = 1;
  }
  for (int i = n-1; i > 0; --i) for (int j = 0; j < i; j++) {
    ll v = A[j][i];
    for (int k = 0; k < n; k++)
      tmp[j][k] = (tmp[j][k] - v*tmp[i][k]) % MOD;
  }
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
    A[col[i]][col[j]] = tmp[i][j]%MOD + (tmp[i][j]<0)*MOD;
  return n;
}
vector<pair<int,int>> generalMatching(int N,
    vector<pair<int,int>>& ed) {
  mt19937 rng(chrono::steady_clock::now()
    .time_since_epoch().count());
  vector<vector<ll>> mat(N, vector<ll>(N)), A;
  for (auto [a, b] : ed) {
    int r = rng() % MOD;
    mat[a][b] = r; mat[b][a] = (MOD - r) % MOD;
  }
  int r = matInv(A = mat), M = 2*N - r, fi, fj;
  if (M != N) do {
    mat.resize(M, vector<ll>(M));
    for (int i = 0; i < N; i++) {
      mat[i].resize(M);
      for (int j = N; j < M; j++) {
        int rv = rng() % MOD;
        mat[i][j] = rv; mat[j][i] = (MOD - rv) % MOD;
      }
    }
  } while (matInv(A = mat) != M);
  vector<int> has(M, 1);
  vector<pair<int,int>> ret;
  for (int it = 0; it < M/2; it++) {
    for (int i = 0; i < M; i++) if (has[i])
      for (int j = i+1; j < M; j++)
        if (A[i][j] && mat[i][j])
          { fi = i; fj = j; goto done; }
    break; done:
    if (fj < N) ret.emplace_back(fi, fj);
    has[fi] = has[fj] = 0;
    for (int sw = 0; sw < 2; sw++) {
      ll a = pw(A[fi][fj], MOD - 2);
      for (int i = 0; i < M; i++)
        if (has[i] && A[i][fj]) {
          ll b = A[i][fj] * a % MOD;
          for (int j = 0; j < M; j++)
            A[i][j] = (A[i][j] - A[fi][j]*b) % MOD;
        }
      swap(fi, fj);
    }
  }
  return ret;
}
