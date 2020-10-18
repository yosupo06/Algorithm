---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/util/stopwatch.hpp\"\nstruct StopWatch {\n    bool f\
    \ = false;\n    clock_t st;\n    void start() {\n        f = true;\n        st\
    \ = clock();\n    }\n    int msecs() {\n        assert(f);\n        return (clock()-st)*1000\
    \ / CLOCKS_PER_SEC;\n    }\n};\n"
  code: "struct StopWatch {\n    bool f = false;\n    clock_t st;\n    void start()\
    \ {\n        f = true;\n        st = clock();\n    }\n    int msecs() {\n    \
    \    assert(f);\n        return (clock()-st)*1000 / CLOCKS_PER_SEC;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/util/stopwatch.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/util/stopwatch.hpp
layout: document
redirect_from:
- /library/src/util/stopwatch.hpp
- /library/src/util/stopwatch.hpp.html
title: src/util/stopwatch.hpp
---
