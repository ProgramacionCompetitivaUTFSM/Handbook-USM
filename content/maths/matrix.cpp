/*
 *Author:* Carlos Lagos
 *Description:* Matrix and their operations
 *Status:* ??
*/

template<class T>
vector<vector<T>> multWithoutMOD(vector<vector<T>> &a, vector<vector<T>> &b){
    int n = a.size(),m = b[0].size(),l = a[0].size();
    vector<vector<T>> ans(n,vector<T>(m,0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            for(int k = 0; k < l; k++){
                ans[i][j] += a[i][k]*b[k][j];
            }
        }
    }
    return ans;
}

template<class T>
vector<vector<T>> mult(vector<vector<T>> a, vector<vector<T>> b,long long mod){
    int n = a.size(),m = b[0].size(),l = a[0].size();
    vector<vector<T>> ans(n,vector<T>(m,0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            for(int k = 0; k < l; k++){
                T temp = (a[i][k]*b[k][j]) % mod;
                ans[i][j] = (ans[i][j] + temp) % mod;
            }
        }
    }
    /*
    for(auto &line: ans)
        for(T &a: line) a = (a % mod + mod) % mod;
    */
    return ans;
}

vector<vector<ll>> binpow(vector<vector<ll>> v,ll n,long long mod){
    ll dim = v.size(); vector<vector<ll>> ans(dim,vector<ll>(dim,0));
    for(ll i = 0; i < dim; i++) ans[i][i] = 1;
    while(n){
        if(n & 1) ans = mult(ans,v,mod);
        v = mult(v,v,mod);
        n = n >> 1;
    }
    return ans;
}