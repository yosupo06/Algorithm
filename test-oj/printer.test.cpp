#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "aplusb.hpp"
#include "base.hpp"
#include "util/fast_io.hpp"

int main() {
    Printer pr(tmpfile());
    pr.writeln("Hello");
    pr.writeln(string("World"));

    solve_aplusb();
}
