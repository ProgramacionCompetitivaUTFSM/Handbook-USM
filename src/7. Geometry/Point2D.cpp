template< T >
struct Point2D {
  T x, y;
  Point2D() {};
  Point2D(T x_, T y_) : x(x_), y(y_) {}
  Point2D& operator+= (const Point2D &t) {
    x += t.x;
    y += t.y;
    return *this;
  }
  Point2D& operator-= (const Point2D &t) {
    x -= t.x;
    y -= t.y;
    return *this;
  }
  Point2D& operator*= (const Point2D &t) {
    x *= t;
    y *= t;
    return *this;
  }
  Point2D& operator/= (const Point2D &t) {
    x /= t;
    y /= t;
    return *this;
  }
  Point2D operator+(const Point2D &t) const {
    return Point2D(*this) += t;
  }
  Point2D operator-(const Point2D &t) const {
    return Point2D(*this) -= t;
  }
  Point2D operator*(T t) const {
    return Point2D(*this) *= t;
  }
  Point2D operator/(T t) const {
    return Point2D(*this) /= t;
  }
};
template< T >
Point2D operator*(T a, Point2D< T > b) {
  return b * a;
}
