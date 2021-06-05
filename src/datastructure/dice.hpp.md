---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/datastructure/dice.hpp\"\n/**\n * +x=0 +y=1 +z=2\n *\
    \ d = [+x, +y, +z]\n * dir[4] = [+x, +y, -x, -y]\n * Dice(a, b): +x=a +y=b\u3068\
    \u306A\u308B\u30B5\u30A4\u30B3\u30ED\u751F\u6210\n * get(dir): dir\u65B9\u5411\
    \u306E\u5024\u3092\u53D6\u5F97\n * rot(dir): dir\u65B9\u5411\u306B\u8EE2\u304C\
    \u3059\n */\nstruct Dice {\n    int d[3];\n    Dice(int a, int b) {\n        for\
    \ (int i = 0; i < 3; i++) {\n            d[i] = (a + i) % 3 + a / 3 * 3;\n   \
    \     }\n        while (d[1] != b) rot(1);\n    }\n    int get(int dir) {\n  \
    \      if (dir < 2) {\n            return d[dir];\n        } else {\n        \
    \    dir -= 2;\n            return 5 - d[dir];\n        }\n    }\n    void rot(int\
    \ dir) {\n        int t = d[2];\n        if (dir < 2) {\n            d[2] = 5\
    \ - d[dir];\n            d[dir] = t;\n        } else {\n            dir -= 2;\n\
    \            d[2] = d[dir];\n            d[dir] = 5 - t;\n        }\n    }\n};\n"
  code: "/**\n * +x=0 +y=1 +z=2\n * d = [+x, +y, +z]\n * dir[4] = [+x, +y, -x, -y]\n\
    \ * Dice(a, b): +x=a +y=b\u3068\u306A\u308B\u30B5\u30A4\u30B3\u30ED\u751F\u6210\
    \n * get(dir): dir\u65B9\u5411\u306E\u5024\u3092\u53D6\u5F97\n * rot(dir): dir\u65B9\
    \u5411\u306B\u8EE2\u304C\u3059\n */\nstruct Dice {\n    int d[3];\n    Dice(int\
    \ a, int b) {\n        for (int i = 0; i < 3; i++) {\n            d[i] = (a +\
    \ i) % 3 + a / 3 * 3;\n        }\n        while (d[1] != b) rot(1);\n    }\n \
    \   int get(int dir) {\n        if (dir < 2) {\n            return d[dir];\n \
    \       } else {\n            dir -= 2;\n            return 5 - d[dir];\n    \
    \    }\n    }\n    void rot(int dir) {\n        int t = d[2];\n        if (dir\
    \ < 2) {\n            d[2] = 5 - d[dir];\n            d[dir] = t;\n        } else\
    \ {\n            dir -= 2;\n            d[2] = d[dir];\n            d[dir] = 5\
    \ - t;\n        }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/dice.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/dice.hpp
layout: document
redirect_from:
- /library/src/datastructure/dice.hpp
- /library/src/datastructure/dice.hpp.html
title: src/datastructure/dice.hpp
---
