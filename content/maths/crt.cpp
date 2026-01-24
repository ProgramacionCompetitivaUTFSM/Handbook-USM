/*
 *Description:* Chinese remainder theorem
 *Status:* Stress-tested
 */
using lll = __int128_t;
ll crt(vector<ll> a, vector<ll> m) {
  int n = a.size();
  for (int i = 0; i < n; i++) {
    a[i] %= m[i];
    a[i] = a[i] < 0 ? a[i] + m[i] : a[i];
  }
  lll ans = a[0];
  lll M = m[0];
  for (int i = 1; i < n; i++) {
    auto pom = ex_GCD(M, m[i]);
    lll x1 = pom.x;
    lll d = pom.d;
    if ((a[i] - ans) % d != 0)
      return -1;
    ans = ans + x1 * (a[i] - ans) / d % (m[i] / d) * M;
    M = M * m[i] / d;
    ans %= M;
    ans = ans < 0 ? ans + M : ans;
    M = M / (lll)__gcd((ll)M, (ll)m[i]) * m[i];
  }
  return ans;
}
