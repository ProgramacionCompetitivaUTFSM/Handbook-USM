/*
 *Description:* Computes the chromatic number of a graph in $O(2^{n}n)$
 *Status:* Tested
*/
int chromatic(vector<int> & adj){
    int n = adj.size();
    if (n == 0) return 0;
    ll mod = 998244353, m = (1<<n);
    vector<ll> ind(m),s(m);
    for (int i = 0; i < m; i++)
        s[i] = ((n-__builtin_popcount(i))&1?-1:1);
    ind[0] = 1;
    for (int i = 1; i < m; i++){
        int ctz = __builtin_ctz(i);
        ind[i] = (ind[i-(1<<ctz)]+ind[(i-(1<<ctz))&~adj[ctz]])%mod;
    }
    for (int j = 1; j < n; j++){
        ll sum = 0;
        for (int i = 0; i < m; i++){
            ll cur = (s[i]*ind[i])%mod;
            s[i] = cur;
            sum = (sum+cur)%mod;
        }
        if (sum != 0) return j;
    }
    return n;
}