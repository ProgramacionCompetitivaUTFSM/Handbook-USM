// Corre en O(n log(log(n)) ))
struct EratosthenesSieve {
    vector<ll> primes;
    vector<bool> isPrime;

    EratosthenesSieve(ll n) {
        isPrime.resize(n + 1, true);
        isPrime[0] = isPrime[1] = false;

        for (ll i = 2; i*i <= n; i++) {
            if (isPrime[i]) {
                primes.push_back(i);
                for (int j = i*i; j <= n; j += i)
                    isPrime[j] = false;
            }
        }
    }
};
