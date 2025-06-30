/*
  *Author:* 
  *Description:* Computes XOR, OR and AND convolution of two arrays in $O(n log n)$.
  op = 0 -> OR, op = 1 -> AND, op = 2 -> XOR, mxn and n must be powers of two.
  *Status:* Tested on CSES
*/
const int mod = 1e9+7, mxn = (1<<20), op = 2;
const int inv2 = (mod+1) >> 1;
struct fwht {
  int P1[mxn], P2[mxn];
  void wt(int *a, int n){
    if (n == 0) return;
    int m = n/2;
    wt(a,m); wt(a+m,m);
    for (int i = 0; i < m; i++){
      int x = a[i], y = a[i+m];
      if (op == 0) a[i] = x, a[i+m] = (x+y)%mod;
      if (op == 1) a[i] = (x+y)%mod, a[i+m] = y;
      if (op == 2) a[i] = (x+y)%mod, a[i+m] = (x-y+mod)%mod;
    }
  }
  void iwt(int* a, int n){
    if (n == 0) return;
    int m = n/2;
    iwt(a,m); iwt(a+m,m);
    for (int i = 0; i < m; i++){
      int x = a[i], y = a[i+m];
      if (op == 0) a[i] = x, a[i+m] = (y-x+mod)%mod;
      if (op == 1) a[i] = (x-y+mod)%mod, a[i+m] = y;
      if (op == 2) a[i] = 1LL*(x+y)*inv2%mod, a[i+m] = 1LL*(x-y+mod)*inv2%mod;
    }
  }
  vector<int> conv(int n, vector<int> A, vector<int> B) {
    A.resize(n); B.resize(n);
    for (int i = 0; i < n; i++) P1[i] = A[i];
    for (int i = 0; i < n; i++) P2[i] = B[i];
    wt(P1, n); wt(P2, n);
    for (int i = 0; i < n; i++) P1[i] = 1LL*P1[i]*P2[i]%mod;
    iwt(P1, n);
    return vector<int> (P1, P1 + n);
  }
} FWHT;