template< T >
struct Point3D {
  T x, y, z;
  Point3D() {};
  Point3D(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}
  Point3D< T >& operator=(Point3D< T > t) {
    x = t.x; y = t.y; z = z.y;
    return *this;
  }
  Point3D< T >& operator+=(Point3D< T > t) {
    x += t.x; y += t.y; z += t.z;
    return *this;
  }
  Point3D< T >& operator-=(Point3D< T > t) {
    x -= t.x; y -= t.y; z -= t.z;
    return *this;
  }
  Point3D< T >& operator*=(Point3D< T > t) {
    x *= t; y *= t; z *= t;
    return *this;
  }
  Point3D< T >& operator/=(Point3D< T > t) {
    x /= t; y /= t; z /= t;
    return *this;
  }
  Point3D< T > operator+(Point3D< T > t) {
    return Point3D(*this) += t;
  }
  Point3D< T > operator-(Point3D< T > t) {
    return Point3D(*this) -= t;
  }
  Point3D< T > operator*(T t) {
    return Point3D(*this) *= t;
  }
  Point3D< T > operator/(T t) {
    return Point3D(*this) /= t;
  }
  T operator|(Point3D< T >& b) { return x * b.x + y * b.y + z * b.z; }
  Point3D< T > operator^(Point3D< T > & b) {
    return Point3D(y * b.z - z * b.y,
                   z * b.x - x * b.z,
                   x * b.y - y * b.x);
  }
  T norm() { return (*this)|(*this); }
  double abs() { return sqrt(norm()); }
  double proj(Point3D< T >& b) { return ((*this)|b) / b.abs(); }
  double angle(Point3D< T >& b) { 
    return acos(((*this)|b) / abs() / b.abs());
  }
};
template< T >
Point3D< T > operator*(T a, Point3D< T > b) { return b * a; }
template< T >
T triple(Point3D< T > a, Point3D< T > b, Point3D< T > c) {
  return a|(b^c);
}
