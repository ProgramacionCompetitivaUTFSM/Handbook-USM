// Miller-Rabin deterministico O(log^2(n))
bool MillerRabin(uint64_t n) {
  if (n <= 1) return false;
  auto check = [](uint64_t n, uint64_t a, uint64_t d, uint64_t s) {
    int x = binpow(a, d, n); // Usar binpow de 128bits
    if (x == 1 or x == n-1) return false;
    for (int r = 1; r < s; r++) {
      x = (__uint128_t)x*x % n;
      if (x == n-1) return false;
    }
    return true;
  };
  uint64_t r = 0, d = n - 1;
  while ((d & 1) == 0) d >>= 1, r++;
  for (int x : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (x == n) return true;
    if (check(n, x, d, r)) return false;
  }
  return true;
}
