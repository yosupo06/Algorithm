#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "base.hpp"
#include "util/fast_io.hpp"

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

int main() {
    check_separator();
    int a, b;
    cin >> a >> b;
    cout << a + b << endl;
}
