#!/bin/bash
# Usage: print-func-asm.sh binary(compiled with -g) func_name
# Example: ./print-func-asm.sh static_map 'test_1\(\)'
#                                           ^ This should follow regex syntax

objdump -dS "$1" | c++filt -t | awk "/<$2>:/{flag=1;next}/<.*>:/{flag=0}flag"
