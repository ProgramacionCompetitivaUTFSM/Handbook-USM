struct trie {
  vector <vector <ll>> tree;
  trie() {
    tree.push_back(vector < ll > (26, -1));
  };
  void insert(string &s, ll i = 0, ll u = 0) {
    if (s.size() == i) return;
    char c = s[i];
    if (tree[u][c - 'a'] != -1)
      insert(s, i + 1, tree[u][c - 'a']);
    else {
      ll pos = tree.size();
      tree.push_back(vector < ll > (26, -1));
      tree[u][c - 'a'] = pos;
      insert(s, i + 1, tree[u][c - 'a']);
    }
  }
};