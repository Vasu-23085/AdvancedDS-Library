
#!/usr/bin/env bash
set -e

cd "$(dirname "$0")"

echo "Configuring AdvancedDS..."
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

echo "Building AdvancedDS..."
cmake --build build

echo "Running all data structures example..."
./build/all_structures_example
