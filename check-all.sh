#!/bin/bash
# ./check-all.sh {{bin_name}} {{func_name}}
BASEDIR=$(dirname "$0")
${BASEDIR}/print-func-asm.sh "$1"  "$2" | ${BASEDIR}/check-optimized.sh
exit $?
