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
  bundledCode: "#line 1 \"src/geo/graphiccompute.hpp\"\n/*\nreturn arg(l) < arg(r)\n\
    arg(-1, 0) = PI, arg(0, 0) = arg(1, 0) = 0\n*/\nint argcmp(P l, P r) {\n    auto\
    \ psgn = [&](P p) {\n        if (int u = sgn(p.y)) return u;\n        if (sgn(p.x)\
    \ == -1) return 2;\n        return 0;\n    };\n    int lsgn = psgn(l), rsgn =\
    \ psgn(r);\n    if (lsgn < rsgn) return -1;\n    if (lsgn > rsgn) return 1;\n\
    \    return sgncrs(r, l);\n}\n\nV<L> halfplane_intersects(V<L> lines) {\n    sort(lines.begin(),\
    \ lines.end(), [&](const L& a, const L& b) {\n        if (int u = argcmp(a.vec(),\
    \ b.vec())) return u == -1;\n        return sgncrs(a.vec(), b.s - a.s) < 0;\n\
    \    });\n    lines.erase(unique(lines.begin(), lines.end(),\n               \
    \        [&](const L& a, const L& b) {\n                           return argcmp(a.vec(),\
    \ b.vec()) == 0;\n                       }),\n                lines.end());\n\n\
    \    deque<L> st;\n    for (auto l : lines) {\n        bool err = false;\n   \
    \     auto is_need = [&](L a, L b, L c) {\n            D ab_dw = crs(a.vec(),\
    \ b.vec()), ab_up = crs(a.vec(), a.t - b.s);\n            D bc_dw = crs(b.vec(),\
    \ c.vec()), bc_up = crs(c.t - b.s, c.vec());\n            if (ab_dw <= 0 || bc_dw\
    \ <= 0) return true;\n            bool f = bc_up * ab_dw > bc_dw * ab_up;\n  \
    \          if (!f && crs(a.vec(), c.vec()) < 0) err = true;\n            return\
    \ f;\n        };\n        while (st.size() >= 2 && !is_need(l, st[0], st[1]))\
    \ st.pop_front();\n        while (st.size() >= 2 &&\n               !is_need(st[st.size()\
    \ - 2], st[st.size() - 1], l))\n            st.pop_back();\n        if (st.size()\
    \ < 2 || is_need(st.back(), l, st.front())) st.push_back(l);\n        if (err)\
    \ return {};\n    }\n    if (st.size() == 2 && !sgncrs(st[0].vec(), st[1].vec())\
    \ &&\n        sgncrs(st[0].vec(), st[1].s - st[0].s) <= 0)\n        return {};\n\
    \n    return V<L>(st.begin(), st.end());\n}\n\nstruct Arrange {\n    V<P> ps;\n\
    \    VV<int> g;\n    Arrange(const V<L>& l) {\n        int n = int(l.size());\n\
    \        for (int i = 0; i < n; i++) {\n            ps.push_back(l[i].s);\n  \
    \          ps.push_back(l[i].t);\n            for (int j = i + 1; j < n; j++)\
    \ {\n                P p;\n                if (crossSS(l[i], l[j], p) != 1) continue;\n\
    \                ps.push_back(p);\n            }\n        }\n        sort(ps.begin(),\
    \ ps.end());\n        ps.erase(unique(ps.begin(), ps.end()), ps.end());\n    \
    \    int m = int(ps.size());\n        g = VV<int>(m);\n        for (int i = 0;\
    \ i < n; i++) {\n            V<int> v;\n            for (int j = 0; j < m; j++)\
    \ {\n                if (!ccw(l[i].s, l[i].t, ps[j])) v.push_back(j);\n      \
    \      }\n            sort(v.begin(), v.end(), [&](int x, int y) {\n         \
    \       return (ps[x] - l[i].s).rabs() < (ps[y] - l[i].s).rabs();\n          \
    \  });\n            for (int j = 0; j < int(v.size()) - 1; j++) {\n          \
    \      g[v[j]].push_back(v[j + 1]);\n                g[v[j + 1]].push_back(v[j]);\n\
    \            }\n        }\n\n        for (int i = 0; i < m; i++) {\n         \
    \   sort(g[i].begin(), g[i].end());\n            g[i].erase(unique(g[i].begin(),\
    \ g[i].end()), g[i].end());\n        }\n    }\n};\n\nstruct DualGraph {\n    V<Pol>\
    \ pols;\n    VV<int> g;\n    V<int> tr;\n\n    DualGraph(V<P> ps, VV<int> pg)\
    \ {\n        // prohibit self-loop, multi edge\n        int n = int(ps.size());\n\
    \        using Pi = pair<int, int>;\n        map<Pi, int> mp;\n        for (int\
    \ i = 0; i < n; i++) {\n            if (pg[i].empty()) continue;\n           \
    \ sort(pg[i].begin(), pg[i].end(), [&](int l, int r) {\n                return\
    \ (ps[l] - ps[i]).arg() < (ps[r] - ps[i]).arg();\n            });\n          \
    \  int a, b = pg[i].back();\n            for (int now : pg[i]) {\n           \
    \     a = b;\n                b = now;\n                mp[{b, i}] = a;\n    \
    \        }\n        }\n\n        map<Pi, int> vis;\n        int m = 0;\n     \
    \   for (int i = 0; i < n; i++) {\n            for (int j : pg[i]) {\n       \
    \         if (vis.count({i, j})) continue;\n                int id = m++;\n  \
    \              pols.push_back({});\n                Pi pi = {i, j};\n        \
    \        while (!vis.count(pi)) {\n                    vis[pi] = id;\n       \
    \             pols.back().push_back(ps[pi.first]);\n                    pi = {pi.second,\
    \ mp[pi]};\n                }\n            }\n        }\n\n        g = VV<int>(m);\n\
    \        for (int i = 0; i < n; i++) {\n            for (int j : pg[i]) {\n  \
    \              g[vis[{i, j}]].push_back(vis[{j, i}]);\n            }\n       \
    \ }\n    }\n    V<int> scan(V<P> que, D eps) {\n        int n = int(pols.size()),\
    \ m = int(que.size());\n        tr = V<int>(n);\n        iota(tr.begin(), tr.end(),\
    \ 0);\n        struct S {\n            P s, t;\n            int id;\n        \
    \    D get_y(D x) const {\n                if (!sgn(s.x, t.x)) return s.y;\n \
    \               return (s.y * (t.x - x) + t.y * (x - s.x)) / (t.x - s.x);\n  \
    \          }\n            bool operator<(const S& r) const {\n               \
    \ D x = (max(s.x, r.s.x) + min(t.x, r.t.x)) / 2;\n                return get_y(x)\
    \ < r.get_y(x);\n            }\n        };\n        struct Q {\n            D\
    \ x;\n            int ty;\n            S l;\n        };\n        V<Q> ev;\n  \
    \      for (int i = 0; i < int(que.size()); i++) {\n            auto p = que[i];\n\
    \            ev.push_back({p.x, 0, {p, p, n + i}});\n        }\n        for (int\
    \ ph = 0; ph < n; ph++) {\n            auto v = pols[ph];\n            P a, b\
    \ = v.back();\n            for (auto now : v) {\n                a = b;\n    \
    \            b = now;\n                if (sgn(b.x, a.x) == -1) {\n          \
    \          ev.push_back({b.x, 2, {b, a, ph}});\n                    ev.push_back({a.x,\
    \ 1, {b, a, ph}});\n                }\n            }\n            if (area2(v)\
    \ <= eps) {\n                P mi = *min_element(v.begin(), v.end());\n      \
    \          tr[ph] = -1;\n                ev.push_back({mi.x, 0, {mi, mi, ph}});\n\
    \            }\n        }\n        sort(ev.begin(), ev.end(), [&](Q a, Q b) {\n\
    \            if (sgn(a.x, b.x)) return sgn(a.x, b.x) == -1;\n            return\
    \ a.ty < b.ty;\n        });\n        V<int> res(m);\n        set<S> st;\n    \
    \    for (auto e : ev) {\n            if (e.ty == 0) {\n                // get\n\
    \                auto it = st.lower_bound(e.l);\n                int u = (it ==\
    \ st.end() ? -1 : tr[it->id]);\n                if (e.l.id < n)\n            \
    \        tr[e.l.id] = u;\n                else\n                    res[e.l.id\
    \ - n] = u;\n            } else {\n                if (e.ty == 1)\n          \
    \          st.erase(e.l);\n                else\n                    st.insert(e.l);\n\
    \            }\n        }\n        return res;\n    }\n};\n"
  code: "/*\nreturn arg(l) < arg(r)\narg(-1, 0) = PI, arg(0, 0) = arg(1, 0) = 0\n\
    */\nint argcmp(P l, P r) {\n    auto psgn = [&](P p) {\n        if (int u = sgn(p.y))\
    \ return u;\n        if (sgn(p.x) == -1) return 2;\n        return 0;\n    };\n\
    \    int lsgn = psgn(l), rsgn = psgn(r);\n    if (lsgn < rsgn) return -1;\n  \
    \  if (lsgn > rsgn) return 1;\n    return sgncrs(r, l);\n}\n\nV<L> halfplane_intersects(V<L>\
    \ lines) {\n    sort(lines.begin(), lines.end(), [&](const L& a, const L& b) {\n\
    \        if (int u = argcmp(a.vec(), b.vec())) return u == -1;\n        return\
    \ sgncrs(a.vec(), b.s - a.s) < 0;\n    });\n    lines.erase(unique(lines.begin(),\
    \ lines.end(),\n                       [&](const L& a, const L& b) {\n       \
    \                    return argcmp(a.vec(), b.vec()) == 0;\n                 \
    \      }),\n                lines.end());\n\n    deque<L> st;\n    for (auto l\
    \ : lines) {\n        bool err = false;\n        auto is_need = [&](L a, L b,\
    \ L c) {\n            D ab_dw = crs(a.vec(), b.vec()), ab_up = crs(a.vec(), a.t\
    \ - b.s);\n            D bc_dw = crs(b.vec(), c.vec()), bc_up = crs(c.t - b.s,\
    \ c.vec());\n            if (ab_dw <= 0 || bc_dw <= 0) return true;\n        \
    \    bool f = bc_up * ab_dw > bc_dw * ab_up;\n            if (!f && crs(a.vec(),\
    \ c.vec()) < 0) err = true;\n            return f;\n        };\n        while\
    \ (st.size() >= 2 && !is_need(l, st[0], st[1])) st.pop_front();\n        while\
    \ (st.size() >= 2 &&\n               !is_need(st[st.size() - 2], st[st.size()\
    \ - 1], l))\n            st.pop_back();\n        if (st.size() < 2 || is_need(st.back(),\
    \ l, st.front())) st.push_back(l);\n        if (err) return {};\n    }\n    if\
    \ (st.size() == 2 && !sgncrs(st[0].vec(), st[1].vec()) &&\n        sgncrs(st[0].vec(),\
    \ st[1].s - st[0].s) <= 0)\n        return {};\n\n    return V<L>(st.begin(),\
    \ st.end());\n}\n\nstruct Arrange {\n    V<P> ps;\n    VV<int> g;\n    Arrange(const\
    \ V<L>& l) {\n        int n = int(l.size());\n        for (int i = 0; i < n; i++)\
    \ {\n            ps.push_back(l[i].s);\n            ps.push_back(l[i].t);\n  \
    \          for (int j = i + 1; j < n; j++) {\n                P p;\n         \
    \       if (crossSS(l[i], l[j], p) != 1) continue;\n                ps.push_back(p);\n\
    \            }\n        }\n        sort(ps.begin(), ps.end());\n        ps.erase(unique(ps.begin(),\
    \ ps.end()), ps.end());\n        int m = int(ps.size());\n        g = VV<int>(m);\n\
    \        for (int i = 0; i < n; i++) {\n            V<int> v;\n            for\
    \ (int j = 0; j < m; j++) {\n                if (!ccw(l[i].s, l[i].t, ps[j]))\
    \ v.push_back(j);\n            }\n            sort(v.begin(), v.end(), [&](int\
    \ x, int y) {\n                return (ps[x] - l[i].s).rabs() < (ps[y] - l[i].s).rabs();\n\
    \            });\n            for (int j = 0; j < int(v.size()) - 1; j++) {\n\
    \                g[v[j]].push_back(v[j + 1]);\n                g[v[j + 1]].push_back(v[j]);\n\
    \            }\n        }\n\n        for (int i = 0; i < m; i++) {\n         \
    \   sort(g[i].begin(), g[i].end());\n            g[i].erase(unique(g[i].begin(),\
    \ g[i].end()), g[i].end());\n        }\n    }\n};\n\nstruct DualGraph {\n    V<Pol>\
    \ pols;\n    VV<int> g;\n    V<int> tr;\n\n    DualGraph(V<P> ps, VV<int> pg)\
    \ {\n        // prohibit self-loop, multi edge\n        int n = int(ps.size());\n\
    \        using Pi = pair<int, int>;\n        map<Pi, int> mp;\n        for (int\
    \ i = 0; i < n; i++) {\n            if (pg[i].empty()) continue;\n           \
    \ sort(pg[i].begin(), pg[i].end(), [&](int l, int r) {\n                return\
    \ (ps[l] - ps[i]).arg() < (ps[r] - ps[i]).arg();\n            });\n          \
    \  int a, b = pg[i].back();\n            for (int now : pg[i]) {\n           \
    \     a = b;\n                b = now;\n                mp[{b, i}] = a;\n    \
    \        }\n        }\n\n        map<Pi, int> vis;\n        int m = 0;\n     \
    \   for (int i = 0; i < n; i++) {\n            for (int j : pg[i]) {\n       \
    \         if (vis.count({i, j})) continue;\n                int id = m++;\n  \
    \              pols.push_back({});\n                Pi pi = {i, j};\n        \
    \        while (!vis.count(pi)) {\n                    vis[pi] = id;\n       \
    \             pols.back().push_back(ps[pi.first]);\n                    pi = {pi.second,\
    \ mp[pi]};\n                }\n            }\n        }\n\n        g = VV<int>(m);\n\
    \        for (int i = 0; i < n; i++) {\n            for (int j : pg[i]) {\n  \
    \              g[vis[{i, j}]].push_back(vis[{j, i}]);\n            }\n       \
    \ }\n    }\n    V<int> scan(V<P> que, D eps) {\n        int n = int(pols.size()),\
    \ m = int(que.size());\n        tr = V<int>(n);\n        iota(tr.begin(), tr.end(),\
    \ 0);\n        struct S {\n            P s, t;\n            int id;\n        \
    \    D get_y(D x) const {\n                if (!sgn(s.x, t.x)) return s.y;\n \
    \               return (s.y * (t.x - x) + t.y * (x - s.x)) / (t.x - s.x);\n  \
    \          }\n            bool operator<(const S& r) const {\n               \
    \ D x = (max(s.x, r.s.x) + min(t.x, r.t.x)) / 2;\n                return get_y(x)\
    \ < r.get_y(x);\n            }\n        };\n        struct Q {\n            D\
    \ x;\n            int ty;\n            S l;\n        };\n        V<Q> ev;\n  \
    \      for (int i = 0; i < int(que.size()); i++) {\n            auto p = que[i];\n\
    \            ev.push_back({p.x, 0, {p, p, n + i}});\n        }\n        for (int\
    \ ph = 0; ph < n; ph++) {\n            auto v = pols[ph];\n            P a, b\
    \ = v.back();\n            for (auto now : v) {\n                a = b;\n    \
    \            b = now;\n                if (sgn(b.x, a.x) == -1) {\n          \
    \          ev.push_back({b.x, 2, {b, a, ph}});\n                    ev.push_back({a.x,\
    \ 1, {b, a, ph}});\n                }\n            }\n            if (area2(v)\
    \ <= eps) {\n                P mi = *min_element(v.begin(), v.end());\n      \
    \          tr[ph] = -1;\n                ev.push_back({mi.x, 0, {mi, mi, ph}});\n\
    \            }\n        }\n        sort(ev.begin(), ev.end(), [&](Q a, Q b) {\n\
    \            if (sgn(a.x, b.x)) return sgn(a.x, b.x) == -1;\n            return\
    \ a.ty < b.ty;\n        });\n        V<int> res(m);\n        set<S> st;\n    \
    \    for (auto e : ev) {\n            if (e.ty == 0) {\n                // get\n\
    \                auto it = st.lower_bound(e.l);\n                int u = (it ==\
    \ st.end() ? -1 : tr[it->id]);\n                if (e.l.id < n)\n            \
    \        tr[e.l.id] = u;\n                else\n                    res[e.l.id\
    \ - n] = u;\n            } else {\n                if (e.ty == 1)\n          \
    \          st.erase(e.l);\n                else\n                    st.insert(e.l);\n\
    \            }\n        }\n        return res;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: src/geo/graphiccompute.hpp
  requiredBy: []
  timestamp: '2020-05-08 21:35:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: src/geo/graphiccompute.hpp
layout: document
redirect_from:
- /library/src/geo/graphiccompute.hpp
- /library/src/geo/graphiccompute.hpp.html
title: src/geo/graphiccompute.hpp
---
