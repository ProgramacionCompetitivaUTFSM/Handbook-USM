/*
 *Description:* Space-efficient bit vector with rank support
 *Status:* Tested
 */
struct succinct_indexable_dictionary {
  size_t len, blocks;
  vector<unsigned> bit, sum;
  succinct_indexable_dictionary() = default;
  succinct_indexable_dictionary(size_t len) : len(len), blocks((len + 31)>>5) {
    bit.assign(blocks, 0U);
    sum.assign(blocks, 0U);
  }
  void set(int k) { bit[k >> 5] |= 1U << (k & 31); }
  void build() {
    sum[0] = 0U;
    for (int i = 1; i < blocks; i++)
      sum[i] = sum[i - 1] + __builtin_popcount(bit[i - 1]);
  }
  bool operator[](int k) { return (bool((bit[k >> 5] >> (k & 31)) & 1)); }
  int rank(int k) {
    return (sum[k >> 5] + __builtin_popcount(bit[k >> 5] & ((1U << (k & 31)) - 1)));
  }
  int rank(bool val, int k) { return (val ? rank(k) : k - rank(k)); }
};
