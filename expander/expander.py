#!/usr/bin/env python3

import argparse
import re
from os import getenv
from logging import Logger, basicConfig, getLogger
from subprocess import check_call

logger = getLogger(__name__)  # type: Logger

if __name__ == "__main__":
    basicConfig(
        level=getenv('LOG_LEVEL', 'INFO'),
        format="%(asctime)s %(levelname)s %(name)s : %(message)s"
    )
    parser = argparse.ArgumentParser(description='Testcase Generator')
    parser.add_argument('src', help='Source File')
    args = parser.parse_args()


    check_call(['g++-9', args.src,
        '-E',
        '-I/Users/yosupo/Programs/Algorithm/src',
        '-nostdlib',
        '-I/Users/yosupo/Programs/Algorithm/expander/dummy_include',
        '-o', 'connected.cpp'])

    f = open('connected.cpp', 'r')
    pat = re.compile(r'#pragma yosupo_dummy "(.*)"')
    new_src = ""
    for s in f.readlines():
        res = pat.match(s)
        if res:
            new_src += res.group(1) + '\n'
        else:
            new_src += s
    f.close()
    f = open('connected.cpp', 'w')
    f.write(new_src)
    f.close()
