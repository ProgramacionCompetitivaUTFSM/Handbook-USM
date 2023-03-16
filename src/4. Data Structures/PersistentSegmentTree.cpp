template<class T, T _m(T, T)>
struct persistent_segment_tree {
    vector<T> ST; vector<int> L, R;
    int n, rt;
    persistent_segment_tree(int n): ST(1, T()),L(1, 0),R(1, 0), n(n), rt(0){}
    int new_node(T v, int l = 0, int r = 0){
        int ks = ST.size();
        ST.push_back(v); L.push_back(l); R.push_back(r);
        return ks;
    }
    int update(int k, int l, int r, int p, T v){
        int ks = new_node(ST[k], L[k], R[k]);
        if (l == r) {
            ST[ks] = v;
            return ks;
        }
        int m = (l + r) / 2, ps;
        if (p <= m) {
            ps = update(L[ks], l, m, p, v);
            L[ks] = ps;
        }
        else {
            ps = update(R[ks], m + 1, r, p, v);
            R[ks] = ps;
        }
        ST[ks] = _m(ST[L[ks]], ST[R[ks]]);
        return ks;
    }
    int query(int k, int l, int r, int a, int b){
        if (l >= a and r <= b)
            return ST[k];
        int m = (l + r) / 2;
        if (b <= m)
            return query(L[k], l, m, a, b);
        if (a > m)
            return query(R[k], m + 1, r, a, b);
        return _m(query(L[k], l, m, a, b), query(R[k], m + 1, r, a, b));
    }
    int update(int k, int p, int v){
        return rt = update(k, 0, n - 1, p, v);
    }
    int update(int p, int v){
        return update(rt, p, v);
    }
    int query(int k, int a, int b){
        return query(k, 0, n - 1, a, b);
    }
};
