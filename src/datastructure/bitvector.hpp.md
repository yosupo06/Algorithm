---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/bitop.hpp
    title: src/bitop.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: src/math/matrix.hpp
    title: src/math/matrix.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bitop.hpp: line\
    \ -1: no such header\n"
  code: "#pragma once\n\n#include \"bitop.hpp\"\n\nstruct BitVec {\n    static constexpr\
    \ size_t B = 64;\n    size_t n;\n    V<ull> d;\n    explicit BitVec(size_t _n\
    \ = 0) : n(_n), d((n + B - 1) / B) {}\n    void erase_last() {\n        if (n\
    \ % B) d.back() &= ull(-1) >> (B - n % B);\n    }\n    size_t size() const { return\
    \ n; }\n    bool operator[](size_t i) const { return (d[i / B] >> (i % B) & 1)\
    \ != 0; }\n    void set(size_t i, bool f = true) {\n        if (f)\n         \
    \   d[i / B] |= 1ULL << (i % B);\n        else\n            d[i / B] &= ~(1ULL\
    \ << (i % B));\n    }\n    void reset() { fill(d.begin(), d.end(), 0); }\n   \
    \ void reset(size_t i) { set(i, false); }\n    void push_back(bool f) {\n    \
    \    if (n % B == 0) d.push_back(0);\n        set(n, f);\n        n++;\n    }\n\
    \    bool empty() const {\n        for (auto& x : d)\n            if (x) return\
    \ false;\n        return true;\n    }\n\n    size_t bsf() const {\n        auto\
    \ m = d.size();\n        for (size_t i = 0; i < m; i++) {\n            if (d[i])\
    \ return i * B + ::bsf(d[i]);\n        }\n        assert(false);\n    }\n\n  \
    \  size_t count() const {\n        size_t sm = 0;\n        for (auto x : d) sm\
    \ += popcnt(x);\n        return sm;\n    }\n\n    void swap_elms(size_t a, size_t\
    \ b) {\n        bool f = (*this)[a];\n        set(a, (*this)[b]);\n        set(b,\
    \ f);\n    }\n\n    template <class OP> BitVec& op1(OP op) {\n        for (auto&\
    \ x : d) x = op(x);\n        return *this;\n    }\n\n    template <class OP> BitVec&\
    \ op2(const BitVec& r, OP op) {\n        assert(n == r.n);\n        for (size_t\
    \ i = 0; i < d.size(); i++) d[i] = op(d[i], r.d[i]);\n        return *this;\n\
    \    }\n\n    BitVec& flip() {\n        op1(bit_not<ull>());\n        if (n %\
    \ B) d.back() &= ~(-1ULL << (n % B));\n        return *this;\n    }\n    BitVec&\
    \ operator&=(const BitVec& r) { return op2(r, bit_and<ull>()); }\n    BitVec&\
    \ operator|=(const BitVec& r) { return op2(r, bit_or<ull>()); }\n    BitVec& operator^=(const\
    \ BitVec& r) { return op2(r, bit_xor<ull>()); }\n    BitVec& operator<<=(const\
    \ size_t& s) {\n        auto block = s / B, rem = s % B;\n        if (d.size()\
    \ <= block) {\n            reset();\n            return *this;\n        }\n  \
    \      for (size_t i = d.size() - 1; i > block; i--) {\n            if (rem ==\
    \ 0)\n                d[i] = d[i - block];\n            else\n               \
    \ d[i] = d[i - block] << rem | d[i - block - 1] >> (B - rem);\n        }\n   \
    \     d[block] = d[0] << rem;\n        erase_last();\n        fill(d.begin(),\
    \ d.begin() + block, 0ULL);\n        return *this;\n    }\n    BitVec& operator>>=(const\
    \ size_t& s) {\n        auto block = s / B, rem = s % B;\n        if (d.size()\
    \ <= block) {\n            reset();\n            return *this;\n        }\n  \
    \      for (size_t i = 0; i < d.size() - block - 1; i++) {\n            if (rem\
    \ == 0)\n                d[i] = d[i + block];\n            else\n            \
    \    d[i] = d[i + block + 1] << (B - rem) | d[i + block] >> rem;\n        }\n\
    \        d[d.size() - block - 1] = d.back() >> rem;\n        fill(d.begin() +\
    \ d.size() - block, d.end(), 0ULL);\n        return *this;\n    }\n    BitVec&\
    \ operator~() const { return BitVec(*this).flip(); }\n    BitVec operator&(const\
    \ BitVec& r) const { return BitVec(*this) &= r; }\n    BitVec operator|(const\
    \ BitVec& r) const { return BitVec(*this) |= r; }\n    BitVec operator^(const\
    \ BitVec& r) const { return BitVec(*this) ^= r; }\n    BitVec operator<<(const\
    \ size_t& s) const { return BitVec(*this) <<= s; }\n    BitVec operator>>(const\
    \ size_t& s) const { return BitVec(*this) >>= s; }\n\n    BitVec substr(size_t\
    \ st, size_t le) const {\n        assert(st + le <= n);\n        BitVec res(le);\n\
    \        size_t i = 0;\n        while (i < le) {\n            res.d[i / B] |=\
    \ d[(st + i) / B] >> ((st + i) % B) << (i % B);\n            i += min(B - i %\
    \ B, B - (st + i) % B);\n        }\n        res.erase_last();\n        return\
    \ res;\n    }\n    bool substr_match(size_t st, const BitVec& pat) const {\n \
    \       size_t le = pat.size();\n        assert(st + le <= n);\n        size_t\
    \ i = 0;\n        while (i < le) {\n            size_t u = min({le - i, B - i\
    \ % B, B - (st + i) % B});\n            ull z = pat.d[i / B] >> (i % B) ^ d[(st\
    \ + i) / B] >> ((st + i) % B);\n            if (z << (B - u)) return false;\n\
    \            i += u;\n        }\n        return true;\n    }\n\n    bool operator==(const\
    \ BitVec& r) const { return d == r.d; }\n};\nostream& operator<<(ostream& os,\
    \ const BitVec& bs) {\n    os << \"B(\";\n    for (size_t i = 0; i < bs.size();\
    \ i++) {\n        os << bs[i];\n    }\n    return os << \")\";\n}"
  dependsOn:
  - src/bitop.hpp
  isVerificationFile: false
  path: src/datastructure/bitvector.hpp
  requiredBy:
  - src/math/matrix.hpp
  timestamp: '2020-05-22 19:22:07+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/bitvector.hpp
layout: document
redirect_from:
- /library/src/datastructure/bitvector.hpp
- /library/src/datastructure/bitvector.hpp.html
title: src/datastructure/bitvector.hpp
---
