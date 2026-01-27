/*
 *Description:* Calculate$space ^(b)a mod m$
 *Status:* Tested on josupo.jp
*/
map<ll, ll> memophi;
ll tetration(ll a, ll b, ll m) {
  if (m == 1) return 0;
  if (a == 0) return (b+1) % 2 % m;
  if (a == 1 or b == 0) return 1;
  if (b == 1) return a % m;
  if (a == 2 and b == 2) return 4 % m;
  if (a == 2 and b == 3) return 16 % m;
  if (a == 3 and b == 2) return 27 % m;
  if (memophi.find(m) == memophi.end()) 
    memophi[m] = phi(m);
  ll tot = memophi[m];
  ll n = tetration(a, b-1, tot);
  return binpow(a, (n < tot ? n + tot : n), m);
}