#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include "base.h"
#include "util/fast_io.h"
#include "string/suffixarray.h"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    string s;
    sc.read(s);
    auto sai = SA<string>(s, sa_is(s));
    int n = int(s.size());
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += max(0, (n - sai.sa[i + 1]) - sai.lcp[i]);
    }
    pr.writeln(ans);
}
