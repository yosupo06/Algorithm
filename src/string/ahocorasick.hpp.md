---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"src/string/ahocorasick.hpp\"\nstruct ACTrie {\n    using\
    \ NP = ACTrie*;\n    V<int> acc;\n    map<int, NP> next;\n    NP fail = nullptr,\
    \ dnx = nullptr;\n\n  private:\n    void add(const string& s, int id, int p =\
    \ 0) {\n        if (p == int(s.size())) {\n            acc.push_back(id);\n  \
    \          return;\n        }\n        if (next[s[p]] == nullptr) {\n        \
    \    next[s[p]] = new ACTrie();\n        }\n        next[s[p]]->add(s, id, p +\
    \ 1);\n    }\n    template <class OP> NP count(OP op, int p) {\n        if (fail\
    \ == nullptr) return this;\n        for (int id : acc) {\n            op(id, p);\n\
    \        }\n        if (dnx) {\n            dnx->count(op, p);\n        } else\
    \ {\n            dnx = fail->count(op, p);\n        }\n        return acc.size()\
    \ ? this : dnx;\n    }\n\n  public:\n    // \u30D1\u30BF\u30FC\u30F3\u306B\u30DE\
    \u30C3\u30C1\u3059\u308B\u305F\u3073\u306Bop(string ID, \u767A\u898B\u4F4D\u7F6E\
    \u306E\u7D42\u7AEF)\u3092\u547C\u3073\u51FA\u3059\n    // \u7D42\u7AEF\u304C\u540C\
    \u3058\u3067\u8907\u6570\u30DE\u30C3\u30C1\u3059\u308B\u6587\u5B57\u5217\u304C\
    \u5B58\u5728\u3059\u308B\u5834\u5408\uFF0C\u9577\u3044\u9806\u306B\u547C\u3073\
    \u51FA\u3055\u308C\u308B\n    // s = \"abaaba\", pattern = {\"ab\", \"ba\"} \u306A\
    \u3089\n    // op(0, 2), op(1, 3), op(0, 5), op(1, 6)\n    template <class OP>\
    \ void match(const string& s, OP op, int p = 0) {\n        if (p == int(s.size()))\
    \ return;\n        if (next[s[p]]) {\n            next[s[p]]->count(op, p + 1);\n\
    \            next[s[p]]->match(s, op, p + 1);\n        } else {\n            if\
    \ (!fail)\n                match(s, op, p + 1);  // root\n            else\n \
    \               fail->match(s, op, p);  // other\n        }\n    }\n    static\
    \ NP make(V<string> v) {\n        NP tr = new ACTrie();\n        for (int i =\
    \ 0; i < int(v.size()); i++) {\n            tr->add(v[i], i);\n        }\n   \
    \     queue<NP> q;\n        q.push(tr);\n        tr->fail = nullptr;\n       \
    \ while (!q.empty()) {\n            NP ntr = q.front();\n            q.pop();\n\
    \            for (auto p : ntr->next) {\n                int i = p.first;\n  \
    \              NP fail = ntr->fail;\n                while (fail && !fail->next.count(i))\
    \ {\n                    fail = fail->fail;\n                }\n             \
    \   ntr->next[i]->fail = (fail == nullptr) ? tr : fail->next[i];\n           \
    \     q.push(ntr->next[i]);\n            }\n        }\n        return tr;\n  \
    \  }\n};\n"
  code: "struct ACTrie {\n    using NP = ACTrie*;\n    V<int> acc;\n    map<int, NP>\
    \ next;\n    NP fail = nullptr, dnx = nullptr;\n\n  private:\n    void add(const\
    \ string& s, int id, int p = 0) {\n        if (p == int(s.size())) {\n       \
    \     acc.push_back(id);\n            return;\n        }\n        if (next[s[p]]\
    \ == nullptr) {\n            next[s[p]] = new ACTrie();\n        }\n        next[s[p]]->add(s,\
    \ id, p + 1);\n    }\n    template <class OP> NP count(OP op, int p) {\n     \
    \   if (fail == nullptr) return this;\n        for (int id : acc) {\n        \
    \    op(id, p);\n        }\n        if (dnx) {\n            dnx->count(op, p);\n\
    \        } else {\n            dnx = fail->count(op, p);\n        }\n        return\
    \ acc.size() ? this : dnx;\n    }\n\n  public:\n    // \u30D1\u30BF\u30FC\u30F3\
    \u306B\u30DE\u30C3\u30C1\u3059\u308B\u305F\u3073\u306Bop(string ID, \u767A\u898B\
    \u4F4D\u7F6E\u306E\u7D42\u7AEF)\u3092\u547C\u3073\u51FA\u3059\n    // \u7D42\u7AEF\
    \u304C\u540C\u3058\u3067\u8907\u6570\u30DE\u30C3\u30C1\u3059\u308B\u6587\u5B57\
    \u5217\u304C\u5B58\u5728\u3059\u308B\u5834\u5408\uFF0C\u9577\u3044\u9806\u306B\
    \u547C\u3073\u51FA\u3055\u308C\u308B\n    // s = \"abaaba\", pattern = {\"ab\"\
    , \"ba\"} \u306A\u3089\n    // op(0, 2), op(1, 3), op(0, 5), op(1, 6)\n    template\
    \ <class OP> void match(const string& s, OP op, int p = 0) {\n        if (p ==\
    \ int(s.size())) return;\n        if (next[s[p]]) {\n            next[s[p]]->count(op,\
    \ p + 1);\n            next[s[p]]->match(s, op, p + 1);\n        } else {\n  \
    \          if (!fail)\n                match(s, op, p + 1);  // root\n       \
    \     else\n                fail->match(s, op, p);  // other\n        }\n    }\n\
    \    static NP make(V<string> v) {\n        NP tr = new ACTrie();\n        for\
    \ (int i = 0; i < int(v.size()); i++) {\n            tr->add(v[i], i);\n     \
    \   }\n        queue<NP> q;\n        q.push(tr);\n        tr->fail = nullptr;\n\
    \        while (!q.empty()) {\n            NP ntr = q.front();\n            q.pop();\n\
    \            for (auto p : ntr->next) {\n                int i = p.first;\n  \
    \              NP fail = ntr->fail;\n                while (fail && !fail->next.count(i))\
    \ {\n                    fail = fail->fail;\n                }\n             \
    \   ntr->next[i]->fail = (fail == nullptr) ? tr : fail->next[i];\n           \
    \     q.push(ntr->next[i]);\n            }\n        }\n        return tr;\n  \
    \  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/string/ahocorasick.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/string/ahocorasick.hpp
layout: document
redirect_from:
- /library/src/string/ahocorasick.hpp
- /library/src/string/ahocorasick.hpp.html
title: src/string/ahocorasick.hpp
---
