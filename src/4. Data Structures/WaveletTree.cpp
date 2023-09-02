class WT {
    typedef vi::iterator iter;
    vvi r0; vi arrCopy;
    int n, s;
    void build(iter b, iter e, int l, int r, int u) {
        if (l == r) return;
        int m = (l + r) / 2;
        r0[u].reserve(e - b + 1); r0[u].pb(0);
        for (iter it = b; it != e; ++it)
            r0[u].pb(r0[u].back() + (*it <= m));
        iter p = stable_partition(b, e, [=](int i) { return i <= m; });
        build(b, p, l, m, u * 2); build(p, e, m + 1, r, u * 2 + 1);
    }
    int q, w;
    int range(int a, int b, int l, int r, int u) {
        if (r < q or w < l) return 0;
        if (q <= l && r <= w) return b - a;
        int m = (l + r) / 2, za = r0[u][a], zb = r0[u][b];
        return range(za, zb, l, m, u * 2) +
               range(a - za, b - zb, m + 1, r, u * 2 + 1);
    }
public:
    WT(vi arr, int sigma) { // arr[i] in [0,sigma)
        n = sz(arr); s = sigma; r0.resize(s * 2);
        arrCopy = arr;
        build(all(arr), 0, s - 1, 1);
    }
    // k in [1,n], [a,b) is 0-indexed, -1 if error
    int quantile(int k, int a, int b) {
        // extra conditions disabled
        if (/*a < 0 or b > n or*/ k < 1 or k > b - a) return -1;
        int l = 0, r = s - 1, u = 1, m, za, zb;
        while (l != r) {
            m = (l + r) / 2;
            za = r0[u][a], zb = r0[u][b], u *= 2;
            if (k <= zb - za) a = za, b = zb, r = m;
            else k -= zb - za, a -= za, b -= zb, l = m + 1, ++u;
        }
        return r;
    }
    // counts numbers in [x,y] in positions [a,b)
    int range(int x, int y, int a, int b) {
        if (y < x or b <= a) return 0;
        q = x, w = y;
        return range(a, b, 0, s - 1, 1);
    }
    // count occurrences of x in positions [0,k)
    int rank(int x, int k) {
        int l = 0, r = s - 1, u = 1, m, z;
        while (l != r) {
            m = (l + r) / 2;
            z = r0[u][k], u *= 2;
            if (x <= m) k = z, r = m;
            else k -= z, l = m + 1, ++u;
        }
        return k;
    }
    // x in [0,sigma)
    void pb(int x) {
        int l = 0, r = s - 1, u = 1, m, p; ++n;
        while (l != r) {
            m = (l + r) / 2;
            p = (x <= m);
            r0[u].pb(r0[u].back() + p);
            u *= 2;
            if (p) r = m;
            else l = m + 1, ++u;
        }
    }
    void pop_back() { // doesn't check if empty
        int l = 0, r = s - 1, u = 1, m, p, k; --n;
        while (l != r) {
            m = (l + r) / 2;
            k = sz(r0[u]), p = r0[u][k - 1] - r0[u][k - 2];
            r0[u].pop_back();
            u *= 2;
            if (p) r = m;
            else l = m + 1, ++u;
        }
    }
    void swap_adj(int i) { // swap arr[i] with arr[i+1], i in [0,n-1)
        int &x = arrCopy[i], &y = arrCopy[i + 1];
        int l = 0, r = s - 1, u = 1;
        while (l != r) {
            int m = (l + r) / 2, p = (x <= m), q = (y <= m);
            if (p != q) {
                r0[u][i + 1] ^= r0[u][i] ^ r0[u][i + 2];
                break;
            }
            u *= 2;
            if (p) r = m;
            else l = m + 1, ++u;
        }
        swap(x, y);
    }
};
