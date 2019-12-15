#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "base.h"
#include "util/fast_io.h"
#include "string/suffixarray.h"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    string s;
    sc.read(s);
    auto sa = doublingSA(s);
    pr.writeln(V<int>{sa.begin() + 1, sa.end()});
}
