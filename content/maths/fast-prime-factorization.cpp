/*
  *Description:* Factorize the number using Pollard's Rho and Miller Rabin $O(n^(1/3))$
  *Status:* Partially tested
*/
void fact(ll n, map<ll, int> &f) { //O (lg n)^3
  if(n==1) return;
  if(nd_miller_rabin(n)) { f[n]++; return; }
  ll q=pollard_rho(n); fact(q,f); fact(n/q,f);
}
