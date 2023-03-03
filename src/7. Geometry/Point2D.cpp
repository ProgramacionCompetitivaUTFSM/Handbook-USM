template<typename T>
struct Point2D {
  T x, y;
  Point2D() {};
  Point2D(T x_, T y_) : x(x_), y(y_) {}
  Point2D< T >& operator=(Point2D< T > t) {
    x = t.x; y = t.y;
    return *this;
  }
  Point2D< T >& operator+=(Point2D< T > t) {
    x += t.x; y += t.y;
    return *this;
  }
  Point2D< T >& operator-=(Point2D< T > t) {
    x -= t.x; y -= t.y;
    return *this;
  }
  Point2D< T >& operator*=(Point2D< T > t) {
    x *= t.x; y *= t.y;
    return *this;
  }
  Point2D< T >& operator/=(Point2D< T > t) {
    x /= t.y; y /= t.y;
    return *this;
  }
  Point2D< T > operator+(Point2D< T > t) {
    return Point2D(*this) += t;
  }
  Point2D< T > operator-(Point2D< T > t) {
    return Point2D(*this) -= t;
  }
  Point2D< T > operator*(T t) {
    return Point2D(*this) *= t;
  }
  Point2D< T > operator/(T t) {
    return Point2D(*this) /= t;
  }
  T operator|(Point2D< T > b) { return x * b.x + y * b.y; }
  T operator^(Point2D< T > b) { return x * b.y - y * b.x; }
  T cross(Point2D< T > a, Point2D< T > b) { return (a-*this)^(b-*this); }
  T norm() { return (*this) | (*this); }
  double abs() { return sqrt(norm()); }
  double proj(Point2D< T > b) { return (*this | b) / b.abs(); }
  double angle(Point2D< T > b) { 
    return acos(((*this) | b) / this->abs() / b.abs()); 
  }
};
template<typename T >
Point2D< T > operator*(T a, Point2D< T > b) { return b * a; }
