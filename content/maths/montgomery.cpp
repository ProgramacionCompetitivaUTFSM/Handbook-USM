/*
 *Description:*  Optimizes multiplication with large modules, useful for fast_ntt.
 *Status:* Tested on codeforces.
*/
using ll = uint64_t
struct montgomery {
    ll n, nr;
    constexpr montgomery(ll n) : n(n), nr(1) {
        for (int i = 0; i < 6; i++)
            nr *= 2 - n * nr;
    }
    ll reduce(__uint128_t x) const {
        ll q = __uint128_t(x) * nr;
        ll m = ((__uint128_t) q * n) >> 64;
        ll res = (x >> 64) + n - m;
        if (res >= n)
            res -= n;
        return res;
    }
    ll multiply(ll x, ll y) const {
        return reduce((__uint128_t) x * y);
    }
    ll transform(ll x) const {
        return (__uint128_t(x) << 64) % n;
    }
};