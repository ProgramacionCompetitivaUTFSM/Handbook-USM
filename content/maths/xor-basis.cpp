/*
 *Description:* Calculate the xor basis of a set of numbers.
 *Complexity:*
    - Insertion: O(d)
    - Query if a number can be formed: O(d)
    - Get maximum xor subset: O(d)
    - Merging two bases: O(d^2)
 *Status:* Partially tested
*/

struct xor_basis {
  int d, sz;
  vector<long long> basis;
  xor_basis(int _d): d(_d), sz(0), basis(_d, 0) {}
  bool insert(long long mask) {
    for (int i = d - 1; i >= 0; --i) {
      if ((mask & (1LL << i)) == 0) continue;
      if (!basis[i]) {
        basis[i] = mask;
        ++sz;
        return true;
      }
      mask ^= basis[i];
    }
    return false;
  }
  bool can_make(long long x){
    for (int i = d - 1; i >= 0; --i) {
      if ((x & (1LL << i)) == 0) continue;
      if (!basis[i]) return false;
      x ^= basis[i];
    }
    return x == 0;
  }
  long long get_max(){
    long long res = 0;
    for (int i = d - 1; i >= 0; --i)
      if ((res ^ basis[i]) > res) res ^= basis[i];
    return res;
  }
  void merge(const xor_basis &o) {
    for (long long v : o.basis)
      if (v) insert(v);
  }
};