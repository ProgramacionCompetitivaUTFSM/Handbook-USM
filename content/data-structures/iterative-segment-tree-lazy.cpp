/*
 *Description:* Segment tree with lazy propagation, but now iterative. Build is $O(n)$, querys and updates are $O(log n)$
 *Status:* Tested
*/
template<class T1,class T2,T1 merge(T1&,T1&),void applyUpd(T1&,T2&,int), void pushUpd(T2&,T2&,int)>
struct segment_tree_lazy {
    int n,h; vector<T1> st; vector<T2> lazy;
    segment_tree_lazy(vector<T1> & a){
        n = a.size(); h = sizeof(int)*8-__builtin_clz(n);
        st.resize(n<<1); lazy.resize(n);
        for (int i = 0; i < n; i++) st[n+i] = a[i];
        for (int i = n-1; i > 0; i--) st[i] = merge(st[i<<1],st[i<<1|1]);
    }
    void calc(int pos, int sz){
        if (lazy[pos].upd()) applyUpd(st[pos],lazy[pos],sz);
        else st[pos] = merge(st[pos<<1],st[pos<<1|1]);
    }
    void apply(int pos, T2 val, int sz){
        applyUpd(st[pos],val,sz);
        if (pos < n) pushUpd(val,lazy[pos],sz);
    }
    void build(int l, int r){
        int sz = 2;
        for (l += n, r += n-1; l > 1; sz <<= 1){
            l >>= 1, r >>= 1;
            for (int i = r; i >= l; i--)
                apply(i,sz);
        }
    }
    void push(int l, int r){
        int s = h, sz = 1<<(h-1);
        for (l += n, r += n-1; s > 0; s--, sz >>= 1)
            for (int i = l>>s; i <= r>>s; i++) if (lazy[i].upd()){
                apply(i<<1,lazy[i],sz);
                apply(i<<1|1,lazy[i],sz);
                lazy[i] = T2();
            }
    }
    void update(int l, int r, T2 val){
        push(l,l+1); push(r,r+1);
        bool cl = 0, cr = 0; int sz = 1;
        for (l += n, r += n+1; l < r; l >>= 1, r >>= 1, sz <<= 1){
            if (cl) calc(l-1,sz);
            if (cr) calc(r,sz);
            if (l&1) apply(l++,val,sz), cl = 1;
            if (r&1) apply(--r,val,sz), cr = 1;
        }
        for (--l; r > 0; l >>= 1, r >>= 1, sz <<= 1){
            if (cl) calc(l,sz);
            if (cr && (!cl || l != r)) calc(r,sz);
        }
    }
    T1 query(int l, int r){
        push(l,l+1); push(r,r+1);
        T1 ansL, ansR; bool hasL = 0,hasR = 0;
        for (l += n, r += n+1; l < r; l >>= 1, r >>= 1){
            if (l&1) ansL = (hasL?merge(ansL,st[l++]):st[l++]), hasL = 1; 
            if (r&1) ansR = (hasR?merge(st[--r],ansR):st[--r]), hasR = 1; 
        }
        if (!hasL) return ansR; if (!hasR) return ansL;
        return merge(ansL,ansR);
    }
};
/* example of use */
struct lz {
    ll val;
    lz(){ val = 0; }
    bool upd(){ return (val != 0); }
};
ll merge(ll & a, ll & b){
    return a+b;
}
void applyUpd(ll & v, lz & u, int sz){
    v += u.val*((ll)sz);
}
void pushUpd(lz & u1, lz & u2, int sz){
    u2.val += u1.val;
}