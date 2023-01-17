struct Fraction {
  ll numerator, denominator;
  Fraction(ll a, ll b){
    numerator = a, denominator = b;
  }
  Fraction simplify(Fraction f){
    ll g = gcd(f.numerator, f.denominator);
    return Fraction(f.numerator/g, f.denominator/g);
  }
  Fraction add(Fraction f){
    ll l = lcm(denominator, f.denominator);
    numerator *= (l/denominator);
    numerator += f.numerator * (l/f.denominator);
    return simplify(Fraction(numerator, l));
  }
};
