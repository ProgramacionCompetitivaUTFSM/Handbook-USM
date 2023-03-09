int N; vector<int> A;
vector<vector<int>> DP, OPT;

int main()
{
    DP.assign(N + 1, vi(N + 1));
    OPT.assign(N + 1, vi(N + 1));

    rep(i, N) DP[i][i + 1] = A[i + 1] - A[i], OPT[i][i + 1] = i;

    repx(d, 2, N + 1) rep(l, N + 1 - d)
    {
        int r = l + d, l_ = OPT[l][r - 1], r_ = OPT[l + 1][r];
        DP[l][r] = 1e9;
        repx(i, l_, r_ + 1)
        {
            int aux = DP[l][i] + DP[i][r] + A[r] - A[l];
            if (aux < DP[l][r]) DP[l][r] = aux, OPT[l][r] = i;
        }
    }
}
