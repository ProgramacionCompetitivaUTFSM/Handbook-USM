ll binpow(ll a, ll b, ll mod) {
  a %= mod;
  ll res = 1;
  while (b) {
    if (b & 1)
      res = (res * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return res;
}

// Para exponenciacion binaria de 2^63 - 1
using u64 = uint64_t;
using u128 = __uint128_t;
u64 binpow(u64 a, u64 b, u64 mod) {
  a %= mod;
  u64 res = 1;
  while (b) {
    if (b & 1)
      res = (u128)res * a % mod;
      a = (u128)a * a % mod;
      b >>= 1;
  }
  return res;
}
