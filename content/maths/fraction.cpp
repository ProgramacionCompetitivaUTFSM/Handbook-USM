/*
  *Description:* Just a fraction, every operation runs on $O(log(min(p, q)))$
  *Status:* Not tested
*/
template <typename T = ll>
struct Fraction {
  T p, q;
  Fraction() {}
  Fraction(T p, T q): p(p), q(q) {
    if (q < 0) this->p = -p, this->q = -q;
  }
  bool operator<(const Fraction o) const {
    return (ll)p*o.q < (ll)o.p*q;
  }
  Fraction simplify(Fraction f){
    T g = __gcd(f.p, f.q);
    return Fraction(f.p/g, f.q/g);
  }
  Fraction add(Fraction f){
    T l = q / __gcd(q, f.q) * f.q;
    T np = p * (l/q) + f.p * (l/f.q);
    return simplify(Fraction(np, l));
  }
};