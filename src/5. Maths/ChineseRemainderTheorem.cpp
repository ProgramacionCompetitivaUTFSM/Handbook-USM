ll GCRT(vector<ll> &A, vector<ll> &N) {
  int k = A.size();
  ll a = A[0], n = N[0];
  for(int i = 1; i < k; ++i) {
    vector<ll> v = egcd(n,N[i]); 
    ll g = v[0], m1 = v[1], m2 = v[2];
    if((a - A[i])%g != 0) return -1;
    ll nn = N[i]/g*n; a = (a*m2%nn*(N[i]/g) + A[i]*m1%nn*(n/g))%nn;
    n = nn; if(a < 0) a += n;
  }
  return a;
}
