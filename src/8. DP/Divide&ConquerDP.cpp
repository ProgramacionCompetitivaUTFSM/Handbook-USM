// dp(i, j) = min dp(i-1,k-1) + C(k,j) for all k in [0, j]
// C(a,c) + C(b, d) <= C(a,d) + C(b,c) for all a <= b <= c <= d
vp c;
vl acum1, acum2;

ll cost(ll i, ll j) {
  return c[j].first * (acum1[j+1] - acum1[i]) - (acum2[j+1] - acum2[i]);
}

vector<ll> last, now;

void compute(int l, int r, int optl, int optr) {
    if (l > r) return;

    int mid = (l + r) / 2;
    pair<ll, int> best = {cost(0, mid), -1};

    for(int k = max(1, optl); k < min(mid, optr) + 1; k++)
        best = min(best, {last[k - 1] + cost(k, mid), k});

    now[mid] = best.first;

    compute(l, mid - 1, optl, best.second);
    compute(mid + 1, r, best.second, optr);
}
