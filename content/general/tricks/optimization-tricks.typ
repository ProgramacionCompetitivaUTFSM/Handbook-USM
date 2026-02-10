`__builtin_ia32_ldmxcsr(40896);` disables denormals (which make floats 20x slower near their minimum value).

*Bit hacks:*
- `x & -x` is the least significant bit of `x`.
- `for (int x = m; x; ) { --x &= m; ... }` loops over all subset masks of `m` (except `m` itself).
- `c = x&-x, r = x+c; (((r^x) >> 2)/c) | r` is the next number after `x` with the same popcount.
- Subset sum over all bitmasks in $O(2^K)$:
```cpp
rep(b,0,K) rep(i,0,(1 << K))
  if (i & 1 << b) D[i] += D[i^(1 << b)];
```

*Pragmas:*
- `#pragma GCC optimize ("Ofast")` — auto-vectorize loops, optimize floats.
- `#pragma GCC target ("avx2")` — can double vectorized performance (crashes on old machines).
- `#pragma GCC optimize ("trapv")` — kills program on integer overflows (slow).
