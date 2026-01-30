/*
 *Description:* 3D Convex Hull using randomized incremental algorithm
 *Time:* $O(n log n)$ expected
 *Status:* Tested
 */
template <typename T> struct convex_hull_3d {
  using pt = point3d<T>;
  const ld EPS = 1e-9;
  struct edge;
  struct face {
    int a, b, c;
    pt pa, pb, pc, q;
    edge *e1, *e2, *e3;
    vector<int> points;
    int dead = 1e9;
    face(int a, int b, int c, pt pa, pt pb, pt pc)
        : a(a), b(b), c(c), pa(pa), pb(pb), pc(pc) {
      q = ((pb - pa)^(pc - pa));
      e1 = e2 = e3 = nullptr;
    }
  };

  struct edge {
    edge *rev; face *f;
  };

  vector<pt> p;
  vector<face *> f;

  static void glue(face *F1, face *F2, edge *&e1, edge *&e2) {
    e1 = new edge, e2 = new edge;
    e1->rev = e2, e2->rev = e1;
    e1->f = F2, e2->f = F1;
  }

  void prepare() {
    int n = (int)p.size();
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(p.begin(), p.end(), rng);
    vector<int> ve = {0};
    for (int i = 1; i < n; i++) {
      if (ve.size() == 1) {
        if ((p[ve[0]] - p[i]).abs() > EPS) ve.push_back(i);
      } else if (ve.size() == 2) {
        if ((p[ve[1]] - p[ve[0]]).cross(p[i] - p[ve[0]]).abs() > EPS)
          ve.push_back(i);
      } else if (abs((p[i] - p[ve[0]])
                .dot((p[ve[1]] - p[ve[0]])
                .cross(p[ve[2]] - p[ve[0]]))) > EPS) {
        ve.push_back(i);
        break;
      }
    }
    assert((int)ve.size() == 4);
    vector<pt> ve2;
    for (int i : ve) ve2.push_back(p[i]);
    reverse(ve.begin(), ve.end());
    for (int i : ve) p.erase(p.begin() + i);
    p.insert(p.begin(), ve2.begin(), ve2.end());
  }

  convex_hull_3d(vector<pt> points) : p(move(points)) {
    int n = p.size();
    prepare();
    vector<face *> new_face(n, nullptr);
    vector<vector<face *>> conflict(n);

    auto add_face = [&](int a, int b, int c) {
      face *F = new face(a, b, c, p[a], p[b], p[c]);
      f.push_back(F);
      return F;
    };

    face *F1 = add_face(0, 1, 2);
    face *F2 = add_face(0, 2, 1);
    glue(F1, F2, F1->e1, F2->e3);
    glue(F1, F2, F1->e2, F2->e2);
    glue(F1, F2, F1->e3, F2->e1);

    for (int i = 3; i < n; i++) {
      for (face *F : {F1, F2}) {
        T Q = (p[i] - p[F->a]).dot(F->q);
        if (Q > EPS) conflict[i].push_back(F);
        if (Q >= -EPS) F->points.push_back(i);
      }
    }

    for (int i = 3; i < n; i++) {
      for (face *F : conflict[i])
        F->dead = min(F->dead, i);
      int v = -1;
      for (face *F : conflict[i]) {
        if (F->dead != i)
          continue;
        int parr[3] = {F->a, F->b, F->c};
        edge *earr[3] = {F->e1, F->e2, F->e3};
        for (int j = 0; j < 3; j++) {
          int j2 = (j + 1)%3;
          if (earr[j]->f->dead > i) {
            face *Fn = new_face[parr[j]] = add_face(parr[j], parr[j2], i);
            set_union(F->points.begin(), F->points.end(),
                      earr[j]->f->points.begin(), earr[j]->f->points.end(),
                      back_inserter(Fn->points));
            Fn->points.erase(
                stable_partition(Fn->points.begin(), Fn->points.end(),
                                 [&](int k) {
                                   return k > i and
                                          (p[k] - p[Fn->a]).dot(Fn->q) > EPS;
                                 }),
                Fn->points.end());
            for (int k : Fn->points) conflict[k].push_back(Fn);
            earr[j]->rev->f = Fn;
            Fn->e1 = earr[j];
            v = parr[j];
          }
        }
      }
      if (v == -1) continue;
      while (new_face[v]->e2 == nullptr) {
        int u = new_face[v]->b;
        glue(new_face[v], new_face[u], new_face[v]->e2, new_face[u]->e3);
        v = u;
      }
    }
    f.erase(remove_if(f.begin(), f.end(), [&](face *F) { return F->dead < n; }), f.end());
  }

  int num_faces() const { return f.size(); }
  T area() {
    T res = 0;
    for (face *F : f)
      res += F->q.abs() / 2.0;
    return res;
  }
  T volume() {
    T vol = 0;
    for (face *F : f)
      vol += F->pa.dot(F->q);
    return abs(vol) / 6.0;
  }
  vector<array<int, 3>> faces() {
    vector<array<int, 3>> res;
    for (face *F : f)
      res.push_back({F->a, F->b, F->c});
    return res;
  }
};