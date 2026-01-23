/*
 *Description:* FFT(a) computes $ hat(f(k)) = sum_x a[x] exp(2 pi i dot k x \/ N)$ for all $k$. $N$ must be a power of 2, runs on $O(N log N)$, where $N = |A| + |B|$
  - For convolution of complex numbers or more than two vectors: FFT, multiply pointwise, divide by $n$, reverse(start+1, end), FFT back.
  - Rounding is safe if $(sum a_i^2 + sum b_i^2)log_2(N) < 9 dot 10^14$ (in practice $10^16$; higher for random inputs).
  *Status:* Highly tested (josupo.jp)
*/
struct FFT {
  const long double PI = acos(-1);
  typedef long double d; // to double if too slow
  void fft(vector<complex<d>> &a) {
    int n = a.size(), L = 31 - __builtin_clz(n);
    vector<complex<d>> R(2, 1), rt(2, 1);
    for (int k = 2; k < n; k *= 2) {
      R.resize(n); rt.resize(n);
      auto x = polar(1.0L, PI / k);
      for(int i = k; i < 2*k; ++i) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
    }
    vector<int> rev(n);
    for(int i = 0; i < n; ++i) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    for(int i = 0; i < n; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k)
    for(int j = 0; j < k; ++j) {
      auto x = (d*)&rt[j + k], y = (d*)&a[i + j + k];
      complex<d> z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);
      a[i + j + k] = a[i + j] - z, a[i + j] += z;
    }
  }
  vector<int> conv(vector<d> &a, vector<d> &b) {
    if (a.empty() || b.empty()) return {};
    vector<d> res(a.size() + b.size() - 1);
    int B = 32 - __builtin_clz(res.size()), n = 1 << B;
    vector<complex<d>> in(n), out(n);
    copy(a.begin(), a.end(), in.begin());
    for(int i = 0; i < b.size(); ++i) in[i].imag(b[i]);
    fft(in); for (auto &x : in) x *= x;
    for(int i = 0; i < n; ++i) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out); for(int i = 0; i < res.size(); ++i) res[i] = imag(out[i]) / (4 * n);
    vector<int> resint(res.size());
    for (int i = 0; i < res.size(); i++) resint[i] = round(res[i]);
    return resint;
  }
  vector<ll> convMod(vector<ll> &a, vector<ll> &b, ll mod) {
    if (a.empty() || b.empty()) return {};
    vector<d> res(a.size() + b.size() - 1);
    int B = 32 - __builtin_clz(res.size()), n = 1 << B;
    ll cut = (ll)sqrt(mod);
    vector<complex<d>> L(n), R(n), outs(n), outl(n);
    for (int i = 0; i < (int)a.size(); i++) L[i] = complex<d>(a[i]/cut, a[i]%cut);
    for (int i = 0; i < (int)b.size(); i++) R[i] = complex<d>(b[i]/cut, b[i]%cut);
    fft(L), fft(R);
    for (int i = 0; i < n; i++) {
      int j = -i & (n-1);
      outl[j] = (L[i] + conj(L[j])) * R[i] / ((d)2.0 * n);
      outs[j] = (L[i] - conj(L[j])) * R[i] / ((d)2.0 * n) / complex<d>(0, 1);
    }
    fft(outl), fft(outs);
    for (int i = 0; i < (int)res.size(); i++) {
      ll av = (ll)(real(outl[i])+.5), cv = (ll)(imag(outs[i])+.5);
      ll bv = (ll)(imag(outl[i])+.5) + (ll)(real(outs[i])+.5);
      res[i] = ((av % mod * cut + bv) % mod * cut + cv) % mod;
    }
    vector<ll> resll(res.size());
    for (int i = 0; i < (int)res.size(); i++) resll[i] = (ll)round(res[i]);
    return resll;
  }
};
