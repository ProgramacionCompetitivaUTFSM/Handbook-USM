template< T >
// Line of Segment Integer
// here we asume that P and Q are only points
vector< T > LSI(Point2D< T > P, Point2D< T > Q){
  vector< T > L(3, 0);
  // L[0]x + L[1]y + L[2]
  L[0] = P.y - Q.y;
  L[1] = Q.x - Px;
  L[2] = -1 * A * P.x - B * P.y;
  T gcdABC = gcd(L[0], gcd(L[1], L[2]));
  L[0] /= gcdABC;
  L[1] /= gcdABC;
  L[2] /= gcdABC;
  if(L[0] < 0 || (L[0] == 0 && L[1] < 0)) {
    L[0] *= -1;
    L[1] *= -1;
    L[2] *= -1;
  }
  return L;
}

template< T >
// Line of Segment Real
// here we asume that P and Q are only points
vector< T > LSR(Point2D< T > P, Point2D< T > Q, T eps){
  vector< T > L(3, 0);
  // L[0]x + L[1]y + L[2]
  L[0] = P.y - Q.y;
  L[1] = Q.x - Px;
  L[2] = -1 * A * P.x - B * P.y;
  T z = sqrt(L[0] * L[0] + L[1] * L[1]);
  L[0] /= z;
  L[1] /= z;
  L[2] /= z;
  if(L[0] < -1 * eps || (abs(L[0]) < eps && L[1] < -1 * eps)) {
    L[0] *= -1;
    L[1] *= -1;
    L[2] *= -1;
  }
  return L;
}
