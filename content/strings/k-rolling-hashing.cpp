/*
 *Description:* Rolling hash with multiple hash functions for collision resistance
 *Status:* Tested
*/
template<class T>
struct rolling_hashing {
  vector<ll> base, mod; int n, k;
  vector<vector<ll>> p, H;
  rolling_hashing(T s, vector<ll> b, vector<ll> m): base(b), mod(m), n(s.size()), k(b.size()) {
    p.resize(k); H.resize(k);
    for (int j = 0; j < k; j++) {
      p[j].assign(n + 1, 1);
      H[j].assign(n + 1, 0);
      for (int i = 0; i < n; i++) {
        H[j][i + 1] = (H[j][i] * b[j] + s[i]) % mod[j];
        p[j][i + 1] = (p[j][i] * b[j]) % mod[j];
      }
    }
  }
  vector<ll> get(int l, int r) {
    vector<ll> res(k);
    for (int j = 0; j < k; j++) {
      res[j] = (H[j][r + 1] - H[j][l] * p[j][r - l + 1] % mod[j] + mod[j]) % mod[j];
    }
    return res;
  }
};