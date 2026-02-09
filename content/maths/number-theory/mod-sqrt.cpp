/*
 *Description:* Tonelli-Shanks. Finds $x$ s.t. $x^2 equiv a (mod p)$ ($-x$ gives the other). $O(log^2 p)$ worst case.
 *Status:* KACTL based, not self tested
*/
ll modpow(ll b, ll e, ll m) {
  ll r = 1; for (b %= m; e > 0; e >>= 1, b = b*b%m)
    if (e & 1) r = r*b%m; return r;
}
ll modSqrt(ll a, ll p) {
  a %= p; if (a < 0) a += p;
  if (a == 0) return 0;
  assert(modpow(a, (p-1)/2, p) == 1);
  if (p % 4 == 3) return modpow(a, (p+1)/4, p);
  ll s = p-1, n = 2;
  int r = 0, m;
  while (s % 2 == 0) ++r, s /= 2;
  while (modpow(n, (p-1)/2, p) != p-1) ++n;
  ll x = modpow(a, (s+1)/2, p);
  ll b = modpow(a, s, p), g = modpow(n, s, p);
  for (;; r = m) {
    ll t = b;
    for (m = 0; m < r && t != 1; ++m) t = t*t%p;
    if (m == 0) return x;
    ll gs = modpow(g, 1LL << (r-m-1), p);
    g = gs*gs%p;
    x = x*gs%p;
    b = b*g%p;
  }
}
