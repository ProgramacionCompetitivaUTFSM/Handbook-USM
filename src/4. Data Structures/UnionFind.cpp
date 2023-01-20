struct UnionFind {
	vector<int> e;
	UnionFind(int n) {
		e.assign(n, -1);
	}
	int findSet (int x) {
		return (e[x] < 0 ? x : e[x] = findSet(e[x]));
	}
	bool sameSet (int x, int y) {
		return findSet(x) == findSet(y);
	}
	int size (int x) {
		return -e[findSet(x)];
	}
	bool unionSet (int x, int y) {
		x = findSet(x), y = findSet(y);
		if (x == y) return 0;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y], e[y] = x;
		return 1;
	}
};
