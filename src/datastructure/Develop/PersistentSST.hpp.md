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
  bundledCode: "#line 1 \"src/datastructure/Develop/PersistentSST.hpp\"\nstruct Node\
    \ {\n    using NP = const Node*;\n\n    int ma, lz;\n\n    /*\n     init_node,\
    \ update, push\n    */\n    void init_node() {\n        ma = lz = 0;\n    }\n\
    \    void update() {\n        ma = max(l->ma, r->ma);\n    }\n    void push()\
    \ {\n        if (!lz) continue;\n        auto nl = make(l);\n        auto nr =\
    \ make(r);\n        if (lz) {\n            nl->lzdata(lz);\n            nr->lzdata(lz);\n\
    \            lz = 0;\n        }\n        l = nl;\n        r = nr;\n    }\n   \
    \ /// push\u306Fconst\u306B\u95A2\u308F\u3089\u305A\u547C\u3093\u3067\u826F\u3044\
    \n    void push() const {\n        const_cast<Node*>(this)->push();\n    }\n \
    \   void lzdata(int x) {\n        ma += x;\n        lz += x;\n    }\n\n    NP\
    \ add(int a, int b, int x) const {\n        if (b <= 0 or sz <= a) return this;\n\
    \        if (a <= 0 and sz <= b) {\n            auto n = make(this);\n       \
    \     n->lzdata(x);\n            return n;\n        }\n        push();\n     \
    \   auto n = make(this);\n        auto n->l = l->add(a, b, x);\n        auto n->r\
    \ = r->add(a - sz/2, b - sz/2, x);\n        n->update();\n        return n;\n\
    \    }\n    int get(int a, int b) const {\n        if (b <= 0 or sz <= a) return\
    \ -1;\n        if (a <= 0 and sz <= b) {\n            return ma;\n        }\n\
    \        push();\n        return max(l->get(a, b), r->get(a-sz/2, b-sz/2));\n\
    \    }\n\n    NP l, r;\n    int sz;\n    Node() {}\n    Node(int sz) : sz(sz)\
    \ {\n        init_node();\n        if (sz == 1) return;\n        l = new Node(sz/2);\n\
    \        r = new Node(sz - sz/2);\n        update();\n    }\n    static Node*\
    \ make(NP x) {\n        auto n = new Node();\n        *n = *x;\n        return\
    \ n;\n    }\n};\n"
  code: "struct Node {\n    using NP = const Node*;\n\n    int ma, lz;\n\n    /*\n\
    \     init_node, update, push\n    */\n    void init_node() {\n        ma = lz\
    \ = 0;\n    }\n    void update() {\n        ma = max(l->ma, r->ma);\n    }\n \
    \   void push() {\n        if (!lz) continue;\n        auto nl = make(l);\n  \
    \      auto nr = make(r);\n        if (lz) {\n            nl->lzdata(lz);\n  \
    \          nr->lzdata(lz);\n            lz = 0;\n        }\n        l = nl;\n\
    \        r = nr;\n    }\n    /// push\u306Fconst\u306B\u95A2\u308F\u3089\u305A\
    \u547C\u3093\u3067\u826F\u3044\n    void push() const {\n        const_cast<Node*>(this)->push();\n\
    \    }\n    void lzdata(int x) {\n        ma += x;\n        lz += x;\n    }\n\n\
    \    NP add(int a, int b, int x) const {\n        if (b <= 0 or sz <= a) return\
    \ this;\n        if (a <= 0 and sz <= b) {\n            auto n = make(this);\n\
    \            n->lzdata(x);\n            return n;\n        }\n        push();\n\
    \        auto n = make(this);\n        auto n->l = l->add(a, b, x);\n        auto\
    \ n->r = r->add(a - sz/2, b - sz/2, x);\n        n->update();\n        return\
    \ n;\n    }\n    int get(int a, int b) const {\n        if (b <= 0 or sz <= a)\
    \ return -1;\n        if (a <= 0 and sz <= b) {\n            return ma;\n    \
    \    }\n        push();\n        return max(l->get(a, b), r->get(a-sz/2, b-sz/2));\n\
    \    }\n\n    NP l, r;\n    int sz;\n    Node() {}\n    Node(int sz) : sz(sz)\
    \ {\n        init_node();\n        if (sz == 1) return;\n        l = new Node(sz/2);\n\
    \        r = new Node(sz - sz/2);\n        update();\n    }\n    static Node*\
    \ make(NP x) {\n        auto n = new Node();\n        *n = *x;\n        return\
    \ n;\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: src/datastructure/Develop/PersistentSST.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/datastructure/Develop/PersistentSST.hpp
layout: document
redirect_from:
- /library/src/datastructure/Develop/PersistentSST.hpp
- /library/src/datastructure/Develop/PersistentSST.hpp.html
title: src/datastructure/Develop/PersistentSST.hpp
---
