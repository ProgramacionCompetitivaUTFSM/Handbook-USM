/*
 *Description:* Range queries, precomputed $O(n log n)$, query $O(1)$.
 - Only needs associativity
 - Does not allow updates
 *Status:* Tested on CSES/Codeforces
*/
template <typename T, T (*m_)(T, T)>
struct disjoint_sparse_table{
  static const int MAXLOG = 20;
  vector<T> dp[MAXLOG]; vector<bool> has[MAXLOG];
  disjoint_sparse_table() {}
  disjoint_sparse_table(vector<T> &ar){
    int i, c, h, l, n = (int)ar.size();
    for (h = 0; h <= __lg(n); h++){
      dp[h].resize(n + 1), has[h].resize(n+1);
      for (c = l = 1 << h; c < n + l; c += (l << 1)){
        for (i = c + 1; i <= min(n, c + l); i++) {
          if (!has[h][i-1]) dp[h][i] = ar[i-1];
          else dp[h][i] = m_(dp[h][i - 1], ar[i-1]);
          has[h][i] = 1;
        }
        for (i = min(n, c) - 1; i >= c - l; i--) {
          if (!has[h][i+1]) dp[h][i] = ar[i];
          else dp[h][i] = m_(ar[i], dp[h][i+1]);
          has[h][i] = 1;
        }
      }
    }
  }
  T query(int l, int r){
    int h = __lg(l ^ (r + 1));
    if (!has[h][l]) return dp[h][r+1];
    if (!has[h][r+1]) return dp[h][l];
    return m_(dp[h][l], dp[h][r + 1]);
  }
};
