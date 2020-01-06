#!/usr/bin/env python3
from subprocess import check_call
from pathlib import Path
from sys import argv
import re
import platform
import onlinejudge
import shutil

def run(file):
    print('Start: {}'.format(file.name))
    cmd = ['g++']
    cmd += ['-std=c++14', '-O2']
    cmd += ['-Wall', '-Wextra', '-Wshadow', '-Wconversion', '-Wno-sign-conversion', '-Werror']
    cmd += ['-I', '../src/']
    outdir = Path('test') / '_'.join(file.name.split('.'))
    output = outdir / 'a.out'
    cmd += ['-o', output]
    cmd += [file.name]
    print('Output: {}'.format(outdir))
    Path(outdir).mkdir(parents=True, exist_ok=True)
    check_call(cmd)
#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#    res = re.findall(r'^#define PROBLEM "([a-zA-Z:/]*)"$', open(file).read())
    res = re.match(r'^#define PROBLEM "(.*)"$', open(file).read(), re.MULTILINE)

    if not res:
        print('Simple Execute')
        check_call([output.name], timeout=10.0)
        return
    
    url = res.group(1)
    print('Detect URL: {}'.format(url))

    if not Path(outdir / 'test').exists():
        check_call(['oj', 'download', '--system', url, '-d', outdir / 'test'])
    
    oj_problem = onlinejudge.dispatch.problem_from_url(url)
    with open(outdir / 'checker.cpp', 'wb') as f:
        checker = oj_problem.download_checker_cpp()
        f.write(checker)

    if not (Path('test') / 'testlib.h').exists():
        with open(Path('test') / 'testlib.h', 'wb') as f:
            check_call(
                ['curl', 'https://raw.githubusercontent.com/MikeMirzayanov/testlib/master/testlib.h'], stdout=f)

    shutil.copy(Path('test') / 'testlib.h', outdir / 'testlib.h')
    check_call(['g++', '-std=c++14', '-O2', '-o', outdir / 'checker.out', outdir / 'checker.cpp'])

    check_call(['oj', 'test', '-t', '30', '-c', output, '-d', outdir / 'test', '--judge-command', outdir / 'checker.out'])

if __name__ == "__main__":
    check_call(['oj', '--version'])
    
    if len(argv) > 1:
        for fn in argv[1:]:
            run(Path(fn))
    else:
        for f in Path('.').glob('*.test.cpp'):
            run(f)
