/*
  *Description:* Get all prime numbers up to $n$, runs on $O(n log(log (n)) ) $
  *Status:* Highly tested
*/
struct eratosthenes_sieve {
  vector<ll> primes;
  vector<bool> isPrime;
  eratosthenes_sieve(ll n) {
    isPrime.resize(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (ll i = 2; i <= n; i++) {
      if (isPrime[i]) {
        primes.push_back(i);
        for (ll j = i*i; j <= n; j += i)
          isPrime[j] = false;
      }
    }
  }
};