
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>

#include "advanced_ds/indexed_priority_queue.hpp"

using advanced_ds::IndexedPriorityQueue;

// 1. Basic insertion and minimum
void testInsertAndMinimum() {
    IndexedPriorityQueue<int> pq;

    assert(pq.empty());

    pq.insert(10, 50);
    pq.insert(20, 30);
    pq.insert(30, 40);

    assert(pq.size() == 3);
    assert(!pq.empty());
    assert(pq.minIndex() == 20);
    assert(pq.minPriority() == 30);
    assert(pq.contains(10));
}

// 2. Decrease and increase priority
void testChangePriority() {
    IndexedPriorityQueue<int> pq;

    pq.insert(1, 50);
    pq.insert(2, 30);
    pq.insert(3, 40);

    pq.changePriority(1, 10);

    assert(pq.minIndex() == 1);
    assert(pq.minPriority() == 10);

    pq.changePriority(1, 60);

    assert(pq.minIndex() == 2);
    assert(pq.minPriority() == 30);
}

// 3. Change priority without changing its value
void testSamePriority() {
    IndexedPriorityQueue<int> pq;

    pq.insert(1, 10);
    pq.insert(2, 20);

    pq.changePriority(1, 10);

    assert(pq.minIndex() == 1);
    assert(pq.minPriority() == 10);
}

// 4. Extract minimum
void testExtractMin() {
    IndexedPriorityQueue<int> pq;

    pq.insert(1, 50);
    pq.insert(2, 20);
    pq.insert(3, 30);

    auto result = pq.extractMin();

    assert(result.first == 2);
    assert(result.second == 20);
    assert(!pq.contains(2));
    assert(pq.size() == 2);

    assert(pq.minIndex() == 3);
    assert(pq.minPriority() == 30);
}

// 5. Extract elements in sorted priority order
void testExtractAllInOrder() {
    IndexedPriorityQueue<int> pq;

    pq.insert(10, 50);
    pq.insert(20, 10);
    pq.insert(30, 40);
    pq.insert(40, 20);
    pq.insert(50, 30);

    std::vector<int> expected = {10, 20, 30, 40, 50};

    for (int priority : expected) {
        auto result = pq.extractMin();
        assert(result.second == priority);
    }

    assert(pq.empty());
    assert(pq.size() == 0);
}

// 6. Erase existing and missing indices
void testErase() {
    IndexedPriorityQueue<int> pq;

    pq.insert(1, 10);
    pq.insert(2, 20);
    pq.insert(3, 30);

    assert(pq.erase(1));
    assert(!pq.erase(1));
    assert(!pq.contains(1));
    assert(pq.minIndex() == 2);
    assert(pq.size() == 2);
}

// 7. Erase root, middle and last positions
void testEraseDifferentPositions() {
    IndexedPriorityQueue<int> pq;

    pq.insert(1, 10);
    pq.insert(2, 20);
    pq.insert(3, 30);
    pq.insert(4, 40);
    pq.insert(5, 50);

    assert(pq.erase(1));
    assert(pq.minIndex() == 2);

    assert(pq.erase(4));
    assert(pq.contains(2));
    assert(pq.contains(3));
    assert(pq.contains(5));

    assert(pq.erase(5));
    assert(pq.size() == 2);

    assert(pq.extractMin().second == 20);
    assert(pq.extractMin().second == 30);

    assert(pq.empty());
}

// 8. Duplicate index
void testDuplicateIndex() {
    IndexedPriorityQueue<int> pq;

    pq.insert(1, 10);

    bool thrown = false;

    try {
        pq.insert(1, 20);
    } catch (const std::invalid_argument&) {
        thrown = true;
    }

    assert(thrown);
    assert(pq.size() == 1);
    assert(pq.minPriority() == 10);
}

// 9. Missing index errors
void testMissingIndexErrors() {
    IndexedPriorityQueue<int> pq;

    pq.insert(1, 10);

    bool changeThrown = false;

    try {
        pq.changePriority(99, 5);
    } catch (const std::out_of_range&) {
        changeThrown = true;
    }

    assert(changeThrown);
    assert(!pq.erase(99));
    assert(!pq.contains(99));
}

// 10. Empty queue errors
void testEmptyQueueErrors() {
    IndexedPriorityQueue<int> pq;

    bool indexThrown = false;
    bool priorityThrown = false;
    bool extractThrown = false;

    try {
        pq.minIndex();
    } catch (const std::out_of_range&) {
        indexThrown = true;
    }

    try {
        pq.minPriority();
    } catch (const std::out_of_range&) {
        priorityThrown = true;
    }

    try {
        pq.extractMin();
    } catch (const std::out_of_range&) {
        extractThrown = true;
    }

    assert(indexThrown);
    assert(priorityThrown);
    assert(extractThrown);
}

// 11. Clear and reuse
void testClearAndReuse() {
    IndexedPriorityQueue<int> pq;

    pq.insert(1, 10);
    pq.insert(2, 20);
    pq.insert(3, 30);

    pq.clear();

    assert(pq.empty());
    assert(pq.size() == 0);
    assert(!pq.contains(1));

    pq.insert(4, 40);
    pq.insert(5, 5);

    assert(pq.size() == 2);
    assert(pq.minIndex() == 5);
    assert(pq.minPriority() == 5);
}

// 12. Large index values
void testLargeIndices() {
    IndexedPriorityQueue<int> pq;

    const std::size_t largeIndex =
        std::numeric_limits<std::size_t>::max();

    pq.insert(largeIndex, 10);
    pq.insert(100, 20);

    assert(pq.contains(largeIndex));
    assert(pq.minIndex() == largeIndex);

    assert(pq.erase(largeIndex));
    assert(pq.minIndex() == 100);
}

// 13. Negative priorities
void testNegativePriorities() {
    IndexedPriorityQueue<int> pq;

    pq.insert(1, -10);
    pq.insert(2, -50);
    pq.insert(3, 0);

    assert(pq.minIndex() == 2);
    assert(pq.minPriority() == -50);

    pq.changePriority(3, -100);

    assert(pq.minIndex() == 3);
    assert(pq.minPriority() == -100);
}

// 14. Randomized operations against a reference model
void testRandomizedOperations() {
    IndexedPriorityQueue<int> pq;
    std::vector<std::pair<std::size_t, int>> reference;

    std::mt19937 rng(42);
    std::uniform_int_distribution<int> indexDist(0, 99);
    std::uniform_int_distribution<int> priorityDist(-1000, 1000);

    for (int operation = 0; operation < 1000; operation++) {
        int index = indexDist(rng);
        int priority = priorityDist(rng);

        auto it = std::find_if(
            reference.begin(),
            reference.end(),
            [index](const auto& entry) {
                return entry.first == static_cast<std::size_t>(index);
            }
        );

        int choice = operation % 4;

        if (choice == 0) {
            // Insert
            if (it == reference.end()) {
                pq.insert(index, priority);
                reference.push_back({index, priority});
            }
        } else if (choice == 1) {
            // Change priority
            if (it != reference.end()) {
                pq.changePriority(index, priority);
                it->second = priority;
            }
        } else if (choice == 2) {
            // Erase
            bool actual = pq.erase(index);
            bool expected = (it != reference.end());

            assert(actual == expected);

            if (expected) {
                reference.erase(it);
            }
        } else {
            // Check minimum
            assert(pq.size() == reference.size());

            if (!reference.empty()) {
                auto expected = *std::min_element(
                    reference.begin(),
                    reference.end(),
                    [](const auto& a, const auto& b) {
                        return a.second < b.second;
                    }
                );

                assert(pq.minPriority() == expected.second);

                // For unique minimum priorities, verify the index too.
                int minimumCount = 0;

                for (const auto& entry : reference) {
                    if (entry.second == expected.second) {
                        minimumCount++;
                    }
                }

                if (minimumCount == 1) {
                    assert(pq.minIndex() == expected.first);
                }
            }
        }

        assert(pq.size() == reference.size());
    }
}

int main() {
    testInsertAndMinimum();
    testChangePriority();
    testSamePriority();
    testExtractMin();
    testExtractAllInOrder();
    testErase();
    testEraseDifferentPositions();
    testDuplicateIndex();
    testMissingIndexErrors();
    testEmptyQueueErrors();
    testClearAndReuse();
    testLargeIndices();
    testNegativePriorities();
    testRandomizedOperations();

    std::cout << "All Indexed Priority Queue tests passed!\n";

    return 0;
}
