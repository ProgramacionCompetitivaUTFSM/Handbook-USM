#include <bits/stdc++.h>
using namespace std;
 
#define ll long long 
#define ar array
#define rep(i, n) for(int i = 0; i<(int)n; ++i)
#define repx(i, a ,b) for(int i = (int)a; i<(int)b; ++i)

const int mxN = 2e5+5, M = 1e9+7;
int n, s, dp[mxN], t[mxN], f[mxN];

int w(int j, int i){ // 
    if(j >= i) return 1e9;  // here is the cost function from (j, i]
    return s*(f[n]-f[j]) + t[i]*(f[i]-f[j]);
}

struct DD{ // index 0 is used as neutral state
    vector<pair<int, int>> v; // (start pos, best k)
    DD() { v.push_back(make_pair(0, 0)); }
    int qry(int i){
        return (--lower_bound(v.begin(), v.end(), make_pair(i+1, 0)))->second;
    }
    void upd(int x){
        for(int i = (int)v.size()-1; i>=0; --i){
            int y = v[i].first, oldk = v[i].second;
            if(y > x && dp[x] + w(x, y) < dp[oldk] + w(oldk, y)) v.pop_back();
            else{
                int l = y+1, r = n+1; 
                while(l < r){
                    int mid = (l+r)/2;
                    if(dp[x] + w(x, mid) < dp[oldk] + w(oldk, mid)) r = mid;
                    else l = mid+1;
                }
                if(r != n+1) v.push_back(make_pair(r, x)); break;
            }
        }
        if(v.size() == 0) v.push_back(make_pair(0, x));
    }
};
    cin >> n >> s;
    DD dd;
    t[0] = f[0] = dp[0] = 0;
    for(int i = 1; i<=n; ++i){
        cin >> t[i] >> f[i]; t[i] += t[i-1]; f[i] += f[i-1];
    }
    for(int i = 1; i<=n; ++i){
        int k = dd.qry(i); dp[i] = dp[k] + w(k, i);dd.upd(i);
    }
    cout << dp[n] << '\n';
// https://vjudge.net/problem/OpenJ_Bailian-1180
