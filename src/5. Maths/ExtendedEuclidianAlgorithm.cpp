vector<ll> egcd(ll n, ll m) {
  ll r0 = n, r1 = m;
  ll s0 = 1, s1 = 0;
  ll t0 = 0, t1 = 1;

  while(r1 != 0) {
    ll q = r0/r1;
    ll r = r0 - q*r1; r0 = r1; r1 = r;
    ll s = s0 - q*s1; s0 = s1; s1 = s;
    ll t = t0 - q*t1; t0 = t1; t1 = t;
  }

  return {r0,s0,t0};
}
