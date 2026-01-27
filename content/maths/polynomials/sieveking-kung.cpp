/*
 *Description:* Computes the first n elements of the inverse series of a polynomial, 
 requires fast_ntt, and good modulus.
 *Status:* Tested on yosupo
*/
using ull = uint64_t;
const ull mod = 998244353, pr = 3;
vector<ull> sieveking_kung(vector<ull> a, int n) {
  vector<ull> ans = {bin_pow(a[0],mod-2,mod)};
  fast_ntt<mod, pr> pol;
  for (int i = 1; i < n; i <<= 1) {
    vector<ull> a_trunc(a.begin(),a.begin()+min((int)a.size(),2*i));
    vector<ull> res = pol.conv(ans,a_trunc);
    res = pol.conv(res,ans); res.resize(2*i);
    for (int j = 0; j < 2 * i; ++j)
      res[j] = ((j < (int)ans.size()?2*ans[j]:0ULL)+mod-res[j])%mod;
    ans = res;
  }
  ans.resize(n);
  return ans;
}