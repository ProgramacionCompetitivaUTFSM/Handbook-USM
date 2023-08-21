struct Factorial {
  vector<int> f, finv, inv; int mod;
  Factorial(int n, int mod): mod(mod) {
    f.assign(n+1, 1); inv.assign(n+1, 1); finv.assign(n+1, 1);
    for(int i = 2; i <= n; ++i)
      inv[i] = mod - (mod/i) * inv[mod%i] % mod;

    for (int i = 1; i <= n; ++i) {
      f[i] = (f[i-1] * i) % mod;
      finv[i] = (finv[i-1] * inv[i]) % mod;
    }
  }
};
