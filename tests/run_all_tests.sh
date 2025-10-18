#!/bin/bash

echo "=== Building and Running All Tests ==="

# Build and run tests
make -f Makefile.tests all

# Check if tests completed successfully
if [ $? -eq 0 ]; then
    echo "=== All tests completed successfully ==="
else
    echo "=== Some tests failed ==="
    exit 1
fi
