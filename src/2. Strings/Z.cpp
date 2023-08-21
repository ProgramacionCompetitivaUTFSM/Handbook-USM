struct Z {
    int n, m; 
    vector<int> z;
    Z(string s) {
        n = s.size();
        z.assign(n, 0);
        int l = 0, r = 0;
        for (int i = 1; i < n; i++) {
            if (i <= r)
                z[i] = min(r - i + 1, z[i - l]);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]])
                ++z[i];
            if (i + z[i] - 1 > r)
                l = i, r = i + z[i] - 1;
        }
    }
    Z(string p, string t) {
        string s = p + "#" + t;
        n = p.size();
        m = t.size();
        z.assign(n + m + 1, 0);
        int l = 0, r = 0;
        for (int i = 1; i < n + m + 1; i++) {
            if (i <= r)
                z[i] = min(r - i + 1, z[i - l]);
            while (i + z[i] < n + m + 1 && s[z[i]] == s[i + z[i]])
                ++z[i];
            if (i + z[i] - 1 > r)
                l = i, r = i + z[i] - 1;
        }
    }
    void p_in_t(vector<int>& ans) {
        for (int i = n + 1; i < n + m + 1; i++) {
            if (z[i] == n)
                ans.push_back(i - n - 1);
        }
    }
};
