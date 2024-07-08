/*
 *Description:* Calculate factorials from $1$ to $n$ and their factorial, runs on $O(n)$
 *Status:* Highly tested
*/
struct Factorial {
  vector<ll> f, finv, inv; ll mod;
  Factorial(ll n, ll mod): mod(mod) {
    f.assign(n+1, 1); inv.assign(n+1, 1); finv.assign(n+1, 1);
    for(ll i = 2; i <= n; ++i)
      inv[i] = mod - (mod/i) * inv[mod%i] % mod;
    for (ll i = 1; i <= n; ++i) {
      f[i] = (f[i-1] * i) % mod;
      finv[i] = (finv[i-1] * inv[i]) % mod;
    }
  }
}