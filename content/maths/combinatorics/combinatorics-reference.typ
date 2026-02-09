*Derangements:* Permutations where no element is in its original position.
$ D(n) = (n-1)(D(n-1) + D(n-2)) = n D(n-1) + (-1)^n = floor(n! / e) $

*Burnside's lemma:* Given a group $G$ of symmetries and a set $X$, the number of elements of $X$ up to symmetry equals:
$ 1 / (|G|) sum_(g in G) |X^g| $
where $X^g$ are elements fixed by $g$. For rotational symmetry with $G = ZZ_n$:
$ g(n) = 1 / n sum_(k | n) f(k) phi(n \/ k) $

*Partition function:* Ways to write $n$ as sum of positive integers (order irrelevant).
$ p(0) = 1, quad p(n) = sum_(k in ZZ without {0}) (-1)^(k+1) p(n - k(3k-1) \/ 2) $
$ p(n) tilde 0.145 / n dot e^(2.56 sqrt(n)) $

#table(
  columns: 14,
  stroke: 0.5pt,
  align: center,
  $n$, $0$, $1$, $2$, $3$, $4$, $5$, $6$, $7$, $8$, $9$, $20$, $50$, $100$,
  $p(n)$, $1$, $1$, $2$, $3$, $5$, $7$, $11$, $15$, $22$, $30$, $627$, [~2e5], [~2e8],
)

*Lucas' theorem:* For prime $p$, write $n = sum n_i p^i$, $m = sum m_i p^i$:
$ binom(n, m) equiv product_(i=0)^k binom(n_i, m_i) quad (mod p) $

*Multinomial:* $binom(n, k_1, k_2, dots, k_m) = n! / (k_1! k_2! dots.c k_m!)$
