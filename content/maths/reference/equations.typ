*Quadratic:*
$ a x^2 + b x + c = 0 arrow.double x = (-b plus.minus sqrt(b^2 - 4a c)) / (2a), quad "extremum at" x = -b / (2a) $

*Linear system 2x2:*
$ cases(a x + b y = e, c x + d y = f) arrow.double x = (e d - b f)/(a d - b c), quad y = (a f - e c)/(a d - b c) $

*Cramer's rule:* Given $A bold(x) = bold(b)$, then $x_i = det(A_i') \/ det(A)$ where $A_i'$ is $A$ with $i$-th column replaced by $bold(b)$.

*Recurrences:* If $a_n = c_1 a_(n-1) + dots.c + c_k a_(n-k)$ and $r_1, dots, r_k$ are distinct roots of $x^k - c_1 x^(k-1) - dots.c - c_k$, then:
$ a_n = d_1 r_1^n + dots.c + d_k r_k^n $
Non-distinct root $r$ becomes polynomial factor, e.g. $a_n = (d_1 n + d_2) r^n$.
