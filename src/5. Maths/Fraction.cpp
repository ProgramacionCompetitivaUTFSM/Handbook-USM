template <typename T>
struct Fraction {
  T p, q;
  Fraction() {}
  Fraction(T p, T q): p(p), q(q) {
    if (q < 0) this->p = -p, this->q = -q;
  }
  bool operator<(const Fraction o) {
    return p*o.q < o.p*q;
  }
  Fraction simplify(Fraction f){
    ll g = gcd(f.p, f.q);
    return Fraction(f.p/g, f.q/g);
  }
  Fraction add(Fraction f){
    ll l = lcm(q, f.q);
    p *= (l/q);
    p += f.p * (l/f.q);
    return simplify(Fraction(p, l));
  }
};
