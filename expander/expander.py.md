---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 96, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "#!/usr/bin/env python3\n\nimport argparse\nimport re\nfrom os import getenv\n\
    from logging import Logger, basicConfig, getLogger\nfrom subprocess import check_call\n\
    \nlogger = getLogger(__name__)  # type: Logger\n\nif __name__ == \"__main__\"\
    :\n    basicConfig(\n        level=getenv('LOG_LEVEL', 'INFO'),\n        format=\"\
    %(asctime)s %(levelname)s %(name)s : %(message)s\"\n    )\n    parser = argparse.ArgumentParser(description='Source\
    \ Code Combiner')\n    parser.add_argument('src', help='Source File')\n    parser.add_argument('out',\
    \ help='Output File')\n    args = parser.parse_args()\n\n\n    CXX = getenv('CXX',\
    \ 'g++')\n    check_call([CXX, args.src,\n        '-E', '-C', '-P',\n        '-I/Users/yosupo/Programs/Algorithm/src',\n\
    \        '-nostdlib',\n        '-I/Users/yosupo/Programs/Algorithm/expander/dummy_include',\n\
    \        '-o', args.out])\n\n    f = open(args.out, 'r')\n    pat = re.compile(r'#pragma\
    \ yosupo_dummy \"(.*)\"')\n    new_src = \"\"\n    for s in f.readlines():\n \
    \       res = pat.match(s)\n        if res:\n            new_src += res.group(1)\
    \ + '\\n'\n        else:\n            new_src += s\n    f.close()\n    f = open(args.out,\
    \ 'w')\n    f.write(new_src)\n    f.close()\n"
  dependsOn: []
  isVerificationFile: false
  path: expander/expander.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: expander/expander.py
layout: document
redirect_from:
- /library/expander/expander.py
- /library/expander/expander.py.html
title: expander/expander.py
---
