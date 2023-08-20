template<class T>
struct Manacher {
    vector<int> odd, even; T s; int n;
    Manacher(T &s): s(s), n(s.size()) {
        odd.resize(n), even.resize(n);
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 1 : min(odd[l+r-i], r-i+1);
            while (0 <= i-k and i+k < n and s[i-k] == s[i+k]) k++;
            odd[i] = k--;
            if (i+k > r) l = i-k, r = i+k;
        }
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i>r) ? 0 : min(even[l+r-i+1], r-i+1);
            while (0 <= i-k-1 and i+k < n && s[i-k-1] == s[i+k]) k++;
            even[i] = k--;
            if (i+k > r) l = i-k-1, r = i+k;
        }
    }
    // devuelve el intervalo del palindromo más largo centrado en i
    pair<int, int> get(int i) { 
        int o = 2*odd[i] - 1;   // está centrado normal
        int e = 2*even[i];      // está centrado a la derecha
        if (o >= e)
            return {i-odd[i]+1, i+odd[i]-1};
        return {i-even[i], i+even[i]-1};
    }
};
