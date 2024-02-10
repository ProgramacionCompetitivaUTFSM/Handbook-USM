/*
 *Description:* Get the minumum element of the deque, runs on $O(1)$ per operation amortized. Can be modified to get the maximum just changing the function
 *Status:* Not tested
*/
template<typename T>
struct min_deque {
  min_stack<T> l, r, t;
	void rebalance() {
		bool f = false;
		if (r.empty()) {f = true; l.swap(r);}
		int sz = r.size() / 2;
		while (sz--) {t.push(r.top()); r.pop();}
		while (!r.empty()) {l.push(r.top()); r.pop();}
		while (!t.empty()) {r.push(t.top()); t.pop();}
		if (f) l.swap(r);
	}
	int getmin() {
		if (l.empty()) return r.getmin();
		if (r.empty()) return l.getmin();
		return min(l.getmin(), r.getmin());
	}
  bool empty() {return l.empty() and r.empty();}
	int size() {return l.size() + r.size();}
	void push_front(int x) {l.push(x);}
	void push_back(int x) {r.push(x);}
	void pop_front() {if (l.empty()) rebalance(); l.pop();}
	void pop_back() {if (r.empty()) rebalance(); r.pop();}
	int front() {if (l.empty()) rebalance(); return l.top();}
	int back() {if (r.empty()) rebalance(); return r.top();}
	void swap(min_deque &x) {l.swap(x.l); r.swap(x.r);}
};
