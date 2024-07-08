/*
  *Description:* Binary pow using mulmod, mulmod can be changed.
  *Status:* Partially tested
*/
ll binpow(ll b, ll e, ll m){
	if(!e)return 1;
	ll q=binpow(b,e/2,m);q=mulmod(q,q,m);
	return e&1?mulmod(b,q,m):q;
}
