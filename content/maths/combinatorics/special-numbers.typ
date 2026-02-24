*Bernoulli numbers:* EGF: $B(t) = t \/ (e^t - 1)$.

#table(
  columns: 8,
  stroke: 0.5pt,
  align: center,
  $B_0$, $B_1$, $B_2$, $B_3$, $B_4$, $B_5$, $B_6$, $dots$,
  $1$, $-1/2$, $1/6$, $0$, $-1/30$, $0$, $1/42$, [],
)

Sums of powers:
$ sum_(i=1)^n n^m = 1 / (m+1) sum_(k=0)^m binom(m+1, k) B_k dot (n+1)^(m+1-k) $

Euler-Maclaurin formula:
$ sum_(i=m)^infinity f(i) approx integral_m^infinity f(x) dif x + f(m) / 2 - (f'(m)) / 12 + (f'''(m)) / 720 + O(f^((5))(m)) $

*Stirling 1st kind:* Permutations on $n$ items with $k$ cycles.
$ c(n,k) = c(n-1, k-1) + (n-1) c(n-1, k), quad c(0,0) = 1 $
$ sum_(k=0)^n c(n,k) x^k = x(x+1) dots.c (x+n-1) $

*Eulerian numbers:* Permutations of $S_n$ with exactly $k$ ascents.
$ E(n,k) = (n-k) E(n-1, k-1) + (k+1) E(n-1, k) $
$ E(n,0) = E(n, n-1) = 1 $

*Stirling 2nd kind:* Partitions of $n$ distinct elements into exactly $k$ groups.
$ S(n,k) = S(n-1, k-1) + k S(n-1, k), quad S(n,1) = S(n,n) = 1 $
$ S(n,k) = 1 / (k!) sum_(j=0)^k (-1)^(k-j) binom(k, j) j^n $

*Bell numbers:* Total partitions of $n$ distinct elements. $B(n) = 1, 1, 2, 5, 15, 52, 203, 877, 4140, dots$

For $p$ prime: $B(p^m + n) equiv m B(n) + B(n+1) (mod p)$

*Labeled unrooted trees:* \#on $n$ vertices: $n^(n-2)$. \#on $k$ trees of size $n_i$: $n_1 n_2 dots.c n_k n^(k-2)$. \#with degrees $d_i$: $(n-2)! / ((d_1 - 1)! dots.c (d_n - 1)!)$

*Catalan numbers:*
$ C_n = 1 / (n+1) binom(2n, n) = binom(2n, n) - binom(2n, n+1) = ((2n)!) / ((n+1)! n!) $
$ C_0 = 1, quad C_(n+1) = (2(2n+1)) / (n+2) C_n, quad C_(n+1) = sum_(i=0)^n C_i C_(n-i) $
$C_n = 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, dots$

- Sub-diagonal monotone paths in $n times n$ grid
- Strings with $n$ pairs of correctly nested parentheses
- Binary trees with $n+1$ leaves (0 or 2 children)
- Ordered trees with $n+1$ vertices
- Triangulations of convex polygon with $n+2$ sides
- Permutations of $[n]$ with no 3-term increasing subseq
