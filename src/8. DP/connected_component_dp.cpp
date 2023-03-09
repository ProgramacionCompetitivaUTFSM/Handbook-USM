int n, k, dp[mxN][mxN][1005][3];
int a[mxN];

int ff(ll i, ll c, ll sum, ll b){ // {i, components, sum, borders} 1 indexed
    if(b > 2 || sum > k) return 0; // k = limit sum
    if(c == 0 && i > 1) return 0;
    if(i == n+1) return b == 2 && c == 1; // array completely filled
    int &ret = dp[i][c][sum][b];
    if(ret != -1) return ret;             // this behind changes between problems
    int nsum = sum + (a[i]-a[i-1])*(2*c-b); // all unknown positions equals to a[i] 
    ll ans = 0;
    if(c >= 2) ans += (c-1)*ff(i+1, c-1, nsum, b); // merge two cc
    if(c >= 1) ans += (2LL*c-b)*ff(i+1, c, nsum, b); // add to a component end
    ans += (c+1-b)*(i+1, c+1, nsum, b); // create new component
    if(b < 2) ans += (2LL-b)*ff(i+1, c+1, nsum, b+1); // create new end
    if(b < 1) ans += (2LL-b)*ff(i+1, c, nsum, b+1); // extend cc to a border
    ans %= M; return ret = ans;
}
