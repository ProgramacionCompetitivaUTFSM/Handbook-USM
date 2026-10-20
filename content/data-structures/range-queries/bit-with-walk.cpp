/*
 *Description:*: Extends fenwick_tree with walk operation. Return 0-based index i where freq bit[i] reach k. Walk O(log n). Return n if that k > sum(n-1).
 *Status:* Partially tested
*/
struct fenwick_tree_with_walk : fenwick_tree {
  ll walk(ll k) {
    if (k <= 0 || k > sum(n-1)) return n;
    ll i = -1, s = 1;
    while ((s << 1) < n) s <<= 1;
    while (s > 0) {
      ll m = i + s;
      if (m < n && bit[m] < k) {
        i = m;
        k -= bit[m];
      }
      s >>= 1;
    }
    return i + 1;
  }
};
