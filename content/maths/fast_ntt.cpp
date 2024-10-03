/*
 *Description:* Same utility as FFT but with some magic primes, runs in $O(n log n)$ with better constant
  Posible primes and their roots:
    - 998244353, 3
    - 9223372036737335297, 3
    - 2013265921, 31
  requires binpow(be careful with overflow), and montgomery
 *Status:* Tested on codeforces, every prime above
*/
using ll = uint64_t;
template<ll mod, ll gen>
struct fast_ntt {
    fast_ntt() {};
    vector<int> bit_sort(int n) {
        int h = -1;
        vector<int> rev(n, 0);
        int skip = __lg(n) - 1;
        for (int i = 1; i < n; ++i) {
            if (!(i & (i - 1)))
                ++h;
            rev[i] = rev[i ^ (1 << h)] | (1 << (skip - h));
        }
        return rev;
    }
    void ntt(vector<ll>& a, vector<int>& rev, montgomery& red, ll inv_n, ll root, ll inv_root, bool invert) {
        int n = (int)a.size();
        for (int i = 0; i < n; ++i)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        ll w = invert ? inv_root : root;
        vector<ll> W(n >> 1, red.transform(1));
        for (int i = 1; i < (n >> 1); ++i)
            W[i] = red.multiply(W[i-1], w);
        int lim = __lg(n);
        for (int i = 0; i < lim; ++i)
            for (int j = 0; j < n; ++j)
                if (!(j & (1 << i))) {
                    ll t = red.multiply(a[j ^ (1 << i)], W[(j & ((1 << i) - 1)) * (n >> (i + 1))]);
                    a[j ^ (1 << i)] = a[j] >= t ? a[j] - t : a[j] + mod - t;
                    a[j] = a[j] + t < mod ? a[j] + t : a[j] + t - mod;
                }
        if (invert)
            for (int i = 0; i < n; i++)
                a[i] = red.multiply(a[i], inv_n);
    }
    vector<ll> conv(vector<ll> a, vector<ll> b) {
        montgomery red(mod);
        for (auto& x : a)
            x = red.transform(x);
        for (auto& x : b)
            x = red.transform(x);
        int n = 1;
        while (n < a.size() || n < b.size())
            n <<= 1;
        n <<= 1;
        a.resize(n);
        b.resize(n);
        ll inv_n = red.transform(bin_pow(n, mod-2, mod));
        ll root = red.transform(bin_pow(gen, (mod-1)/n, mod));
        ll inv_root = red.transform(bin_pow(red.reduce(root), mod-2, mod));
        auto rev = bit_sort(n);
        ntt(a, rev, red, inv_n, root, inv_root, false);
        ntt(b, rev, red, inv_n, root, inv_root, false);
        for (int i = 0; i < n; i++)
            a[i] = red.multiply(a[i], b[i]);
        ntt(a, rev, red, inv_n, root, inv_root, true);
        for (auto& x : a)
            x = red.reduce(x);
        return a;
    }
};