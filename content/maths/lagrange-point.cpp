/*
 *Description:* Using points evaluated at 0,1,..n from f(n), interpolates f(x).
 Time complexity O(k), where k is the amount of points
 *Status:* Tested on codeforces
*/
ll lagrange_point(vector<ll> & p, ll x){
    int n = p.size();
    if (x < n) return p[x];
    vector<ll> pref(n+1,1), suff(n+1,1);
    for (int i = 1; i <= n; i++) pref[i] = (pref[i-1]*(x-(i-1)))%mod;
    for (int i = n-1; i >= 0; i--) suff[i] = (suff[i+1]*(x-i))%mod;
    vector<ll> ifact(n);
    ll fact = 1;
    for (ll i = 1; i < n; i++) fact = (fact*i)%mod;
    ifact[n-1] = binpow(fact,mod-2);
    for (ll i = n-2; i >= 0; i--) ifact[i] = (ifact[i+1]*(i+1))%mod;
    ll res = 0;
    for (int i = 1; i <= n; i++){
        ll val = (pref[i-1]*suff[i])%mod;
        ll temp = (((n-i)&1)?mod-1:1);
        val = (val*temp)%mod;
        val = (val*ifact[i-1])%mod;
        val = (val*ifact[n-i])%mod;
        val = (val*p[i-1])%mod;
        res = (res+val)%mod;
    }
    if (res < 0) res += mod;
    return res;
}