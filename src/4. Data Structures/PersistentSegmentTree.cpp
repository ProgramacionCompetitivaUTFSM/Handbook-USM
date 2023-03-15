template < typename T, T merge(T, T) >
  struct st_node {
    st_node * left = 0, * right = 0;
    int i, j;
    T val;
    st_node() {}
    st_node(int _i, int _j): i(_i), j(_j) {}
    st_node(vector < T > & A) {
      int N = int(A.size());
      i = 0, j = N - 1;
      build(A);
    }

    void build(vector < ll > & A) {
      if (i == j) {
        val = A[i];
        return;
      }
      int mid = (i + j) / 2;
      left = new st_node < T, merge > (i, mid);
      right = new st_node < T, merge > (mid + 1, j);
      left -> build(A);
      right -> build(A);
      val = merge(left -> val, right -> val);
    }

    st_node * update(int t, ll v) {
      if (t < i || j < t) {
        return this;
      }
      if (i == j) {
        st_node * ret = new st_node < T, merge > ( * this);
        ret -> val = v;
        return ret;
      }
      st_node * ret = new st_node < T, merge > (i, j);
      ret -> left = left -> update(t, v);
      ret -> right = right -> update(t, v);
      ret -> val = merge(ret -> left -> val, ret -> right -> val);
      return ret;
    }

    ll query(int l, int r) {
      if (l <= i && j <= r) return val;
      int mid = (i + j) / 2;
      if (mid < l || r < i) return right -> query(l, r);
      else if (j < l || r < mid + 1) return left -> query(l, r);
      return merge(left -> query(l, r), right -> query(l, r));
    }
  };
