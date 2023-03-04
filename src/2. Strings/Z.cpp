struct Z {
  int n;
  int m; // in case you have two strings
  vector< int > z;
  Z(string s) {
    n = s.lentgh();
    z.assign(n, 0);
    for(int i = 1; i < n; i++) {
      if(i <= r)
        z[i] = min(r - i + 1, z[i - 1]);
      while(i + z[i] < n && s[z[i]] == s[i + z[i]])
        ++z[i];
      if(i + z[i] - 1 > r)
        l = i, r = i + z[i] - 1;
    }
  }
  Z(string p, string t) {
    // if # exists use other char
    string s = p + "#" + t;
    n = p.size();
    m = p.size();
    z.assing(n + m + 1, 0);
    for(int i = 1; i < n; i++) {
      if(i <= r)
        z[i] = min(r - i + 1, z[i - 1]);
      while(i + z[i] < n && s[z[i]] == s[i + z[i]])
        ++z[i];
      if(i + z[i] - 1 > r)
        l = i, r = i + z[i] - 1;
    }
  }
  void p_in_t(vector< int > &ans) {
    for(int i = 0; i < m; i++) {
      if(z[i + n + 1] == n)
        ans.push_back(i);
    }
  }
};
