template< T >
struct Point3D {
  T x, y, z;
  Point3D() {};
  Point3D(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}
  Point3D& operator+= (const Point3D &t) {
    x += t.x;
    y += t.y;
    z += t.z;
    return *this;
  }
  Point3D& operator-= (const Point3D &t) {
    x -= t.x;
    y -= t.y;
    z -= t.z;
    return *this;
  }
  Point3D& operator*= (const Point3D &t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
  }
  Point3D& operator/= (const Point3D &t) {
    x /= t;
    y /= t;
    z /= t;
    return *this;
  }
  Point3D operator+(const Point3D &t) const {
    return Point3D(*this) += t;
  }
  Point3D operator-(const Point3D &t) const {
    return Point3D(*this) -= t;
  }
  Point3D operator*(T t) const {
    return Point3D(*this) *= t;
  }
  Point3D operator/(T t) const {
    return Point3D(*this) /= t;
  }
  T dot(Point3D& b) {
    return x * b.x + y * b.y + z * b.z;
  }
  Point3D cross(Point3D & b) {
    return Point3D(y * b.z - z * b.y,
                   z * b.x - x * b.z,
                   x * b.y - y * b.x);
  }
  T norm() {
    return dot(*this);
  }
  double abs() {
    return sqrt(norm());
  }
  double proj(Point3D& b) {
    return dot(b) / b.abs();
  }
  double angle(Point3D& b) {
    return acos(dot(b) / abs() / b.abs());
  }
};
template< T >
Point3D operator*(T a, Point3D< T > b) {
  return b * a;
}
template< T >
T triple(Point3D a, Point3D b, Point3D c) {
  return dot(a, cross(b, c));
}
