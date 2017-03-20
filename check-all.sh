#!/bin/bash
# ./check-all.sh {{bin_name}} {{func_name}} [[ ignore_fail ]]
BASEDIR=$(dirname "$0")
${BASEDIR}/print-func-asm.sh "$1"  "$2" | ${BASEDIR}/check-optimized.sh
EXIT_STATUS="$?"
if [ "$3" ]; then
    [ $EXIT_STATUS -ne 0 ] && echo "Check ${2} failed, ignored"
    exit 0
fi
exit "${EXIT_STATUS}"
