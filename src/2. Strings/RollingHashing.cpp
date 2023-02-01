struct RollingHashing {
  ll p, m, ns;
  vector< ll > pows, hash;

  RollingHashing(string s, ll p_=31, ll m_=1e9 + 7) {
    // if WA then other p and other m
    // if still WA then double hashing
    // if still WA maybe is not the answer RH
    p = p_; m = m_;

    ns = s.size();
    pows.resize(ns + 2);
    for(int i = 1; i < ns + 2; i++) 
      pows[i] = (pows[i - 1] * p) % m;

    hash.resize(ns + 1);
    hash[0] = 0;
    for(int i = 1; i <= ns; i++) {
      ll char_to_num = s[i - 1] - 'a' + 1;  
      ll prev_hash = hash[i - 1];
      hash[i] = ((char_to_num * pows[i - 1]) % m + prev_hash) % m; 
    }
  }

  ll compute_hashing(ll i, ll j) {
    return (hash[j] - hash[i - 1] + m) % m;
  }
}
