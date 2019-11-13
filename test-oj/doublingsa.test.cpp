#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "../src/base.h"
#include "../src/string/suffixarray.h"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    auto sa = doublingSA(s);
    int n = int(s.size());
    for (int i = 1; i <= n; i++) cout << sa[i] << " ";
    cout << endl;
}
