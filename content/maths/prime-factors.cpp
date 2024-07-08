/*
 *Description:* Get all prime factors of $n$, runs on $O(sqrt(n))$
 *Status:* Highly tested
*/
vector<ll> primeFactors(ll n) {
  vector<ll> factors;
  for (ll i = 2; (i*i) <= n; i++) {
    while (n % i == 0) {
      factors.push_back(i);
      n /= i;
    }
  }
  if (n > 1) factors.push_back(n);
  return factors;
}