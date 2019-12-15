#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "base.h"
#include "util/fast_io.h"
#include "string/zalgo.h"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    string s;
    sc.read(s);
    auto z = z_algo(s); z.pop_back();
    pr.writeln(z);
}
