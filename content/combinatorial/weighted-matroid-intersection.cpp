/*
 *Description:* Maximum weight base in matroid intersection  $O (r^(2n("O1"+"O2"))) $, where $r$ is the rank of the basis, and 
 $n$ is the size of the ground set, O1 is the cost of Oracle query in the first matroid, and O2 the cost of Oracle query in second matroid.
 
 *Status:* Not tested
*/
template<
    typename W_t, // weight type
    typename T, // element of the ground set type
    typename Orc1, // Oracle of the first matroid
    typename Orc2 // Oracle of the second matroid
>
vector<vector<T>> weighted_matroid_intersection(const vector<T> & ground_set, const Orc1 & matroid1, const Orc2 & matroid2){
    int n = ground_set.size();
    vector<vector<T>> res;
    vector<char> in_set(n), in_matroid1(n), in_matroid2(n);
    vector<pair<W_t,int>> dist(n);
    vector<pair<int,int>> edges;
    vector<int> par(n), l, r;
    l.reserve(n);
    r.reserve(n);
    while (1) {
        res.push_back({});
        for (int i = 0; i < n; i++)
            if (in_set[i])
                res.back().push_back(ground_set[i]);
        Orc1 m1 = matroid1;
        Orc2 m2 = matroid2;
        l.clear();
        r.clear();
        for (int i = 0; i < n; i++)
            if (in_set[i]) {
                m1.add(ground_set[i]);
                m2.add(ground_set[i]);
                l.push_back(i);
            } else {
                r.push_back(i);
            }
        fill(in_matroid1.begin(), in_matroid1.end(), 0);
        fill(in_matroid2.begin(), in_matroid2.end(), 0);
        for (int i : r) {
            in_matroid1[i] = m1.independed_with(ground_set[i]);
            in_matroid2[i] = m2.independed_with(ground_set[i]);
        }
        edges.clear();
        for (int i : l) {
            {
                Orc1 m = matroid1;
                for (int j : l)
                    if (i != j)
                        m.add(ground_set[j]);
 
                for (int j : r)
                    if (m.independed_with(ground_set[j]))
                        edges.emplace_back(i, j);
            }
            {
                Orc2 m = matroid2;
                for (int j : l)
                    if (i != j)
                        m.add(ground_set[j]);
 
                for (int j : r)
                    if (m.independed_with(ground_set[j]))
                        edges.emplace_back(j, i);
            }
        }
        static constexpr W_t INF = numeric_limits<W_t>::max();
        fill(dist.begin(), dist.end(), pair{INF, -1});
        fill(par.begin(), par.end(), -1);
        for (int i : r)
            if (in_matroid1[i])
                dist[i] = {-ground_set[i].weight, 0};
 
        while (1) {
            bool any = false;
            for (auto &[v, u] : edges) {
                if (dist[v].first == INF)
                    continue;
 
                int coeff = in_set[v] ? -1 : 1;
                if (dist[u] > pair{dist[v].first + coeff * ground_set[u].weight, dist[v].second + 1}) {
                    par[u] = v;
                    dist[u] = {dist[v].first + coeff * ground_set[u].weight, dist[v].second + 1};
                    any = 1;
                }
            }
            if (!any)
                break;
        }
        int finish = -1;
        for (int v : r)
            if (in_matroid2[v] && dist[v].first != INF && (finish == -1 || dist[finish] > dist[v]))
                finish = v;
        if (finish == -1)
            break;
 
        for (; finish != -1; finish = par[finish])
            in_set[finish] ^= 1;
    }
    return res;
}