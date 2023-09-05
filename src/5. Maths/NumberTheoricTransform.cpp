// mod: 9223372036737335297 root: 3
template<int mod, int root>
struct NTT {
  void ntt(int* x, int* temp, int* roots, int N, int skip) {
    if (N == 1) return;
    int n2 = N/2;
    ntt(x, temp, roots, n2, skip*2);
    ntt(x+skip, temp, roots, n2, skip*2);
    for (int i = 0; i < N; i++) temp[i] = x[i*skip];
    for (int i = 0; i < n2; i++) {
      int s = temp[2*i], t = temp[2*i+1] * roots[skip*i];
      x[skip*i] = (s + t) % mod;
      x[skip*(i+n2)] = (s - t) % mod;
    }
  }
  void ntt(vector<int>& x, bool inv = false) {
    int e = binpow(root, (mod-1)/(x.size()), mod);
    if (inv) e = binpow(e, mod-2, mod);
    vector<int> roots(x.size(), 1), temp = roots;
    for (int i = 1; i < x.size(); i++) roots[i] = roots[i-1] * e % mod;
    ntt(&x[0], &temp[0], &roots[0], x.size(), 1);
  }
  vector<int> conv(vector<int> a, vector<int> b) {
    int s = a.size()+b.size()-1;
    if (s <= 0) return {};
    int L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;
    if (s <= 200) {
      vector<int> c(s);
      for(int i = 0; i < a.size(); i++) 
        for(int j = 0; j < b.size(); j++)
          c[i + j] = (c[i + j] + a[i] * b[j]) % mod;
      return c;
    }
    a.resize(n); ntt(a);
    b.resize(n); ntt(b);
    vector<int> c(n); int d = binpow(n, mod-2, mod);
    for (int i = 0; i < n; i++) c[i] = a[i] * b[i] % mod * d % mod;
    ntt(c, true); c.resize(s); return c;
  }
};
