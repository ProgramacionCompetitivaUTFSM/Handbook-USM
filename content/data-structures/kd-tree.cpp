/*
 *Description:* given an array of $n$ points, it answers the minimum manhattan distance from the query point in $O(3^{d}log(n))$
 *Status:* Tested on CSES
 */
template<class T, int d>
struct pt {
    array<T,d> p;
    bool operator!=(const pt &o) const { return p != o.p; }
    T dist(const pt &o) const {
        T res = 0;
        for (int i = 0; i < d; i++)
            res += abs(p[i] - o.p[i]);
        return res;
    }
};
template<class pt, class T, int d>
struct kd_tree {
    struct node {
        int ax; T val; pt p;
        node *izq, *der;
        array<T, d> mn, mx;
    };
    node *root;
    T mn_dist(const pt &q, const array<T,d> & mnb, const array<T, d> &mxb) {
        T dist = 0;
        for (int i = 0; i < d; i++) {
            if (q.p[i] < mnb[i]) dist += mnb[i]-q.p[i];
            else if (q.p[i] > mxb[i]) dist += q.p[i]-mxb[i];
        }
        return dist;
    }
    node *build_tree(vector<pt> &a, int l, int r) {
        if (l > r) return nullptr;
        node *cur = new node();
        array<T, d> minb, maxb;
        for (int i = 0; i < d; i++) {
            minb[i] = a[l].p[i];
            maxb[i] = a[l].p[i];
        }
        for (int j = l + 1; j <= r; j++) {
            for (int i = 0; i < d; i++) {
                if (a[j].p[i] < minb[i]) minb[i] = a[j].p[i];
                if (a[j].p[i] > maxb[i]) maxb[i] = a[j].p[i];
            }
        }
        cur->mn = minb; cur->mx = maxb; int ax = 0;
        T mxld = 0;
        for (int i = 0; i < d; i++) {
            T ld = maxb[i]-minb[i];
            if (ld > mxld) {
                mxld = ld;
                ax = i;
            }
        }
        cur->ax = ax; int mid = (l+r)/2;
        nth_element(a.begin() + l, a.begin() + mid, a.begin() + r + 1, [ax](const pt &x, const pt &y) {
            return x.p[ax] < y.p[ax];
        });
        cur->p = a[mid]; cur->val = a[mid].p[ax];
        cur->izq = build_tree(a, l, mid - 1);
        cur->der = build_tree(a, mid + 1, r);
        return cur;
    }
    kd_tree(vector<pt> &a) {
        root = build_tree(a, 0, a.size() - 1);
    }
    void query(node *cur, const pt &q, T &ans) {
        if (cur == nullptr) return;
        if (q != cur->p) {
            T d_here = q.dist(cur->p);
            if (d_here < ans)
                ans = d_here;
        } else {
            ans = min(ans, (T)0);
        }
        vector<pair<T, node *>> ch;
        if (cur->izq) {
            T d_izq = mn_dist(q, cur->izq->mn, cur->izq->mx);
            ch.push_back({d_izq, cur->izq});
        }
        if (cur->der) {
            T d_der = mn_dist(q, cur->der->mn, cur->der->mx);
            ch.push_back({d_der, cur->der});
        }
        sort(ch.begin(), ch.end(), [](const auto &a, const auto &b) {
            return a.first < b.first;
        });
        for (auto &[d_val, to] : ch) 
            if (d_val < ans) query(to, q, ans);
    }
    T query(const pt &q) {
        T ans = numeric_limits<T>::max();
        query(root, q, ans);
        return ans;
    }
};
 