/*
  *Description:* Exponentiation by squares, computes $a^b mod m$ in $O(log b)$
  *Status:* Highly tested
*/
ll binpow(ll a, ll b, ll m) {
  a %= m;
  ll res = 1;
  while (b > 0) {
    if (b & 1)
      res = (res * a) % m;
    a = (a * a) % m;
    b >>= 1;
  }
  return res;
}