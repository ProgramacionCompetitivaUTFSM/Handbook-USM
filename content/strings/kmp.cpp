/*
  *Description:* Find occurrences of a pattern within given text, runs in $O(n + m)$, where $n$ and $m$ are the lengths of the text and pattern respectively.
  *Status:* Tested on CSES
*/
template<class T> struct KMP {
  T pattern; vector<int> lps;
  KMP(T &pat): pattern(pat) {
    lps.resize(pat.size(), 0);
    int len = 0, i = 1;
    while (i < pattern.size()) {
      if (pattern[i] == pattern[len])
        lps[i++] = ++len;
      else {
        if (len != 0) len = lps[len - 1];
        else lps[i++] = 0;
      }
    }
  }
  vector<int> search(T &text) {
    vector<int> matches;
    int i = 0, j = 0;
    while (i < text.size()) {
      if (pattern[j] == text[i]) {
        i++, j++;
        if (j == pattern.size()) {
          matches.push_back(i - j);
          j = lps[j - 1];
        }
      } else {
        if (j != 0) j = lps[j - 1];
        else i++;
      }
    }
    return matches;
  }
};
