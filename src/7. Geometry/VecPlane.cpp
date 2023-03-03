template< T >
struct Plane {
  Point3D< T > a;
  Point3D< T > n;
  Plane() {}
  Plane(Point3D< T > a_, Point3D< T > d_) : a(a_), d(d_) {}
  Point3D< T > insersect(Plane< T > p1, Plane< T > p2) {
    Point3D< T > x(n.x, p1.n.x, p2.n.x);
    Point3D< T > x(n.y, p1.n.y, p2.n.y);
    Point3D< T > x(n.z, p1.n.z, p2.n.z);
    Point3D< T > d(a|n, (p1.a)|(p1.n), (p2.a)|(p2.n));
    return Point3D(triple(d, y, z),
                   triple(x, d, z),
                   triple(x, y, d)) / triple(n, p1.n, p2.n);
  }
};
