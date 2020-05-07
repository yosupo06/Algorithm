#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#define LOCAL
#include "base.h"

int main() {
    pair<int, int> a = {1, 2};
    dbg(a);
    V<int> b = {1, 2, 3};
    dbg(b);
    V<pair<int, int>> c = {{1, 2}, {3, 4}};
    dbg(c);
    pair<V<int>, V<int>> d = {{1, 2}, {3, 4, 5}};
    dbg(d);

    array<int, 3> e = {1, 2, 3};
    dbg(e);
    array<V<int>, 2> f = {{{1, 2, 3}, {4, 5}}};
    dbg(f);

    set<int> g = {1, 2, 3, 4};
    dbg(g);

    map<int, int> h; h[1] = 2; h[3] = 4;
    dbg(h);

    int x, y;
    cin >> x >> y;
    cout << x + y << endl;
    return 0;
}
