/*
 *Description:* Adaptive Simpson's rule for numerical integration. Error proportional to $h^4$.
 *Status:* KACTL based, not self tested
*/
template<class F>
ld simpsonRec(F& f, ld a, ld b,
    ld eps, ld S) {
  ld c = (a+b)/2;
  ld S1 = (f(a)+4*f((a+c)/2)+f(c))*(c-a)/6;
  ld S2 = (f(c)+4*f((c+b)/2)+f(b))*(b-c)/6;
  ld T = S1+S2;
  if (abs(T-S) <= 15*eps || b-a < 1e-10)
    return T + (T-S)/15;
  return simpsonRec(f, a, c, eps/2, S1)
       + simpsonRec(f, c, b, eps/2, S2);
}
template<class F>
ld integrate(ld a, ld b, F f,
    ld eps = 1e-8) {
  ld S = (f(a)+4*f((a+b)/2)+f(b))*(b-a)/6;
  return simpsonRec(f, a, b, eps, S);
}
