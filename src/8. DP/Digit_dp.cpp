int dp[12][12][2]; // dp[i][s][f] {i: posicion, s: estado del problema, f: act < s}
int k, d;

// solve(r) - solve(l-1)
int call(int pos, int cnt, int f){
    if(cnt > k) return 0;
    if(pos == num.size()){
        if(cnt == k) return 1;
        return 0;
    }
    if(dp[pos][cnt][f] != -1) return dp[pos][cnt][f];
    int res = 0, LMT;
    if(f == 0) LMT = num[pos];
    else LMT = 9;
    /// Try to place all the valid digits such that the number doesn't exceed b
    for(int dgt = 0; dgt<=LMT; dgt++){
        int nf = f, ncnt = cnt;
        if(f == 0 && dgt < LMT) nf = 1; /// The number is getting smaller at this position
        if(dgt == d) ncnt++;
        if(ncnt <= k) res += call(pos+1, ncnt, nf);
    }
    return dp[pos][cnt][f] = res;
}
int solve(string s){
    num.clear();
    while(s.size()){
        num.push_back((s.back()-'0')%10);
        s.pop_back();
    }
    reverse(num.begin(), num.end());
    memset(dp, -1, sizeof(dp));
    return call(0, 0, 0);
}
