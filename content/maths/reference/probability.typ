*Expected value and variance:*
$ mu = EE(X) = sum_x x p_X (x), quad sigma^2 = V(X) = EE(X^2) - (EE(X))^2 $
$ EE(a X + b Y) = a EE(X) + b EE(Y) $
For independent $X, Y$: $V(a X + b Y) = a^2 V(X) + b^2 V(Y)$.

*Binomial* $"Bin"(n, p)$: #h(1em) $n$ independent yes/no trials, each with probability $p$.
$ p(k) = binom(n, k) p^k (1-p)^(n-k), quad mu = n p, quad sigma^2 = n p(1-p) $

*First success* $"Fs"(p)$: #h(1em) Trials until first success.
$ p(k) = p(1-p)^(k-1), quad mu = 1 / p, quad sigma^2 = (1-p) / p^2 $

*Poisson* $"Po"(lambda)$: #h(1em) Events in fixed time, average rate $lambda$.
$ p(k) = e^(-lambda) lambda^k / (k!), quad mu = lambda, quad sigma^2 = lambda $

*Uniform* $"U"(a, b)$:
$ f(x) = 1 / (b - a) "for" a < x < b, quad mu = (a+b) / 2, quad sigma^2 = (b-a)^2 / 12 $

*Exponential* $"Exp"(lambda)$:
$ f(x) = lambda e^(-lambda x) "for" x gt.eq 0, quad mu = 1 / lambda, quad sigma^2 = 1 / lambda^2 $

*Normal* $cal(N)(mu, sigma^2)$:
$ f(x) = 1 / sqrt(2 pi sigma^2) e^(-(x - mu)^2 / (2 sigma^2)) $
$a X_1 + b X_2 + c tilde cal(N)(a mu_1 + b mu_2 + c, thin a^2 sigma_1^2 + b^2 sigma_2^2)$

*Markov chains:* Transition $bold(P) = (p_(i j))$, $bold(p)^((n)) = bold(P)^n bold(p)^((0))$.

Stationary: $bold(pi) = bold(pi P)$. If irreducible: $pi_i = 1 \/ EE(T_i)$. Connected undirected non-bipartite graph with uniform transitions: $pi_i prop deg(i)$. Ergodic iff irreducible and aperiodic.

Absorption: $a_(i j) = p_(i j) + sum_(k in bold(G)) a_(i k) p_(k j)$, #h(1em) $t_i = 1 + sum_(k in bold(G)) p_(k i) t_k$.
