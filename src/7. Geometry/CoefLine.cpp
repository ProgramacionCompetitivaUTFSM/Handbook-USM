template< T >
struct CoefLine {
  T A;
  T B;
  T C;
  double EPS;
  CoefLine(double eps) : EPS(eps) {}
  // Line of Segment Integer
  // here we asume that P and Q are only points
  void LSI(Point2D< T > P, Point2D< T > Q){
    // Ax + By + C
    A = P.y - Q.y;
    B = Q.x - P.x;
    C = -1 * A * P.x - B * P.y;
    T gcdABC = gcd(A, gcd(B, C));
    A /= gcdABC;
    B /= gcdABC;
    C /= gcdABC;
    if(A < 0 || (A == 0 && B < 0)) {
      A *= -1;
      B *= -1;
      C *= -1;
    }
    return L;
  }
  T det(T a, T b, T c, T d) {
    return a * d - b * c;
  }
  // Line of Segment Real
  void LSR(Point2D< T > P, Point2D< T > Q, T eps){
    // Ax + By + C
    A = P.y - Q.y;
    B = Q.x - Px;
    C = -1 * A * P.x - B * P.y;
    T z = sqrt(L.A * L.A + L.B * L.B);
    A /= z;
    B /= z;
    C /= z;
    if(A < -1 * eps || (abs(A) < eps && B < -1 * eps)) {
      A *= -1;
      B *= -1;
      C *= -1;
    }
    return L;
  }
  bool intersect(CoefLine l, Point2D &res) {
    double z = det(a, b, l.a, l.b);
    if(abs(z) < EPS) { return false; }
    res.x = -det(c, b, l.c, l.b) / z;
    res.y = -det(a, c, l.a, l.c) / z;
    return true;
  }
  bool parallel(CoefLine l) {
    return abs(det(a, b, l.a, l.b)) < EPS;
  }
  bool equivalent(CoefLine l) {
    return abs(det(a, b, l.a, l.b)) < EPS &&
           abs(det(a, c, l.a, l.c)) < EPS &&
           abs(det(b, c, l.b, l.c)) < EPS;
  }
};

