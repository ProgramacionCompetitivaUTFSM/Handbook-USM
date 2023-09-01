template<class I> vector<int> LIS(const vector<I>& S) {
	if (S.empty()) return {};
	vector<int> prev(S.size());
	vector<pair<I, int>> res;
    for (int i = 0; i < S.size(); i++) {
		// 0 -> i for longest non-decreasing subsequence
		auto it = lower_bound(res.begin(), res.end(), pair<I, int>{S[i], i});
		if (it == res.end()) res.emplace_back(), it = res.end()-1;
		*it = {S[i], i};
		prev[i] = (it == res.begin() ? 0 : (it-1)->second);
	}
	int L = res.size(), cur = res.back().second;
	vector<int> ans(L);
	while (L--) ans[L] = cur, cur = prev[cur];
    /* Para obtener la secuencia
	for (int i = 0; i+1 < ans.size(); i++)
		ans[i] = S[ans[i]];
    */
	return ans;
}
