template<
	class tree_node, 
	class query_input,
	class query_output
>
struct extended_segment_tree{
	vector<tree_node> ST;
	int n;
	void build(int i, int l, int r, vector<tree_node> &a){
		if (l == r){
			ST[i] = a[l];
			return;
		}
		int mid = (l + r) / 2;
		build(i << 1, l, mid, a);
		build(i << 1 | 1, mid + 1, r, a);
		ST[i].build(&ST[i << 1], &ST[i << 1 | 1]);
	}
	extended_segment_tree(vector<tree_node> &a){
		n = a.size();
		ST.resize(n << 2 | 3);
		build(1, 0, n - 1, a);
	}

	query_output query(int i, int l, int r, int a, int b, query_input &q){
		if (l >= a and r <= b){
			return ST[i].query(q);
		}
		int mid = (l + r) / 2;
		if (b <= mid){
			return query(i << 1, l, mid, a, b, q);
		}
		else if (a > mid){
			return query(i << 1 | 1, mid + 1, r, a, b, q);
		}
		query_output R = query(i << 1 | 1, mid + 1, r, a, b, q);
		query_output L = query(i << 1, l, mid, a, b, q);
		return L.merge(&R);
	}

	query_output query(int l, int r, query_input &q){
		return query(1, 0, n - 1, l, r, q);
	}

	void update(int i, int l, int r, int pos, tree_node &x){
		if (l == r){
			ST[i] = x;
			return;
		}
		int mid = (l + r) / 2;
		if (l <= mid){
			update(i << 1, l, mid, pos, x);
		}
		if (r > mid){
			update(i << 1 | 1, mid + 1, r, pos, x);
		}
		ST[i].update(pos - l, x);
	}

	void update(int pos, tree_node &x){
		update(1, 0, n - 1, pos, x);
	}
};

struct query_output{
	int v;
	query_output(int v) : v(v){}
	query_output merge(query_output *r){
		return query_output(v + r->v);
	}
};

typedef int query_input;

struct tree_node{
	int n;
	vector<int> a;
	tree_node(){}
	tree_node(int x){
		a.resize(1, x);
		n = 1;
	}
	void update(int pos, tree_node &x){
		return;
	}
	query_output query(int v){
		int left = 0, right = n - 1;
		while(left < right){
			int mid = (left + right + 1) / 2;
			if (a[mid] <= v){
				left = mid;
			}
			else{
				right = mid - 1;
			}
		}
		if (a[left] > v)
			left --;
		return query_output(n - 1 - left);
	}
	void build(tree_node *l, tree_node *r){
		int nl = l->a.size(), nr = r->a.size();
		int pl = 0, pr = 0;
		a.reserve(nl + nr);
		while(pl < nl || pr < nr){
			if (pl == nl || (pr < nr and l->a[pl] >= r->a[pr])){
				a.push_back(r->a[pr ++]);
			}
			else{
				a.push_back(l->a[pl ++]);
			}
		}
		n = a.size();
	}
};
extended_segment_tree<tree_node, query_output, query_input> EST(a);