const double EPS = 1e-18;
const int INF = 2; // it doesn't actually have to be infinity or a big number
const int MOD = 1e9+7;
int gauss (vector < vector<ll> > a, vector<ll> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;
 
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (!a[sel][col])
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;
 
        for (int i=0; i<n; ++i)
            if (i != row) {
                ll c = ((ll) a[i][col] *binpow(round(a[row][col]),MOD - 2,MOD)) % MOD;
                for (int j=col; j<=m; ++j)
                    a[i][j] = ((a[i][j] - a[row][j] * c) % MOD + MOD) % MOD;
            }
        ++row;
    }
 
    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = ((ll) a[where[i]][m] * binpow(round(a[where[i]][i]),MOD - 2,MOD)) % MOD;
 
    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}
