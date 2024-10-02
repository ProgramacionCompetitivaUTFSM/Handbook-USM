/*
 *Description:* Optimizes linear function, based of linear restrictions, in $O(n^2)$
 *Status:* Not tested
*/
template<class T> struct Simplex {
    T ans;
    vector<vector<T>> a;
    vector<T> b,c,d;
    void pivot(int ii, int jj){
        d[ii] = c[jj];
        T s1 = a[ii][jj];
        for (int i = 0; i < a[0].size(); i++)
            a[ii][i] /= s1;
        b[ii] /= s1;
        for (int i = 0; i < d.size(); i++){
            if (i == ii || a[i][jj] == 0) continue;
            T s2 = a[i][jj];
            for (int j = 0; j < a[0].size(); j++)
                a[i][j] -= s2*a[ii][j];
            b[i] -= s2*b[ii];
        }
    }
    bool next_point(){
        int idx = -1; T mx;
        for (int i = 0; i < a[0].size(); i++){
            T z = 0;
            for (int j = 0; j < d.size(); j++)
                z += a[j][i]*d[j];
            if (idx == -1 || mx < c[i]-z)
                mx = c[i]-z, idx = i;
        }
        if (mx > 0){
            int idx2 = -1; T mn;
            for (int i = 0; i < b.size(); i++){
                if (a[i][idx] == 0 || b[i]/a[i][idx] <= 0) continue;
                if (idx2 == -1 || mn > b[i]/a[i][idx])
                    mn = b[i]/a[i][idx], idx2 = i;
            }
            pivot(idx2,idx);
            return 1;
        }
        return 0;
    }
    Simplex(vector<vector<T>> & _a, vector<T> & _b, vector<T> & _c) : a(_a),b(_b),c(_c){
        d.resize(b.size(),0);
        while (next_point());
        ans = 0;
        for (int i = 0; i < b.size(); i++)
            ans += b[i]*d[i];
    }
};