---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/util/stack_extend.hpp\"\n// stack size\u3092\u62E1\u5F35\
    \u3059\u308B 64bit\u7528\nint main() {\n    static ll eord, enew;\n    const int\
    \ sz = 256*1024*1024;\n    static unsigned char *p = (unsigned char*)malloc(sz);\n\
    \    enew = ((ll)(p+sz-1) & ~0xff);\n    __asm__ volatile(\"mov %%rsp, %0\" :\
    \ \"=r\"(eord));\n    __asm__ volatile(\"mov %0, %%rsp\" : : \"r\"(enew));\n \
    \   main2();\n    __asm__ volatile(\"mov %0, %%rsp\" : : \"r\"(eord));\n    return\
    \ 0;\n}\n"
  code: "// stack size\u3092\u62E1\u5F35\u3059\u308B 64bit\u7528\nint main() {\n \
    \   static ll eord, enew;\n    const int sz = 256*1024*1024;\n    static unsigned\
    \ char *p = (unsigned char*)malloc(sz);\n    enew = ((ll)(p+sz-1) & ~0xff);\n\
    \    __asm__ volatile(\"mov %%rsp, %0\" : \"=r\"(eord));\n    __asm__ volatile(\"\
    mov %0, %%rsp\" : : \"r\"(enew));\n    main2();\n    __asm__ volatile(\"mov %0,\
    \ %%rsp\" : : \"r\"(eord));\n    return 0;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: src/util/stack_extend.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/util/stack_extend.hpp
layout: document
redirect_from:
- /library/src/util/stack_extend.hpp
- /library/src/util/stack_extend.hpp.html
title: src/util/stack_extend.hpp
---
