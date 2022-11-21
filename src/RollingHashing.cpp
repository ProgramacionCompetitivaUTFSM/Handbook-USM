class RollingHashing {
  ll p;
  ll m;
  ll ns;
  vector< ll > pows;
  vector< ll > hash;

  RollingHashing(string s) {
    // if WA then other p and other m
    // if still WA then double hashing
    // if still WA maybe is not the answer RH
    p = 31;
    m = 1e9 + 7;


    ns = s.size();
    pows.resize(ns + 2);
    for(int i = 1; i < ns + 2; i++) {
      pows[i] = (pows[i - 1] * p) % m;
    }
    hash.resize(ns + 1);
    hash[0] = 0;
    for(int i = 1; i <= ns; i++) {
      ll char_to_num = S[i - 1] - 'a' + 1;  
      ll prev_hash = hash[i - 1];
      hash[i] = ((char_to_num * pows[i - 1]) % m + prev_hash) % m; 
    }
  }

  ll compute_hashing(ll i, ll j) {
    return (hash[j] - hash[i] + m) % m;
  }
}
