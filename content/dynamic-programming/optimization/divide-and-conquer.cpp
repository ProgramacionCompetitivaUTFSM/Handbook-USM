/*
 *Description:* Divide and conquer DP optimization. $O(k n^2)$ to $O(k n log n)$.
 *Status:* Tested
*/
const ll INF = 1e18;
int n;
vector<ll> dp, ndp;

ll cost(int l, int r); // define your cost function

void dac_solve(int l, int r, int optl, int optr) {
  if (l > r) return;
  int mid = (l + r) / 2, opt = optl;
  ndp[mid] = INF;
  for (int k = optl; k <= min(mid - 1, optr); k++) {
    ll val = dp[k] + cost(k + 1, mid);
    if (val < ndp[mid]) ndp[mid] = val, opt = k;
  }
  dac_solve(l, mid - 1, optl, opt);
  dac_solve(mid + 1, r, opt, optr);
}

ll dac_dp(int layers) {
  dp.assign(n + 1, INF); dp[0] = 0;
  for (int i = 0; i < layers; i++) {
    ndp.assign(n + 1, INF);
    dac_solve(1, n, 0, n - 1);
    swap(dp, ndp);
  }
  return dp[n];
}
