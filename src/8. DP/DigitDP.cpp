int dp[12][12][2]; // dp[i][s][f] {i: posicion, s: estado del problema, f: act < s}
int k, d;

int call(int pos, int cnt, int f) {
    if (cnt > k) return 0;
    if (pos == num.size()) return (cnt == k) ? 1 : 0;
    if (dp[pos][cnt][f] != -1) return dp[pos][cnt][f];
    int res = 0, LMT = (f == 0) ? num[pos] : 9;
    for (int dgt = 0; dgt <= LMT; dgt++) {
        int nf = f, ncnt = cnt + (dgt == d);
        if (f == 0 && dgt < LMT) nf = 1;
        res += call(pos + 1, ncnt, nf);
    }
    return dp[pos][cnt][f] = res;
}

int solve(string s) {
    num.clear();
    for (char c : s) num.push_back((c - '0') % 10);
    reverse(num.begin(), num.end());
    memset(dp, -1, sizeof(dp));
    return call(0, 0, 0);
}
