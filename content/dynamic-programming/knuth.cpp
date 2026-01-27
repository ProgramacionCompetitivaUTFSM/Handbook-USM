/*
 *Description:* Knuth DP optimization. $O(n^3)$ to $O(n^2)$.
 *Status:* Tested
*/
const ll INF = 1e18;
int n;
vector<vector<ll>> dp;
vector<vector<int>> opt;

ll cost(int i, int j); // define your cost function

ll knuth_dp() {
  dp.assign(n, vector<ll>(n, 0));
  opt.assign(n, vector<int>(n));
  for (int i = 0; i < n; i++) opt[i][i] = i;

  for (int len = 2; len <= n; len++) {
    for (int i = 0; i + len <= n; i++) {
      int j = i + len - 1;
      dp[i][j] = INF;
      for (int k = opt[i][j - 1]; k <= opt[min(i + 1, j)][j]; k++) {
        ll val = dp[i][k] + (k + 1 <= j ? dp[k + 1][j] : 0) + cost(i, j);
        if (val < dp[i][j]) dp[i][j] = val, opt[i][j] = k;
      }
    }
  }
  return dp[0][n - 1];
}
