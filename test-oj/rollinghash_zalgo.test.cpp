#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "string/rollinghash.hpp"

int main() {
    H::init(TEN(6));
    Scanner sc(stdin);
    Printer pr(stdout);
    string s;
    sc.read(s);
    int n = int(s.size());
    V<H> hs = {H()};
    for (char c: s) {
        H nh = hs.back() + H(c);
        hs.push_back(nh);
    }
    dbg(H::powB[3]);
    for (int i = 0; i < n; i++) {
        int lw = 0, up = n - i + 1;
        while (up - lw > 1) {
            int md = (lw + up) / 2;
            if (hs[md] == hs[i + md].strip_left(hs[i])) {
                lw = md;
            } else {
                up = md;
            }
        }
        pr.write(lw);
        pr.write(' ');
    }
    pr.writeln();
}
