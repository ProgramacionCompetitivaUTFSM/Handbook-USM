struct SuffixAutomaton {
  struct state {
    int len, link;
    int next[26];
    state(int _len = 0, int _link = -1) : len(_len), link(_link) {
      memset(next, -1, sizeof(next));
    }
  };
  vector<state> st;
  int last;
  SuffixAutomaton() {}
  SuffixAutomaton(const string &s) { init(s); }
  inline int State(int len = 0, int link = -1) {
    st.emplace_back(len, link);
    return st.size() - 1;
  }
  void init(const string &s) {
    st.reserve(2 * s.size());
    last = State();
    for (char c : s)
      extend(c);
  }
  void extend(char _c) {
    int c = _c - 'a', cur = State(st[last].len + 1), P = last;
    while ((P != -1) && (st[P].next[c] == -1)) {
      st[P].next[c] = cur;
      P = st[P].link;
    }
    if (P == -1)
      st[cur].link = 0;
    else {
      int Q = st[P].next[c];
      if (st[P].len + 1 == st[Q].len)
        st[cur].link = Q;
      else {
        int C = State(st[P].len + 1, st[Q].link);
        copy(st[Q].next, st[Q].next + 26, st[C].next);
        while ((P != -1) && (st[P].next[c] == Q)) {
          st[P].next[c] = C;
          P = st[P].link;
        }
        st[Q].link = st[cur].link = C;
      }
    }
    last = cur;
  }
};
