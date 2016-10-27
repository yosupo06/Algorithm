template <class E>
using Graph = vector<vector<E>>;

struct TreeOrd {
    using P = pair<int, int>;
    vector<P> s, rs;
    template<class E>
    TreeOrd(const Graph<E> &g, int r = 0) {
        s.push_back(P(r, -1));
        for (int i = 0; i < int(s.size()); i++) {
            P p = s[i];
            for (E e: g[p.first]) {
                if (e.to == p.second) continue;
                s.push_back(P(e.to, p.first));
            }
        }
        rs = vector<P>(s.rbegin(), s.rend());
    }
};
