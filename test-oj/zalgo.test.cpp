#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "string/zalgo.hpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    string s;
    sc.read(s);
    auto z = z_algo(s); z.pop_back();
    pr.writeln(z);
}
