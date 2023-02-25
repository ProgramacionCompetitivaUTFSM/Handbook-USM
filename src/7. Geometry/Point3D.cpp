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
};
template< T >
Point3D operator*(T a, Point3D< T > b) {
  return b * a;
}
