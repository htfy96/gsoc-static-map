#!/bin/bash
# Check input that whether complex instruction exists(i.e. not optimized)
EXPR='callq|test|je|jbe'
if grep -C5 -E "${EXPR}"
then
    exit 1
else
    exit 0
fi
