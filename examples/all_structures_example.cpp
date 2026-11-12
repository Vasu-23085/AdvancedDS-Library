#include <iostream>
#include <string>
#include <vector>

#include "advanced_ds/advanced_ds.hpp"

int main() {
    // 1. Trie
    advanced_ds::Trie trie;
    trie.insert("apple");

    std::cout << "Trie finds apple: "
              << std::boolalpha << trie.search("apple") << '\n';

    // 2. Disjoint Set Union
    advanced_ds::DSU dsu(5);
    dsu.unite(0, 1);

    std::cout << "DSU connects 0 and 1: "
              << dsu.connected(0, 1) << '\n';

    // 3. Fenwick Tree
    advanced_ds::FenwickTree fenwick(4);
    fenwick.update(0, 1);
    fenwick.update(1, 2);
    fenwick.update(2, 3);
    fenwick.update(3, 4);

    std::cout << "Fenwick total: "
              << fenwick.rangeSum(0, 4) << '\n';

    // 4. Segment Tree
    std::vector<long long> values = {1, 2, 3, 4};
    advanced_ds::SegmentTree segmentTree(values);

    std::cout << "Segment tree total: "
              << segmentTree.rangeSum(0, 4) << '\n';

    // 5. LRU Cache
    advanced_ds::LRUCache<int, std::string> cache(2);
    cache.put(1, "Hello");

    std::cout << "LRU cache value: "
              << cache.get(1).value_or("Not found") << '\n';

    // 6. Indexed Priority Queue
    advanced_ds::IndexedPriorityQueue<int> pq;
    pq.insert(100, 25);
    pq.insert(200, 10);

    std::cout << "Priority queue minimum index: "
              << pq.minIndex() << '\n';

    return 0;
}
