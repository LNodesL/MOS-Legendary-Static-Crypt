#!/bin/bash

# Build script for the complete system
set -e

echo "=== Building Software ==="
cd software
make clean
make
echo "Software built successfully"

echo "=== Packaging Executable ==="
cd ../packager
python3 packager.py ../software/hello_world -o ../runtime/software.h
echo "Executable packaged successfully"

echo "=== Building Runtime ==="
cd ../runtime
make clean
make
echo "Runtime built successfully"

echo "=== Running Complete System ==="
./runtime

echo "=== Build Complete ==="
