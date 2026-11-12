
#!/usr/bin/env bash
set -e

cd "$(dirname "$0")"

echo "Configuring AdvancedDS..."
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

echo "Building AdvancedDS..."
cmake --build build

echo "Running all tests..."
ctest --test-dir build --output-on-failure
