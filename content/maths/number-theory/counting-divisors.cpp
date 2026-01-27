/*
 *Description*: Counting divisors in $O(n ^ (1/3))$
 *Status:* Tested on codeforces
*/
const int MX_P = 1e6 + 1;
eratosthenes_sieve sieve(MX_P);
ll counting_divisors(ll n) {
  ll ret = 1;
  for (ll p : sieve.primes) {
    if (p*p*p > n) break;
    ll count = 1;
    while (n % p == 0)
      n /= p, count++;
    ret *= count;
  }
  ll isqrt = sqrtl(n);
  if (miller_rabin(n)) ret *= 2;
  else if (isqrt*isqrt == n and miller_rabin(isqrt)) ret *= 3;
  else if (n != 1) ret *= 4;
  return ret;
}
