/*
  *Description:* Multiply two number fast, secure for number lesser than $2^57$
  *Status:* Partially tested
*/
ll mulmod(ll a, ll b, ll m) {
  ll r=a*b-(ll)((ld)a*b/m+.5)*m;
  return r<0?r+m:r;
}
