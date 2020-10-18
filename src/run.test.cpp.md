---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: src/base.hpp
    title: src/base.hpp
  - icon: ':heavy_check_mark:'
    path: src/string/run.hpp
    title: src/string/run.hpp
  - icon: ':heavy_check_mark:'
    path: src/string/zalgo.hpp
    title: src/string/zalgo.hpp
  - icon: ':heavy_check_mark:'
    path: src/util/fast_io.hpp
    title: src/util/fast_io.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/runenumerate
    links:
    - https://judge.yosupo.jp/problem/runenumerate
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: base.hpp: line\
    \ -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/runenumerate\"\n\n#include\
    \ \"base.hpp\"\n#include \"util/fast_io.hpp\"\n#include \"string/run.hpp\"\n\n\
    int main() {\n    Scanner sc(stdin);\n    Printer pr(stdout);\n    string s;\n\
    \    sc.read(s);\n    RunExec<string> runexec(s);\n    int m = int(runexec.runs.size());\n\
    \    int n = 0;\n    for (auto v : runexec.runs) n += int(v.size());\n\n    pr.writeln(n);\n\
    \    for (int i = 0; i < m; i++) {\n        auto v = runexec.runs[i];\n      \
    \  sort(v.begin(), v.end());\n        for (auto p : v) {\n            pr.writeln(i,\
    \ p.first, p.second);\n        }\n    }\n    auto runs = RunExec<string>(s);\n\
    }\n"
  dependsOn:
  - src/base.hpp
  - src/util/fast_io.hpp
  - src/string/run.hpp
  - src/string/zalgo.hpp
  isVerificationFile: true
  path: src/run.test.cpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/run.test.cpp
layout: document
redirect_from:
- /verify/src/run.test.cpp
- /verify/src/run.test.cpp.html
title: src/run.test.cpp
---
