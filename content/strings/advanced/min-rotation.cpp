/*
 *Description:* Finds the lexicographically smallest rotation of a string, runs on $O(n)$
 *Status:* Tested on CSES
*/
string minRotation(string &s) {
  int a = 0, N = s.size();
  string res = s; s += s;
  for (int b = 0; b < N; b++) {
    for (int k = 0; k < N; k++) {
      if (a + k == b || s[a + k] < s[b + k]) {
        b += max(0, k - 1); break;
      }
      if (s[a + k] > s[b + k]) {
        a = b; break;
      }
    }
  }
  rotate(res.begin(), res.begin() + a, res.end());
  return res;
}