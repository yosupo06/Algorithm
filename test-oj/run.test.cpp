#define PROBLEM "https://judge.yosupo.jp/problem/runenumerate"

#include "base.hpp"
#include "util/fast_io.hpp"
#include "string/run.hpp"

int main() {
    Scanner sc(stdin);
    Printer pr(stdout);
    string s;
    sc.read(s);
    RunExec<string> runexec(s);
    int m = int(runexec.runs.size());
    int n = 0;
    for (auto v : runexec.runs) n += int(v.size());

    pr.writeln(n);
    for (int i = 0; i < m; i++) {
        auto v = runexec.runs[i];
        sort(v.begin(), v.end());
        for (auto p : v) {
            pr.writeln(i, p.first, p.second);
        }
    }
    auto runs = RunExec<string>(s);
}
