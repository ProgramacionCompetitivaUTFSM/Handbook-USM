struct trie {
  vector <vector<ll>> tree;
  vector<ll> counts;
  trie() {
    tree.push_back(vector<ll>(26, -1));
    counts.push_back(0);
  };
  void insert(string &s) {
    ll i = 0, u = 0;
    while(i < s.size()){
        char c = s[i];
        if (tree[u][c - 'a'] == -1){
            ll pos = tree.size();
            tree.push_back(vector<ll>(26, -1));
            counts.push_back(0);
            tree[u][c - 'a'] = pos;
        }
        i++;
        u = tree[u][c - 'a'];
    }
    counts[u]++; // count final character
  }
  ll search(string &s){
    ll i = 0,u = 0;
    ll count_ends = 0;
    while(i < s.size()){
        char c = s[i];
        if (tree[u][c - 'a'] != -1){
            //If you need to know how many trailing characters it goes through, uncomment.
            //count_ends += counts[u];
            u = tree[u][c - 'a'];
            i++;
        }else break;
    }
    count_ends += counts[u];
    return count_ends;
  }
};
