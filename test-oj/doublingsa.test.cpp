#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "string/suffixarray.hpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    string s;
    sc.read(s);
    auto sa = doublingSA(s);
    pr.writeln(V<int>{sa.begin() + 1, sa.end()});
}
