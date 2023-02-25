template< T >
struct Point2D {
  T x, y;
  Point2D() {};
  Point2D(T x_, T y_) : x(x_), y(y_) {}
  Point2D< T >& operator=(const Point2D< T > &t) {
    x = t.x;
    y = t.y;
    return * this;
  }
  Point2D< T >& operator+= (const Point2D< T > &t) {
    x += t.x;
    y += t.y;
    return *this;
  }
  Point2D< T >& operator-= (const Point2D< T > &t) {
    x -= t.x;
    y -= t.y;
    return *this;
  }
  Point2D< T >& operator*= (const Point2D< T > &t) {
    x *= t;
    y *= t;
    return *this;
  }
  Point2D< T >& operator/= (const Point2D< T > &t) {
    x /= t;
    y /= t;
    return *this;
  }
  Point2D< T > operator+(const Point2D< T > &t) const {
    return Point2D(*this) += t;
  }
  Point2D< T > operator-(const Point2D< T > &t) const {
    return Point2D(*this) -= t;
  }
  Point2D< T > operator*(T t) const {
    return Point2D(*this) *= t;
  }
  Point2D< T > operator/(T t) const {
    return Point2D(*this) /= t;
  }
  T dot(Point2D< T >& b) {
    return x * b.x + a.y * b.y;
  }
  T cross(Point2D< T >& b) {
    return x * b.y - a.y * a.x;
  }
  T norm() {
    return dot(*this);
  }
  double abs() {
    return sqrt(norm());
  }
  double proj(Point2D< T >& b) {
    return dot(b) / b.abs();
  }
  double angle(Point2D< T >& b) {
    return acos(dot(b) / abs() / b.abs());
  }
};
template< T >
Point2D< T > operator*(T a, Point2D< T > b) {
  return b * a;
}
