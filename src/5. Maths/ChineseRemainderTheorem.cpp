struct GCD_type { ll x, y, d; };
GCD_type ex_GCD(ll a, ll b){
  if (b == 0) return {1, 0, a};
  GCD_type pom = ex_GCD(b, a % b);
  return {pom.y, pom.x - a / b * pom.y, pom.d};
}
ll crt(vector<ll> a, vector<ll> m){
  int n = a.size();
  for (int i = 0; i < n; i ++){
    a[i] %= m[i];
    a[i] = a[i] < 0 ? a[i] + m[i] : a[i];
  }
  ll ans = a[0];
  ll M = m[0];
  for (int i = 1; i < n; i ++){
    auto pom = ex_GCD(M, m[i]);
    ll x1 = pom.x;
    ll d = pom.d;
    if ((a[i] - ans) % d != 0)
      return -1;
    ans = ans + x1 * (a[i] - ans) / d % (m[i] / d) * M;
    M = M * m[i] / d;
    ans %= M;
    ans = ans < 0 ? ans + M : ans;
    M = M / __gcd(M, m[i]) * m[i];
  }
  return ans;
}
