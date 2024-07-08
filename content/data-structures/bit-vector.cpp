/*
 *Description:* A more flexible dynamic bit_vector, with operations `access`, `set`, `not` and `push_back`
 *status:* partially tested
*/
struct bit_vector {
  uint64_t size;
  vector< uint64_t > bv;
  bit_vector() : size(0) {}
  uint64_t get(uint64_t i) const {
    uint64_t b = i / 64;
    uint64_t ib = i % 64;
    return (bv[b] & (1ULL << ib)) >> ib;
  }
  void set(uint64_t i) {
    uint64_t b = i / 64;
    uint64_t ib = i % 64;
    bv[b] |= (1ULL << ib);
  }
  void push_back(uint64_t bit) {
    if(size % 64 == 0) bv.push_back(0);
    uint64_t b = size / 64;
    uint64_t ib = size++ % 64;
    bv[b] |= (bit << ib);
  }
  bit_vector operator~() {
    bit_vector bv = *this;
    for(uint64_t i = 0; i < bv.bv.size(); i++)
      bv.bv[i] = ~bv.bv[i];
    if(size % 64)
      for(uint64_t i = size % 64; i < 64; i++)
        bv.bv[bv.bv.size() - 1] &= (~(1ULL << i));
    return bv;
  }
  friend std::ostream& operator<<(std::ostream& os, const bit_vector& bv) {
    for(uint64_t i = 0; i < bv.size; i++) {
      if(bv.bv[i / 64] < (1ULL << 32) && (i % 64) >= 32) cout << 0;
      else cout << ((bv.bv[i / 64] & (1ULL << (i % 64))) ? 1 : 0);
    }
    return os;
  }
  bit_vector& operator=(const bit_vector& o) {
    if (this != &o)
      size = o.size, bv = o.bv;
    return *this;
  }
  bool operator==(const bit_vector& o) const {
    if(size != o.size) return false;
    for(uint64_t i = 0; i < size; i++)
      if(get(i) != o.get(i)) return false;
    return true;
  }
  bool operator<(const bit_vector& o) const {
    for(uint64_t i = 0; i < size && i < o.size; i++)
      if(get(i) != o.get(i)) return get(i) < o.get(i);
    return size < o.size;
  }
  bool operator>(const bit_vector& o) const {
    for(uint64_t i = 0; i < size && i < o.size; i++)
      if(get(i) != o.get(i)) return get(i) > o.get(i);
    return size > o.size;
  }
  bool operator<=(const bit_vector& o) const {
    for(uint64_t i = 0; i < size && i < o.size; i++)
      if(get(i) != o.get(i)) return get(i) <= o.get(i);
    return size <= o.size;
  }
  bool operator>=(const bit_vector& o) const {
    for(uint64_t i = 0; i < size && i < o.size; i++)
      if(get(i) != o.get(i)) return get(i) >= o.get(i);
    return size >= o.size;
  }
};
