map<int, int> memophi;
int tetration(int a, int b, int mod) {
  if (mod == 1) return 0;
  if (a == 0) return (b+1) % 2 % mod;
  if (a == 1 or b == 0) return 1;
  if (b == 1) return a % mod;
  if (a == 2 and b == 2) return 4 % mod;
  if (a == 2 and b == 3) return 16 % mod;
  if (a == 3 and b == 2) return 27 % mod;
  if (memophi.find(mod) == memophi.end()) 
    memophi[mod] = phi(mod);
  int tot = memophi[mod];
  int n = tetration(a, b-1, tot);
  return binpow(a, (n < tot ? n + tot : n), mod);
}
