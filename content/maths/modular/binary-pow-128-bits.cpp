/*
  *Description:* Binary pow in 128 bits, computes $a^b mod m$ in $O(log b)$
  *Status:* Highly tested
*/
using u64 = uint64_t;
using u128 = __uint128_t;
u64 binpow(u64 a, u64 b, u64 m) {
  a %= m;
  u64 res = 1;
  while (b > 0) {
    if (b & 1)
      res = (u128)res * a % m;
    a = (u128)a * a % m;
    b >>= 1;
  }
  return res;
}