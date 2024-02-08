/*
 *Description:* Same utility of normal union-find, but you can rollback the last union. Runs on $O( alpha (n) ) $
 *Status:* Highly tested
*/
struct op{
  int v,u;
  int v_value,u_value;
  op(int _v,int _v_value,int _u,int _u_value): v(_v),v_value(_v_value),u(_u),u_value(_u_value) {}
};
struct union_find_rb {
  vector<int> e;
  stack<op> ops;
  int comps;
  union_find_rb(){}
  union_find_rb(int n): comps(n) {e.assign(n, -1);}
  int findSet (int x) { 
    return (e[x] < 0 ? x : findSet(e[x]));
  }
  bool sameSet (int x, int y) { return findSet(x) == findSet(y); }
  int size (int x) { return -e[findSet(x)]; }
  bool unionSet (int x, int y) {
    x = findSet(x), y = findSet(y);
    if (x == y) return 0;
    if (e[x] > e[y]) swap(x, y);
    ops.push(op(x,e[x],y,e[y])); comps--;
    e[x] += e[y], e[y] = x;
    return 1;
  }
  void rb(){
    if(ops.empty()) return;
    op last = ops.top(); ops.pop();
    e[last.v] = last.v_value;
    e[last.u] = last.u_value;
    comps++;
  }
};