#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "base.h"
#include "util/fast_io.h"
#include "string/onlinez.h"

struct OnlineZ {
    string s;
    V<int> mp = {-1}, nx;
    int j = -1;
    V<int> inc(char c) {
        // calc nx
        s.push_back(c);
        if (mp.back() == -1) nx.push_back(-1);
        else nx.push_back(s[mp.back()] != c ? mp.back() : nx[mp.back()]);
        // calc mp
        int i = int(s.size()) - 1;
        while (j >= 0 && s[i] != s[j]) j = mp[j];
        j++;
        mp.push_back(j);

        V<int> res;
        int u = nx.back();
        while (u != -1) {
            if (s[u] != c) {
                res.push_back(int(s.size()) - 1 - u);
                u = mp[u];
            } else {
                u = nx[u];
            }
        }
        return res;
    }
};

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    string s;
    sc.read(s);
    int n = int(s.size());
    s += "$";

    V<int> z(n, -1);
    z[0] = n;
    OnlineZ oz;
    for (int i = 0; i <= n; i++) {
        auto v = oz.inc(s[i]);
        for (int x: v) {
            z[x] = i - x;
        }
    }
    pr.writeln(z);
}
