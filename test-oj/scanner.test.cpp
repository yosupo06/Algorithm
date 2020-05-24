#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "base.hpp"
#include "util/fast_io.hpp"

#include "aplusb.hpp"
#include "unistd.h"

void check_separator() {
    auto tmpf = tmpfile();
    fputs(string(1 << 15, 'a').c_str(), tmpf);
    fputs(" ", tmpf);
    fputs(string(1 << 15, 'b').c_str(), tmpf);
    rewind(tmpf);
    Scanner sc(tmpf);
    string s, t;
    sc.read(s, t);
    assert(s == string(1 << 15, 'a'));
    assert(t == string(1 << 15, 'b'));
}

void check_interactive() {
    int pipefd[2];
    assert(pipe(pipefd) == 0);

    Scanner sc(fdopen(pipefd[0], "r"));
    FILE* fw = fdopen(pipefd[1], "w");
    fprintf(fw, "1234\n");
    fflush(fw);
    int x;
    sc.read(x);
    assert(x == 1234);
}

int main() {
    check_separator();
    check_interactive();
    solve_aplusb();
}
