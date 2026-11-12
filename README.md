# AdvancedDS

A header-only C++17 library implementing useful data structures and algorithms with examples and automated tests.

## Features

- **Trie** — Prefix-based string searching and autocomplete.
- **Disjoint Set Union (DSU)** — Efficient connectivity and connected-component operations.
- **Fenwick Tree** — Efficient prefix sums, range sums, and point updates.
- **Segment Tree** — Efficient range-sum queries and point updates.
- **LRU Cache** — Least Recently Used caching with automatic eviction.
- **Indexed Priority Queue** — Min-priority queue supporting priority updates and removal by index.

## Project Structure

```text
AdvancedDS/
├── include/
│   └── advanced_ds/
│       ├── advanced_ds.hpp
│       ├── trie.hpp
│       ├── dsu.hpp
│       ├── fenwick_tree.hpp
│       ├── segment_tree.hpp
│       ├── lru_cache.hpp
│       └── indexed_priority_queue.hpp
├── examples/
├── tests/
├── benchmarks/
├── docs/
├── CMakeLists.txt
└── README.md
```

## Requirements

- A C++17-compatible compiler, such as GCC or Clang.
- CMake 3.16 or later.
- Git (optional).

## Build the Project

Clone the repository, then run:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

## Run Automated Tests

```bash
ctest --test-dir build --output-on-failure
```

## Run Examples

For example, run the combined example:

```bash
./build/all_structures_example
```

Individual examples are available in the `examples/` directory.

## Use the Library

Add the `include` directory to your compiler's include path and include the umbrella header:

```cpp
#include "advanced_ds/advanced_ds.hpp"
```

### 1. Trie

```cpp
advanced_ds::Trie trie;
trie.insert("apple");

bool found = trie.search("apple");
bool hasPrefix = trie.startsWith("app");
```

### 2. Disjoint Set Union

```cpp
advanced_ds::DSU dsu(5);
dsu.unite(0, 1);

bool isConnected = dsu.connected(0, 1);
```

### 3. Fenwick Tree

```cpp
advanced_ds::FenwickTree fenwick(5);

fenwick.update(0, 10);
fenwick.update(1, 20);

long long total = fenwick.rangeSum(0, 2);
```

Fenwick Tree updates add a delta to an element. Its range queries use the half-open interval `[left, right)`.

### 4. Segment Tree

```cpp
std::vector<long long> values = {1, 2, 3, 4, 5};
advanced_ds::SegmentTree tree(values);

long long total = tree.rangeSum(0, 5);
tree.update(0, 10);
```

Segment Tree updates assign a new value to an element. Its range queries use `[left, right)`.

### 5. LRU Cache

```cpp
advanced_ds::LRUCache<int, std::string> cache(2);

cache.put(1, "Apple");
cache.put(2, "Banana");

auto value = cache.get(1);
cache.put(3, "Cherry");
```

When the cache reaches capacity, inserting a new key evicts the least recently used entry. `get()` returns an `std::optional<Value>`.

### 6. Indexed Priority Queue

```cpp
advanced_ds::IndexedPriorityQueue<int> queue;

queue.insert(10, 50);
queue.insert(20, 30);

queue.changePriority(10, 10);
auto minimum = queue.extractMin();
```

The queue returns the entry with the smallest priority. Each index must be unique while it is present in the queue.

## Time Complexity

Let `n` be the number of elements, `L` the length of a string, and `C` the number of entries in a cache or indexed priority queue.

| Data structure | Operation | Time |
|---|---|---|
| Trie | Insert/search/prefix search | O(L) |
| DSU | Union/find | Amortized O(α(n)) |
| Fenwick Tree | Update/prefix or range sum | O(log n) |
| Segment Tree | Build | O(n) |
| Segment Tree | Update/range sum | O(log n) |
| LRU Cache | Get/put/erase | Expected O(1) |
| Indexed Priority Queue | Insert/extract minimum | O(log C) |
| Indexed Priority Queue | Change priority/erase | Expected O(log C) |
| Indexed Priority Queue | Check index existence | Expected O(1) |

The DSU bound assumes path compression and union by rank or size. Hash-based operations have expected, rather than guaranteed, constant-time complexity.

## Testing

The project includes automated tests for the data structures. Please run the test suite before submitting changes.

## Contributing

Contributions are welcome. Consider adding new data structures, tests, examples, documentation, or performance benchmarks.

## License

A license has not yet been selected. Add a license before distributing the project for reuse.
