template<class T>
class Hungarian {
    T inf = numeric_limits<T>::max() / 2;
    bool maxi, swapped = false;
    vector<vector<T>> cost;
    vector<T> u, v;
    vector<int> p, way;
    int l, r;
 
  public:
    // left/right == partition sizes
    Hungarian(int left, int right, bool maximizing) {
        l = left, r = right, maxi = maximizing;
        if (swapped = l > r) swap(l, r);
        cost.assign(l + 1, vector<T>(r + 1, 0));
        u.assign(l + 1, 0); v.assign(r + 1, 0);
        p.assign(r + 1, 0); way.assign(r + 1, 0);
    }
    void add_edge(int l, int r, T w) {
        assert(l and r);  // indices start from 1 !!
        if (swapped) swap(l, r);
        cost[l][r] = maxi ? -w : w;
    }
    // execute after all edges were added
    void calculate() {
        for (int i = 1; i <= l; i++) {
            vector<bool> used(r+1, false);
            vector<T> minv(r+1, inf);
            int j0 = 0; p[0] = i;
 
            while (p[j0]) {
                int j1, i0 = p[j0]; used[j0] = true;
                T delta = inf;
                for (int j = 1; j <= r; j++)
                  if (not used[j]) {
                    T cur = cost[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) minv[j] = cur, way[j] = j0;
                    if(minv[j] < delta) delta = minv[j], j1 = j;
                }
                for (int j = 0; j <= r; j++) {
                    if (used[j]) u[p[j]] += delta, v[j] -= delta;
                    else minv[j] -= delta;
                }
                j0 = j1;
            }
            while (j0) p[j0] = p[way[j0]], j0 = way[j0];
        }
    }
    // execute after executing calculate()
    T answer() { return maxi ? v[0] : -v[0]; }
    bool are_matched(int l, int r) {
        if (swapped) swap(l, r);
        return p[r] == l;
    }
};
