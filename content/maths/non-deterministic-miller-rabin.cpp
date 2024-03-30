/*
  *Description:* Miller rabin using probabilistic algorithm
  *Status:* Partially tested
*/
bool nd_miller_rabin(ll n) {
  if (n == 1) return false;
  auto is_prime_prob = [&](ll n, ll a){
    if (n == a) return true;
    ll s = 0, d = n-1;
    while (d%2==0) s++, d/=2;
    ll x = binpow(a, d, n);
    if ( (x==1) or (x+1 == n)) return true;
    for(ll i = 0; i < s-1; i++) {
      x = mulmod(x, x, n);
      if (x == 1) return false;
      if (x+1 == n) return true;
    }
    return false;
  };
  int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
  for (ll i = 0; i < 9; i++)
    if (!is_prime_prob(n, primes[i]))
      return false;
  return true;
}
