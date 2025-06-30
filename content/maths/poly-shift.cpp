/*
 *Description:* Solves $f(x + c) = sum_0^(n-1) b_i dot x^i$
 *Status:* Tested
*/
vector<int> polyShift(vector<int> &a, int shift) {
  // change for any mod for ntt
  const int mod = 998244353;
  NTT<998244353, 3> ntt;
  int n = a.size() - 1;
  Factorial f(n, mod);
  vector<int> x(n+1), y(n+1);
  int cur = 1;
  for (int i = 0; i <= n; i++) {
    x[i] = cur * f.finv[i] % mod;
    cur = (cur * shift) % mod;
    y[i] = a[n - i] * f.f[n-i] % mod;
  }
  vector<int> tmp = ntt.conv(x, y), res(n+1);
  for (int i = 0; i <= n; i++)
    res[i] = tmp[n-i] * f.finv[i] % mod;
  return res;
}