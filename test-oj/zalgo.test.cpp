#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../src/base.h"
#include "../src/string/zalgo.h"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    auto z = z_algo(s);
    int n = int(s.size());
    for (int i = 0; i < n; i++) cout << z[i] << " ";
    cout << endl;
}
