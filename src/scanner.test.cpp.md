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
    path: src/util/fast_io.hpp
    title: src/util/fast_io.hpp
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
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: unistd.h: line\
    \ -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    base.hpp\"\n#include \"util/fast_io.hpp\"\n\n#include \"aplusb.hpp\"\n#include\
    \ \"unistd.h\"\n\nvoid check_separator() {\n    auto tmpf = tmpfile();\n    fputs(string(1\
    \ << 15, 'a').c_str(), tmpf);\n    fputs(\" \", tmpf);\n    fputs(string(1 <<\
    \ 15, 'b').c_str(), tmpf);\n    rewind(tmpf);\n    Scanner sc(tmpf);\n    string\
    \ s, t;\n    sc.read(s, t);\n    assert(s == string(1 << 15, 'a'));\n    assert(t\
    \ == string(1 << 15, 'b'));\n}\n\nvoid check_interactive() {\n    int pipefd[2];\n\
    \    assert(pipe(pipefd) == 0);\n\n    Scanner sc(fdopen(pipefd[0], \"r\"));\n\
    \    FILE* fw = fdopen(pipefd[1], \"w\");\n    fprintf(fw, \"1234\\n\");\n   \
    \ fflush(fw);\n    int x;\n    sc.read(x);\n    assert(x == 1234);\n}\n\nint main()\
    \ {\n    check_separator();\n    check_interactive();\n    solve_aplusb();\n}\n"
  dependsOn:
  - src/base.hpp
  - src/util/fast_io.hpp
  - src/aplusb.hpp
  isVerificationFile: true
  path: src/scanner.test.cpp
  requiredBy: []
  timestamp: '2020-10-18 20:05:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/scanner.test.cpp
layout: document
redirect_from:
- /verify/src/scanner.test.cpp
- /verify/src/scanner.test.cpp.html
title: src/scanner.test.cpp
---
