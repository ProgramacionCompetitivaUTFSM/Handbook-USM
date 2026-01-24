"""
  *Description:* Berlekamp-Massey algorithm to find the shortest LFSR for a sequence
  *Status:* Tested
"""
from fractions import Fraction

def bm(s):
  s = [Fraction(x) for x in s]
  C, B, m, b = [Fraction(1)], [Fraction(1)], 1, Fraction(1)
  for i in range(len(s)):
    d = sum(C[j]*s[i-j] for j in range(len(C)))
    if d:
      T, coef = C[:], d/b
      C += [Fraction(0)]*(len(B)+m-len(C))
      for j in range(len(B)): C[j+m] -= coef*B[j]
      if 2*(len(T)-1) <= i: B, b, m = T, d, 1
      else: m += 1
    else: m += 1
  return [-c for c in C[1:]]
