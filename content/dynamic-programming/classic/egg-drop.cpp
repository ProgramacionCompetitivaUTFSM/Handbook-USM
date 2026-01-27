/*
 *Description:* Egg drop: min attempts for $h$ floors and $k$ eggs. $O(k h log h)$.
 *Status:* Tested
*/
const ll INF = 1e18;

ll egg_drop(int h, int k) {
  vector<vector<ll>> dp(h + 1, vector<ll>(k + 1, INF));
  for (int j = 0; j <= k; j++) dp[0][j] = 0;
  for (int j = 1; j <= k; j++) {
    for (int i = 1; i <= h; i++) {
      int lo = 1, hi = i;
      while (lo <= hi) {
        int mid = (lo + hi) / 2;
        ll br = dp[mid - 1][j - 1], sv = dp[i - mid][j];
        dp[i][j] = min(dp[i][j], 1 + max(br, sv));
        (br < sv) ? lo = mid + 1 : hi = mid - 1;
      }
    }
  }
  return dp[h][k];
}

// O(k*h) alternative: dp[t][k] = max floors with t tries
ll egg_drop_fast(int h, int k) {
  vector<ll> cur(k + 1, 0), nxt(k + 1);
  for (int t = 1; t <= h; t++) {
    for (int j = 1; j <= k; j++) {
      nxt[j] = cur[j - 1] + cur[j] + 1;
      if (nxt[j] >= h) return t;
    }
    swap(cur, nxt);
  }
  return h;
}
