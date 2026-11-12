#include <iostream>
#include "advanced_ds/indexed_priority_queue.hpp"

int main() {
    advanced_ds::IndexedPriorityQueue<int> pq;

    pq.insert(10, 50);
    pq.insert(20, 30);
    pq.insert(30, 40);

    std::cout << "Minimum index: " << pq.minIndex() << '\n';
    std::cout << "Minimum priority: " << pq.minPriority() << '\n';

    pq.changePriority(10, 10);

    std::cout << "Minimum index after update: "
              << pq.minIndex() << '\n';

    auto result = pq.extractMin();

    std::cout << "Extracted index: " << result.first << '\n';
    std::cout << "Extracted priority: " << result.second << '\n';
    std::cout << "Remaining size: " << pq.size() << '\n';

    return 0;
}
