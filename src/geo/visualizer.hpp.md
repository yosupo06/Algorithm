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
  bundledCode: "#line 1 \"src/geo/visualizer.hpp\"\nstruct Vis {\n    struct Col {\n\
    \        int r, g, b;\n    };\n    FILE* fp;\n    D off, f;\n    Vis(string s,\
    \ D d, D u) : off(d), f(1000 / (u - d)) {\n        fp = fopen(s.c_str(), \"w\"\
    );\n        fprintf(\n                fp,\n                \"<html><head><script>\"\
    \n                \"onload = function draw() {\"\n                \"var cv = document.getElementById('c');\"\
    \n                \"var ct = cv.getContext('2d');\");\n    }\n    D norm(D x)\
    \ { return (x - off) * f; }\n    void set_col(Col c) {\n        fprintf(fp, \"\
    ct.fillStyle = \\\"rgb(%d, %d, %d)\\\";\", c.r, c.g, c.b);\n        fprintf(fp,\
    \ \"ct.strokeStyle = \\\"rgb(%d, %d, %d)\\\";\", c.r, c.g, c.b);\n    }\n    void\
    \ line(L l, Col col = {0, 0, 0}) {\n        set_col(col);\n        fprintf(fp,\n\
    \                \"ct.beginPath();\"\n                \"ct.moveTo(%Lf, %Lf);\"\
    \n                \"ct.lineTo(%Lf, %Lf);\"\n                \"ct.closePath();\"\
    \n                \"ct.stroke();\",\n                norm(l.s.x), norm(l.s.y),\
    \ norm(l.t.x), norm(l.t.y));\n    }\n    void point(P p, Col col = {0, 0, 0})\
    \ {\n        set_col(col);\n        fprintf(fp,\n                \"ct.beginPath();\"\
    \n                \"ct.arc(%Lf, %Lf, 2, 0, Math.PI * 2, true);\"\n           \
    \     \"ct.fill();\",\n                norm(p.x), norm(p.y));\n    }\n    ~Vis()\
    \ {\n        fprintf(fp,\n                \"}</script></head><body>\"\n      \
    \          \"<canvas id=\\\"c\\\" width=\\\"1000\\\" height=\\\"1000\\\">\"\n\
    \                \"</canvas></body></html>\");\n        fclose(fp);\n    }\n};\n"
  code: "struct Vis {\n    struct Col {\n        int r, g, b;\n    };\n    FILE* fp;\n\
    \    D off, f;\n    Vis(string s, D d, D u) : off(d), f(1000 / (u - d)) {\n  \
    \      fp = fopen(s.c_str(), \"w\");\n        fprintf(\n                fp,\n\
    \                \"<html><head><script>\"\n                \"onload = function\
    \ draw() {\"\n                \"var cv = document.getElementById('c');\"\n   \
    \             \"var ct = cv.getContext('2d');\");\n    }\n    D norm(D x) { return\
    \ (x - off) * f; }\n    void set_col(Col c) {\n        fprintf(fp, \"ct.fillStyle\
    \ = \\\"rgb(%d, %d, %d)\\\";\", c.r, c.g, c.b);\n        fprintf(fp, \"ct.strokeStyle\
    \ = \\\"rgb(%d, %d, %d)\\\";\", c.r, c.g, c.b);\n    }\n    void line(L l, Col\
    \ col = {0, 0, 0}) {\n        set_col(col);\n        fprintf(fp,\n           \
    \     \"ct.beginPath();\"\n                \"ct.moveTo(%Lf, %Lf);\"\n        \
    \        \"ct.lineTo(%Lf, %Lf);\"\n                \"ct.closePath();\"\n     \
    \           \"ct.stroke();\",\n                norm(l.s.x), norm(l.s.y), norm(l.t.x),\
    \ norm(l.t.y));\n    }\n    void point(P p, Col col = {0, 0, 0}) {\n        set_col(col);\n\
    \        fprintf(fp,\n                \"ct.beginPath();\"\n                \"\
    ct.arc(%Lf, %Lf, 2, 0, Math.PI * 2, true);\"\n                \"ct.fill();\",\n\
    \                norm(p.x), norm(p.y));\n    }\n    ~Vis() {\n        fprintf(fp,\n\
    \                \"}</script></head><body>\"\n                \"<canvas id=\\\"\
    c\\\" width=\\\"1000\\\" height=\\\"1000\\\">\"\n                \"</canvas></body></html>\"\
    );\n        fclose(fp);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/geo/visualizer.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/geo/visualizer.hpp
layout: document
redirect_from:
- /library/src/geo/visualizer.hpp
- /library/src/geo/visualizer.hpp.html
title: src/geo/visualizer.hpp
---
