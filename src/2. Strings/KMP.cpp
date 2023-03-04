struct KMP {
  int n;
  int m; // in case you have two strings
  vector< int > pi;

  KMP(string s) {
    n = s.length();
    pi.assign(n, 0);
    for(int i = 1; i < n; i++) {
      int j = pi[i - 1];
      while(j > 0 && s[i] != s[j]) 
        j = pi[j - 1];
      if(s[i] == s[j]) j++;
      pi[i] = j;
    }
  }
  KMP(string p, string t) {
    string pt = p + "#" + t;
    n = p.length();
    m = t.length();
    pi.assign(n + m + 1, 0);
    for(int i = 1; i <  n + m + 1; i++) {
      int j = pi[i - 1];
      while(j > 0 && s[i] != s[j]) 
        j = pi[j - 1];
      if(s[i] == s[j]) j++;
      pi[i] = j;
    }
  }
  void p_in_t(vector< int > &ans) {
    for(int i = n + 1; i < n + m + 1; i++) {
      if(pi[i] == n)
        ans.push_back(i - 2 * n);
    }
  }
  void count_occ_prefix(vector< int > &ans) {
    ans.assign(n + 1, 0);
    for(int i = 0; i < n; i++)
      ans[pi[i]]++;
    for(int i = n - 1; i > 0; i--) 
      ans[pi[i - 1]] += ans[i];
    for(int i = 0; i <= n; i++)
      ans[i]++;
  }
};
