struct UnionFind {
    vector<int> p, r;
    UnionFind(int n) {
        r.assign(n+1, 0);
        p.assign(n+1, 0);
        for(int i=1; i<=n; i++) p[i] = i;
    }
    int findSet(int i) {
        return (p[i] == i)? i:(p[i] = findSet(p[i]));
    }
    bool isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }
    void unionSet(int i, int j) {
        if (!isSameSet(i, j)) {
            int x = findSet(i), y = findSet(j);
            if (r[x] > r[y]) p[y] = x;
            else {
                p[x] = y;
                if (r[x] == r[y]) r[y]++;
            }
        }
    }
};