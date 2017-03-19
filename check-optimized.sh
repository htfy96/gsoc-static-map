#!/bin/bash
# Check input that whether complex instruction exists(i.e. not optimized)
EXPR='callq|test|je|jbe'
if grep -C5 -E "${EXPR}"
then
    echo "This function is not optimized!"
    exit 1
else
    echo "This function is optimized"
    exit 0
fi
