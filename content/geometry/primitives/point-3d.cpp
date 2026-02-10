/*
 *Description:* 3D Point with full support
 *Status:* Tested
 */
template <typename T> struct point3d {
  T x, y, z;
  point3d() : x(0), y(0), z(0) {}
  point3d(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

  point3d<T> &operator=(const point3d<T> &t) {
    x = t.x, y = t.y, z = t.z;
    return *this;
  }
  point3d<T> &operator+=(const point3d<T> &t) {
    x += t.x, y += t.y, z += t.z;
    return *this;
  }
  point3d<T> &operator-=(const point3d<T> &t) {
    x -= t.x, y -= t.y, z -= t.z;
    return *this;
  }
  point3d<T> &operator*=(T t) {
    x *= t, y *= t, z *= t;
    return *this;
  }
  point3d<T> &operator/=(T t) {
    x /= t, y /= t, z /= t;
    return *this;
  }
  point3d<T> operator-(const point3d<T> &t) const {
    return {x - t.x, y - t.y, z - t.z};
  }
  point3d<T> operator+(const point3d<T> &t) const {
    return {x + t.x, y + t.y, z + t.z};
  }
  point3d<T> operator*(T t) const { return {x * t, y * t, z * t}; }
  point3d<T> operator/(T t) const { return {x / t, y / t, z / t}; }

  // Dot product
  T dot(const point3d<T> &b) const { return x * b.x + y * b.y + z * b.z; }
  T operator|(const point3d<T> &b) const { return dot(b); }

  // Cross product (returns a vector in 3D)
  point3d<T> cross(const point3d<T> &b) const {
    return {y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x};
  }
  point3d<T> operator^(const point3d<T> &b) const { return cross(b); }

  // Signed volume of tetrahedron (a, b, c, *this as origin)
  T triple(const point3d<T> &a, const point3d<T> &b) const {
    return dot(a ^ b);
  }

  T norm() const { return dot(*this); }
  T sq_dist(const point3d<T> &b) const { return (*this - b).norm(); }
  double abs() const { return sqrt((double)norm()); }
  double dist(const point3d<T> &b) const { return (*this - b).abs(); }

  point3d<T> unit() const { return *this / this->abs(); }

  double proj(const point3d<T> &b) const { return (double)dot(b) / b.abs(); }
  double angle(const point3d<T> &b) const {
    return acos(clamp((double)dot(b) / this->abs() / b.abs(), -1.0, 1.0));
  }

  // Rotations around axes
  point3d<T> rotate_z(double a) const {
    return {(T)(cos(a) * x - sin(a) * y), (T)(sin(a) * x + cos(a) * y), z};
  }
  point3d<T> rotate_x(double a) const {
    return {x, (T)(cos(a) * y - sin(a) * z), (T)(sin(a) * y + cos(a) * z)};
  }
  point3d<T> rotate_y(double a) const {
    return {(T)(cos(a) * x + sin(a) * z), y, (T)(-sin(a) * x + cos(a) * z)};
  }
};

template <typename T> point3d<T> operator*(T a, point3d<T> b) { return b * a; }