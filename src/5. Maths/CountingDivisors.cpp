// Contar divisores en O(n ^ (1/3) )
int countingDivisors(int n) {
  int MX_P = 1e6 + 1, ret = 1;
  EratosthenesSieve sieve(MX_P);
  for (int p : sieve.primes) {
    if (p*p*p > n) break;
    int count = 1;
    while (n % p == 0)
      n /= p, count++;
    ret *= count;
  }
  int isqrt = sqrt(n);
  if (MillerRabin(n)) ret *= 2;
  else if (isqrt*isqrt == n and MillerRabin(isqrt)) ret *= 3;
  else if (n != 1) ret *= 4;
  return ret;
}
