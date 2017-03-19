#!/bin/sh
find ./include ./test -type f -name '*.?pp' | xargs clang-format -i
