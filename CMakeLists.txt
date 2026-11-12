cmake_minimum_required(VERSION 3.16)

project(AdvancedDS
    VERSION 1.0.0
    DESCRIPTION "Reusable Advanced Data Structures Library"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Header-only library
add_library(advanced_ds INTERFACE)

target_include_directories(advanced_ds
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(advanced_ds INTERFACE cxx_std_17)

# Trie example
add_executable(trie_example examples/trie_example.cpp)
target_link_libraries(trie_example PRIVATE advanced_ds)

# Trie tests
enable_testing()

add_executable(test_trie tests/test_trie.cpp)
target_link_libraries(test_trie PRIVATE advanced_ds)

target_compile_options(test_trie PRIVATE -UNDEBUG)

add_test(NAME TrieTests COMMAND test_trie)

add_executable(dsu_example examples/dsu_example.cpp)
target_link_libraries(dsu_example PRIVATE advanced_ds)

add_executable(test_dsu tests/test_dsu.cpp)
target_link_libraries(test_dsu PRIVATE advanced_ds)
target_compile_options(test_dsu PRIVATE -UNDEBUG)
add_test(NAME DSUTests COMMAND test_dsu)

add_executable(fenwick_tree_example examples/fenwick_tree_example.cpp)
target_link_libraries(fenwick_tree_example PRIVATE advanced_ds)

add_executable(test_fenwick_tree tests/test_fenwick_tree.cpp)
target_link_libraries(test_fenwick_tree PRIVATE advanced_ds)
target_compile_options(test_fenwick_tree PRIVATE -UNDEBUG)
add_test(NAME FenwickTreeTests COMMAND test_fenwick_tree)


add_executable(segment_tree_example examples/segment_tree_example.cpp)
target_link_libraries(segment_tree_example PRIVATE advanced_ds)

add_executable(test_segment_tree tests/test_segment_tree.cpp)
target_link_libraries(test_segment_tree PRIVATE advanced_ds)
target_compile_options(test_segment_tree PRIVATE -UNDEBUG)
add_test(NAME SegmentTreeTests COMMAND test_segment_tree)


add_executable(lru_cache_example examples/lru_cache_example.cpp)
target_link_libraries(lru_cache_example PRIVATE advanced_ds)

add_executable(test_lru_cache tests/test_lru_cache.cpp)
target_link_libraries(test_lru_cache PRIVATE advanced_ds)
target_compile_options(test_lru_cache PRIVATE -UNDEBUG)
add_test(NAME LRUCacheTests COMMAND test_lru_cache)

# Indexed Priority Queue
add_executable(indexed_priority_queue_example
    examples/indexed_priority_queue_example.cpp)
target_link_libraries(indexed_priority_queue_example PRIVATE advanced_ds)

add_executable(test_indexed_priority_queue
    tests/test_indexed_priority_queue.cpp)
target_link_libraries(test_indexed_priority_queue PRIVATE advanced_ds)
target_compile_options(test_indexed_priority_queue PRIVATE -UNDEBUG)
add_test(NAME IndexedPriorityQueueTests
    COMMAND test_indexed_priority_queue)

# Combined example using the umbrella header
add_executable(all_structures_example examples/all_structures_example.cpp)
target_link_libraries(all_structures_example PRIVATE advanced_ds)

# Range query benchmark
add_executable(range_query_benchmark
    benchmarks/range_query_benchmark.cpp)
target_link_libraries(range_query_benchmark PRIVATE advanced_ds)
