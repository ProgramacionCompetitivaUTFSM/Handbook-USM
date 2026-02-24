/*
 *Description:* Recovers $n$-order linear recurrence from first $2n$ terms. Output size $lt.eq n$. $O(N^2)$.
 *Usage:* `berlekampMassey({0, 1, 1, 3, 5, 11})` returns `{1, 2}`
 *Status:* KACTL based, not self tested
*/
const ll mod = 998244353;
ll modpow(ll b, ll e, ll m = mod) {
  ll r = 1; for (b %= m; e > 0; e >>= 1, b = b*b%m)
    if (e & 1) r = r*b%m; return r;
}
vector<ll> berlekampMassey(vector<ll> s) {
  int n = s.size(), L = 0, m = 0;
  vector<ll> C(n), B(n), T;
  C[0] = B[0] = 1;
  ll b = 1;
  for (int i = 0; i < n; i++) { ++m;
    ll d = s[i] % mod;
    for (int j = 1; j <= L; j++)
      d = (d + C[j] * s[i-j]) % mod;
    if (!d) continue;
    T = C; ll coef = d * modpow(b, mod-2) % mod;
    for (int j = m; j < n; j++)
      C[j] = (C[j] - coef * B[j-m]) % mod;
    if (2*L > i) continue;
    L = i+1-L; B = T; b = d; m = 0;
  }
  C.resize(L+1); C.erase(C.begin());
  for (ll& x : C) x = (mod - x) % mod;
  return C;
}
