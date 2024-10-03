/*
 *Description:*  Optimizes multiplication with large modules, useful for fast_ntt.
 *Status:* Tested on codeforces.
*/
using ull = uint64_t
struct montgomery {
    ull n, nr;
    constexpr montgomery(ull n) : n(n), nr(1) {
        for (int i = 0; i < 6; i++)
            nr *= 2 - n * nr;
    }
    ull reduce(__uint128_t x) const {
        ull q = __uint128_t(x) * nr;
        ull m = ((__uint128_t) q * n) >> 64;
        ull res = (x >> 64) + n - m;
        if (res >= n)
            res -= n;
        return res;
    }
    ull multiply(ull x, ull y) const {
        return reduce((__uint128_t) x * y);
    }
    ull transform(ull x) const {
        return (__uint128_t(x) << 64) % n;
    }
};