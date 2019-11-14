#!/bin/bash
set -e
oj --version

CXX=${CXX:-g++}
CXXFLAGS="${CXXFLAGS:--std=c++14 -O2 -Wall -Wextra -Wshadow -Wconversion -Werror}"

if [[ "$OSTYPE" == "darwin"* ]]; then
    CXXFLAGS="$CXXFLAGS -Wl,-stack_size,0x10000000"
else
    ulimit -s unlimited
fi

run() {
    file="$1"
    url=$(grep -o '^# *define \+PROBLEM \+\"\(https\?://.*\)\"' < "$file" | sed 's/.* "http/"http/')
    url=${url%\"}
    url=${url#\"}
    dir=test/$(echo -n $url | md5sum | sed 's/ .*//')
    mkdir -p ${dir}
    $CXX $CXXFLAGS -I . -o ${dir}/a.out "$file"
    if [[ -n ${url} ]] ; then
        if [[ ! -e ${dir}/test ]] ; then
            sleep 2
            oj download --system $url -d ${dir}/test
        fi
        oj test --tle 10 --c ${dir}/a.out -d ${dir}/test
    else
        ${dir}/a.out
    fi
}

if [ $# -eq 0 ] ; then
    for f in $(find . -name \*.test.cpp) ; do
        run $f
    done
else
    for f in "$@" ; do
        run "$f"
    done
fi
