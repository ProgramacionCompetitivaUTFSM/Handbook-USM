/*
 *Description:* Rolling hash for fast substring comparison, single hash function
 *Status:* Tested
*/
template<class T>
struct rolling_hashing {
  int base, mod; 
  vector<long long> p, H;
  int n;
  rolling_hashing(const T &s, int b, int m): base(b), mod(m), n(s.size()) {
    p.assign(n+1, 1);
    H.assign(n+1, 0);
    for (int i = 0; i < n; ++i) {
      H[i+1] = (H[i] * base + s[i]) % mod;
      p[i+1] = (p[i] * base) % mod;
    }
  }
  int get(int l, int r) {
    int res = (H[r+1] - H[l]*p[r-l+1]) % mod;
    if (res < 0) res += mod;
    return res;
  }
};
