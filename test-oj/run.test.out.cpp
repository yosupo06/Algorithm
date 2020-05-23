



#include <algorithm>

#include <array>

#include <bitset>

#include <cassert>

#include <complex>

#include <cstdio>

#include <cstring>

#include <iostream>

#include <map>

#include <numeric>

#include <queue>

#include <set>

#include <string>

#include <unordered_map>

#include <unordered_set>

#include <vector>

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

struct Scanner {
    FILE* fp = nullptr;
    char line[(1 << 15) + 1];
    size_t st = 0, ed = 0;
    void reread() {
        memmove(line, line + st, ed - st);
        ed -= st;
        st = 0;
        ed += fread(line + ed, 1, (1 << 15) - ed, fp);
        line[ed] = '\0';
    }
    bool succ() {
        while (true) {
            if (st == ed) {
                reread();
                if (st == ed) return false;
            }
            while (st != ed && isspace(line[st])) st++;
            if (st != ed) break;
        }
        if (ed - st <= 50) reread();
        return true;
    }
    template <class T, enable_if_t<is_same<T, string>::value, int> = 0>
    bool read_single(T& ref) {
        if (!succ()) return false;
        while (true) {
            size_t sz = 0;
            while (st + sz < ed && !isspace(line[st + sz])) sz++;
            ref.append(line + st, sz);
            st += sz;
            if (!sz || st != ed) break;
            reread();
        }
        return true;
    }
    template <class T, enable_if_t<is_integral<T>::value, int> = 0>
    bool read_single(T& ref) {
        if (!succ()) return false;
        bool neg = false;
        if (line[st] == '-') {
            neg = true;
            st++;
        }
        ref = T(0);
        while (isdigit(line[st])) {
            ref = 10 * ref + (line[st++] - '0');
        }
        if (neg) ref = -ref;
        return true;
    }
    template <class T> bool read_single(V<T>& ref) {
        for (auto& d : ref) {
            if (!read_single(d)) return false;
        }
        return true;
    }
    void read() {}
    template <class H, class... T> void read(H& h, T&... t) {
        bool f = read_single(h);
        assert(f);
        read(t...);
    }
    Scanner(FILE* _fp) : fp(_fp) {}
};

struct Printer {
  public:
    template <bool F = false> void write() {}
    template <bool F = false, class H, class... T>
    void write(const H& h, const T&... t) {
        if (F) write_single(' ');
        write_single(h);
        write<true>(t...);
    }
    template <class... T> void writeln(const T&... t) {
        write(t...);
        write_single('\n');
    }

    Printer(FILE* _fp) : fp(_fp) {}
    ~Printer() { flush(); }

  private:
    static constexpr size_t SIZE = 1 << 15;
    FILE* fp;
    char line[SIZE], small[50];
    size_t pos = 0;
    void flush() {
        fwrite(line, 1, pos, fp);
        pos = 0;
    }
    void write_single(const char& val) {
        if (pos == SIZE) flush();
        line[pos++] = val;
    }
    template <class T, enable_if_t<is_integral<T>::value, int> = 0>
    void write_single(T val) {
        if (pos > (1 << 15) - 50) flush();
        if (val == 0) {
            write_single('0');
            return;
        }
        if (val < 0) {
            write_single('-');
            val = -val; // todo min
        }
        size_t len = 0;
        while (val) {
            small[len++] = char('0' + (val % 10));
            val /= 10;
        }
        for (size_t i = 0; i < len; i++) {
            line[pos + i] = small[len - 1 - i];
        }
        pos += len;
    }
    void write_single(const string& s) {
        for (char c : s) write_single(c);
    }
    void write_single(const char* s) {
        size_t len = strlen(s);
        for (size_t i = 0; i < len; i++) write_single(s[i]);
    }
    template <class T> void write_single(const V<T>& val) {
        auto n = val.size();
        for (size_t i = 0; i < n; i++) {
            if (i) write_single(' ');
            write_single(val[i]);
        }
    }
};





// s[0..r[i]] == s[i..i+r[i]]
template <class S> V<int> z_algo(const S& s) {
    int n = int(s.size());
    V<int> r(n + 1);
    r[0] = 0;
    for (int i = 1, j = 0; i <= n; i++) {
        int& k = r[i];
        k = (j + r[j] <= i) ? 0 : min(j + r[j] - i, r[i - j]);
        while (i + k < n && s[k] == s[i + k]) k++;
        if (j + r[j] < i + r[i]) j = i;
    }
    r[0] = n;
    return r;
}

template<class Str>
struct RunExec {
    VV<pair<int, int>> runs;

    int n;
    Str a;

    V<int> rev(V<int> l) {
        reverse(l.begin(), l.end());
        return l;
    }

    V<int> sub_a(int l, int r) { return {a.begin() + l, a.begin() + r}; }
    V<int> concat(V<int> l, const V<int>& r) {
        l.insert(l.end(), r.begin(), r.end());
        return l;
    }

    void run(int l, int r, int f) {
        if (l + 1 == r) return;
        int md = (l + r + f) / 2;
        run(l, md, f);
        run(md, r, f);
        auto z1 = z_algo(rev(sub_a(l, md)));
        auto z2 = z_algo(concat(sub_a(md, r), sub_a(l, r)));
        for (int i = md - 1; i >= l; i--) {
            int l1 = min(i - l, z1[md - i]);
            int l2 = min(r - md, z2[(r - l) - (md - i)]);
            int le = i - l1, ri = md + l2, peri = md - i;
            if (ri - le >= 2 * peri) runs[md - i].push_back({i - l1, md + l2});
        }
    }

    RunExec(Str _a) : a(_a) {
        n = int(a.size());
        runs.resize(n / 2 + 1);
        reverse(a.begin(), a.end());
        run(0, n, 0);
        for (auto& run : runs) {
            for (auto& p : run) {
                tie(p.first, p.second) = make_pair(n - p.second, n - p.first);
            }
        }
        reverse(a.begin(), a.end());
        run(0, n, 1);

        set<pair<int, int>> vis;
        for (int ph = 1; ph <= n / 2; ph++) {
            auto& run = runs[ph];
            sort(run.begin(), run.end(),
                 [&](pair<int, int> lhs, pair<int, int> rhs) {
                     if (lhs.first != rhs.first) return lhs.first < rhs.first;
                     return lhs.second > rhs.second;
                 });
            V<pair<int, int>> res;
            for (auto p : run) {
                if (!res.empty() && p.second <= res.back().second) continue;
                res.push_back(p);
            }
            run = res;
            res.clear();
            for (auto p : run) {
                if (vis.count(p)) continue;
                vis.insert(p);
                res.push_back(p);
            }
            run = res;
        }
    }
};

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
