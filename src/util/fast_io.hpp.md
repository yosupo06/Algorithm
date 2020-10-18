---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: src/bimaching.test.cpp
    title: src/bimaching.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/doublingsa.test.cpp
    title: src/doublingsa.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/fenwick_2d_rectangle_sum.test.cpp
    title: src/fenwick_2d_rectangle_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/hashmap.test.cpp
    title: src/hashmap.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/hashmap_remove.test.cpp
    title: src/hashmap_remove.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/hashset_hashmap.test.cpp
    title: src/hashset_hashmap.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/hl_lca.test.cpp
    title: src/hl_lca.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/hl_vertex_add_path_sum.test.cpp
    title: src/hl_vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/hl_vertex_add_subtree_sum.test.cpp
    title: src/hl_vertex_add_subtree_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/inv_of_formal_power_series.test.cpp
    title: src/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/lctree_lca.test.cpp
    title: src/lctree_lca.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/lctree_vertex_add_path_sum.test.cpp
    title: src/lctree_vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/max_clique.test.cpp
    title: src/max_clique.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/nft_convolution.test.cpp
    title: src/nft_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/nimber.test.cpp
    title: src/nimber.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/number_of_substrings.test.cpp
    title: src/number_of_substrings.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/online-zalgo.test.cpp
    title: src/online-zalgo.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/printer.test.cpp
    title: src/printer.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/rollinghash_zalgo.test.cpp
    title: src/rollinghash_zalgo.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/run.test.cpp
    title: src/run.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/sais.test.cpp
    title: src/sais.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/scanner.test.cpp
    title: src/scanner.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/scanner_many_aplusb.test.cpp
    title: src/scanner_many_aplusb.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/staticrangesum_rectangle_sum.test.cpp
    title: src/staticrangesum_rectangle_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/treedecomp_width2.test.cpp
    title: src/treedecomp_width2.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/unionfind.test.cpp
    title: src/unionfind.test.cpp
  - icon: ':heavy_check_mark:'
    path: src/zalgo.test.cpp
    title: src/zalgo.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"src/util/fast_io.hpp\"\n\n#include <unistd.h>\n\nstruct\
    \ Scanner {\n    int fd = -1;\n    char line[(1 << 15) + 1];\n    size_t st =\
    \ 0, ed = 0;\n    void reread() {\n        memmove(line, line + st, ed - st);\n\
    \        ed -= st;\n        st = 0;\n        ed += ::read(fd, line + ed, (1 <<\
    \ 15) - ed);\n        line[ed] = '\\0';\n    }\n    bool succ() {\n        while\
    \ (true) {\n            if (st == ed) {\n                reread();\n         \
    \       if (st == ed) return false;\n            }\n            while (st != ed\
    \ && isspace(line[st])) st++;\n            if (st != ed) break;\n        }\n \
    \       if (ed - st <= 50) {\n            bool sep = false;\n            for (size_t\
    \ i = st; i < ed; i++) {\n                if (isspace(line[i])) {\n          \
    \          sep = true;\n                    break;\n                }\n      \
    \      }\n            if (!sep) reread();\n        }\n        return true;\n \
    \   }\n    template <class T, enable_if_t<is_same<T, string>::value, int> = 0>\n\
    \    bool read_single(T& ref) {\n        if (!succ()) return false;\n        while\
    \ (true) {\n            size_t sz = 0;\n            while (st + sz < ed && !isspace(line[st\
    \ + sz])) sz++;\n            ref.append(line + st, sz);\n            st += sz;\n\
    \            if (!sz || st != ed) break;\n            reread();            \n\
    \        }\n        return true;\n    }\n    template <class T, enable_if_t<is_integral<T>::value,\
    \ int> = 0>\n    bool read_single(T& ref) {\n        if (!succ()) return false;\n\
    \        bool neg = false;\n        if (line[st] == '-') {\n            neg =\
    \ true;\n            st++;\n        }\n        ref = T(0);\n        while (isdigit(line[st]))\
    \ {\n            ref = 10 * ref + (line[st++] & 0xf);\n        }\n        if (neg)\
    \ ref = -ref;\n        return true;\n    }\n    template <class T> bool read_single(V<T>&\
    \ ref) {\n        for (auto& d : ref) {\n            if (!read_single(d)) return\
    \ false;\n        }\n        return true;\n    }\n    void read() {}\n    template\
    \ <class H, class... T> void read(H& h, T&... t) {\n        bool f = read_single(h);\n\
    \        assert(f);\n        read(t...);\n    }\n    Scanner(FILE* fp) : fd(fileno(fp))\
    \ {}\n};\n\nstruct Printer {\n  public:\n    template <bool F = false> void write()\
    \ {}\n    template <bool F = false, class H, class... T>\n    void write(const\
    \ H& h, const T&... t) {\n        if (F) write_single(' ');\n        write_single(h);\n\
    \        write<true>(t...);\n    }\n    template <class... T> void writeln(const\
    \ T&... t) {\n        write(t...);\n        write_single('\\n');\n    }\n\n  \
    \  Printer(FILE* _fp) : fp(_fp) {}\n    ~Printer() { flush(); }\n\n  private:\n\
    \    static constexpr size_t SIZE = 1 << 15;\n    FILE* fp;\n    char line[SIZE],\
    \ small[50];\n    size_t pos = 0;\n    void flush() {\n        fwrite(line, 1,\
    \ pos, fp);\n        pos = 0;\n    }\n    void write_single(const char& val) {\n\
    \        if (pos == SIZE) flush();\n        line[pos++] = val;\n    }\n    template\
    \ <class T, enable_if_t<is_integral<T>::value, int> = 0>\n    void write_single(T\
    \ val) {\n        if (pos > (1 << 15) - 50) flush();\n        if (val == 0) {\n\
    \            write_single('0');\n            return;\n        }\n        if (val\
    \ < 0) {\n            write_single('-');\n            val = -val;  // todo min\n\
    \        }\n        size_t len = 0;\n        while (val) {\n            small[len++]\
    \ = char(0x30 | (val % 10));\n            val /= 10;\n        }\n        for (size_t\
    \ i = 0; i < len; i++) {\n            line[pos + i] = small[len - 1 - i];\n  \
    \      }\n        pos += len;\n    }\n    void write_single(const string& s) {\n\
    \        for (char c : s) write_single(c);\n    }\n    void write_single(const\
    \ char* s) {\n        size_t len = strlen(s);\n        for (size_t i = 0; i <\
    \ len; i++) write_single(s[i]);\n    }\n    template <class T> void write_single(const\
    \ V<T>& val) {\n        auto n = val.size();\n        for (size_t i = 0; i < n;\
    \ i++) {\n            if (i) write_single(' ');\n            write_single(val[i]);\n\
    \        }\n    }\n};\n"
  code: "#pragma once\n\n#include <unistd.h>\n\nstruct Scanner {\n    int fd = -1;\n\
    \    char line[(1 << 15) + 1];\n    size_t st = 0, ed = 0;\n    void reread()\
    \ {\n        memmove(line, line + st, ed - st);\n        ed -= st;\n        st\
    \ = 0;\n        ed += ::read(fd, line + ed, (1 << 15) - ed);\n        line[ed]\
    \ = '\\0';\n    }\n    bool succ() {\n        while (true) {\n            if (st\
    \ == ed) {\n                reread();\n                if (st == ed) return false;\n\
    \            }\n            while (st != ed && isspace(line[st])) st++;\n    \
    \        if (st != ed) break;\n        }\n        if (ed - st <= 50) {\n     \
    \       bool sep = false;\n            for (size_t i = st; i < ed; i++) {\n  \
    \              if (isspace(line[i])) {\n                    sep = true;\n    \
    \                break;\n                }\n            }\n            if (!sep)\
    \ reread();\n        }\n        return true;\n    }\n    template <class T, enable_if_t<is_same<T,\
    \ string>::value, int> = 0>\n    bool read_single(T& ref) {\n        if (!succ())\
    \ return false;\n        while (true) {\n            size_t sz = 0;\n        \
    \    while (st + sz < ed && !isspace(line[st + sz])) sz++;\n            ref.append(line\
    \ + st, sz);\n            st += sz;\n            if (!sz || st != ed) break;\n\
    \            reread();            \n        }\n        return true;\n    }\n \
    \   template <class T, enable_if_t<is_integral<T>::value, int> = 0>\n    bool\
    \ read_single(T& ref) {\n        if (!succ()) return false;\n        bool neg\
    \ = false;\n        if (line[st] == '-') {\n            neg = true;\n        \
    \    st++;\n        }\n        ref = T(0);\n        while (isdigit(line[st]))\
    \ {\n            ref = 10 * ref + (line[st++] & 0xf);\n        }\n        if (neg)\
    \ ref = -ref;\n        return true;\n    }\n    template <class T> bool read_single(V<T>&\
    \ ref) {\n        for (auto& d : ref) {\n            if (!read_single(d)) return\
    \ false;\n        }\n        return true;\n    }\n    void read() {}\n    template\
    \ <class H, class... T> void read(H& h, T&... t) {\n        bool f = read_single(h);\n\
    \        assert(f);\n        read(t...);\n    }\n    Scanner(FILE* fp) : fd(fileno(fp))\
    \ {}\n};\n\nstruct Printer {\n  public:\n    template <bool F = false> void write()\
    \ {}\n    template <bool F = false, class H, class... T>\n    void write(const\
    \ H& h, const T&... t) {\n        if (F) write_single(' ');\n        write_single(h);\n\
    \        write<true>(t...);\n    }\n    template <class... T> void writeln(const\
    \ T&... t) {\n        write(t...);\n        write_single('\\n');\n    }\n\n  \
    \  Printer(FILE* _fp) : fp(_fp) {}\n    ~Printer() { flush(); }\n\n  private:\n\
    \    static constexpr size_t SIZE = 1 << 15;\n    FILE* fp;\n    char line[SIZE],\
    \ small[50];\n    size_t pos = 0;\n    void flush() {\n        fwrite(line, 1,\
    \ pos, fp);\n        pos = 0;\n    }\n    void write_single(const char& val) {\n\
    \        if (pos == SIZE) flush();\n        line[pos++] = val;\n    }\n    template\
    \ <class T, enable_if_t<is_integral<T>::value, int> = 0>\n    void write_single(T\
    \ val) {\n        if (pos > (1 << 15) - 50) flush();\n        if (val == 0) {\n\
    \            write_single('0');\n            return;\n        }\n        if (val\
    \ < 0) {\n            write_single('-');\n            val = -val;  // todo min\n\
    \        }\n        size_t len = 0;\n        while (val) {\n            small[len++]\
    \ = char(0x30 | (val % 10));\n            val /= 10;\n        }\n        for (size_t\
    \ i = 0; i < len; i++) {\n            line[pos + i] = small[len - 1 - i];\n  \
    \      }\n        pos += len;\n    }\n    void write_single(const string& s) {\n\
    \        for (char c : s) write_single(c);\n    }\n    void write_single(const\
    \ char* s) {\n        size_t len = strlen(s);\n        for (size_t i = 0; i <\
    \ len; i++) write_single(s[i]);\n    }\n    template <class T> void write_single(const\
    \ V<T>& val) {\n        auto n = val.size();\n        for (size_t i = 0; i < n;\
    \ i++) {\n            if (i) write_single(' ');\n            write_single(val[i]);\n\
    \        }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/util/fast_io.hpp
  requiredBy: []
  timestamp: '2020-05-24 20:46:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/inv_of_formal_power_series.test.cpp
  - src/unionfind.test.cpp
  - src/doublingsa.test.cpp
  - src/bimaching.test.cpp
  - src/nft_convolution.test.cpp
  - src/hl_vertex_add_path_sum.test.cpp
  - src/treedecomp_width2.test.cpp
  - src/staticrangesum_rectangle_sum.test.cpp
  - src/hashmap_remove.test.cpp
  - src/scanner.test.cpp
  - src/hashmap.test.cpp
  - src/scanner_many_aplusb.test.cpp
  - src/hl_vertex_add_subtree_sum.test.cpp
  - src/hashset_hashmap.test.cpp
  - src/sais.test.cpp
  - src/fenwick_2d_rectangle_sum.test.cpp
  - src/lctree_vertex_add_path_sum.test.cpp
  - src/max_clique.test.cpp
  - src/online-zalgo.test.cpp
  - src/rollinghash_zalgo.test.cpp
  - src/nimber.test.cpp
  - src/lctree_lca.test.cpp
  - src/number_of_substrings.test.cpp
  - src/zalgo.test.cpp
  - src/hl_lca.test.cpp
  - src/printer.test.cpp
  - src/run.test.cpp
documentation_of: src/util/fast_io.hpp
layout: document
redirect_from:
- /library/src/util/fast_io.hpp
- /library/src/util/fast_io.hpp.html
title: src/util/fast_io.hpp
---
