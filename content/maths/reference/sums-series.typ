*Geometric sum:*
$ c^a + c^(a+1) + dots.c + c^b = (c^(b+1) - c^a) / (c - 1), quad c eq.not 1 $

*Power sums:*
$ sum_(i=1)^n i = (n(n+1)) / 2 $
$ sum_(i=1)^n i^2 = (n(2n+1)(n+1)) / 6 $
$ sum_(i=1)^n i^3 = (n^2 (n+1)^2) / 4 $
$ sum_(i=1)^n i^4 = (n(n+1)(2n+1)(3n^2+3n-1)) / 30 $

*Taylor series:*
$ e^x = 1 + x + x^2 / (2!) + x^3 / (3!) + dots.c quad (-infinity < x < infinity) $
$ ln(1+x) = x - x^2 / 2 + x^3 / 3 - x^4 / 4 + dots.c quad (-1 < x lt.eq 1) $
$ sqrt(1+x) = 1 + x / 2 - x^2 / 8 + (2 x^3) / 32 - dots.c quad (-1 lt.eq x lt.eq 1) $
$ sin x = x - x^3 / (3!) + x^5 / (5!) - x^7 / (7!) + dots.c $
$ cos x = 1 - x^2 / (2!) + x^4 / (4!) - x^6 / (6!) + dots.c $

*XOR from 1 to n:*
$ f(n) := cases(
  n     " if " n mod 4 = 0,
  1     " if " n mod 4 = 1,
  n + 1 " if " n mod 4 = 2,
  0     " if " n mod 4 = 3,
) $
