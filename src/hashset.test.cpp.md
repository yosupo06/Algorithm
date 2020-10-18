---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/aplusb.hpp
    title: src/aplusb.hpp
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/datastructure/hashset.hpp
    title: src/datastructure/hashset.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/hash.hpp
    title: src/util/hash.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/random.hpp
    title: src/util/random.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: util/hash.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    base.hpp\"\n#include \"aplusb.hpp\"\n#include \"datastructure/hashset.hpp\"\n\n\
    int main() {\n    HashSet<ll> st;\n\n    for (int i = 0; i < 100; i++) {\n   \
    \     st.insert(i);\n        assert(int(st.size()) == i + 1);\n    }\n    auto\
    \ actual = st.to_vec();\n    sort(actual.begin(), actual.end());\n    V<int> expect(100);\n\
    \    iota(expect.begin(), expect.end(), 0);\n    assert(expect == actual);\n \
    \   solve_aplusb();\n    return 0;\n}\n"
  dependsOn:
  - src/base.hpp
  - src/aplusb.hpp
  - src/datastructure/hashset.hpp
  - src/util/hash.hpp
  - src/util/random.hpp
  isVerificationFile: true
  path: src/hashset.test.cpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/hashset.test.cpp
layout: document
redirect_from:
- /verify/src/hashset.test.cpp
- /verify/src/hashset.test.cpp.html
title: src/hashset.test.cpp
---
