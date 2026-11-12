
#include <cassert>
#include <iostream>
#include <string>
#include <stdexcept>

#include "advanced_ds/lru_cache.hpp"

using advanced_ds::LRUCache;

// 1. Basic insertion and retrieval
void testPutAndGet() {
    LRUCache<int, std::string> cache(2);

    cache.put(1, "Apple");
    cache.put(2, "Banana");

    assert(cache.size() == 2);
    assert(cache.capacity() == 2);
    assert(cache.get(1).value() == "Apple");
    assert(cache.get(2).value() == "Banana");
}

// 2. Basic eviction
void testEviction() {
    LRUCache<int, std::string> cache(2);

    cache.put(1, "Apple");
    cache.put(2, "Banana");

    cache.get(1);
    cache.put(3, "Cherry");

    assert(cache.contains(1));
    assert(!cache.contains(2));
    assert(cache.contains(3));
    assert(cache.size() == 2);
}

// 3. Access changes the eviction order
void testGetChangesRecency() {
    LRUCache<int, int> cache(3);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    cache.get(1);
    cache.put(4, 40);

    assert(cache.contains(1));
    assert(!cache.contains(2));
    assert(cache.contains(3));
    assert(cache.contains(4));
}

// 4. Updating an existing key
void testUpdateExistingKey() {
    LRUCache<int, std::string> cache(2);

    cache.put(1, "Old");
    cache.put(2, "Banana");

    cache.put(1, "New");

    assert(cache.size() == 2);
    assert(cache.get(1).value() == "New");

    // Updating key 1 makes it recently used.
    cache.put(3, "Cherry");

    assert(cache.contains(1));
    assert(!cache.contains(2));
    assert(cache.contains(3));
}

// 5. Updating does not increase size
void testUpdateDoesNotIncreaseSize() {
    LRUCache<int, int> cache(2);

    cache.put(1, 100);
    cache.put(1, 200);
    cache.put(1, 300);

    assert(cache.size() == 1);
    assert(cache.get(1).value() == 300);
}

// 6. Zero capacity
void testZeroCapacity() {
    LRUCache<int, int> cache(0);

    cache.put(1, 100);
    cache.put(2, 200);

    assert(cache.empty());
    assert(cache.size() == 0);
    assert(cache.capacity() == 0);
    assert(!cache.get(1).has_value());
    assert(!cache.contains(1));
}

// 7. Capacity one
void testCapacityOne() {
    LRUCache<int, int> cache(1);

    cache.put(1, 10);

    assert(cache.get(1).value() == 10);

    cache.put(2, 20);

    assert(!cache.contains(1));
    assert(cache.contains(2));
    assert(cache.size() == 1);
}

// 8. Missing key
void testMissingKey() {
    LRUCache<int, int> cache(2);

    cache.put(1, 10);

    assert(!cache.get(99).has_value());
    assert(!cache.contains(99));
}

// 9. Erase operations
void testErase() {
    LRUCache<int, int> cache(3);

    cache.put(1, 10);
    cache.put(2, 20);

    assert(cache.erase(1));
    assert(!cache.erase(1));
    assert(!cache.contains(1));
    assert(cache.contains(2));
    assert(cache.size() == 1);
}

// 10. Clear operations
void testClear() {
    LRUCache<int, int> cache(3);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    cache.clear();

    assert(cache.empty());
    assert(cache.size() == 0);
    assert(!cache.contains(1));
    assert(!cache.get(2).has_value());

    // Cache should work after clear.
    cache.put(4, 40);

    assert(cache.get(4).value() == 40);
    assert(cache.size() == 1);
}

// 11. Negative keys and values
void testNegativeValues() {
    LRUCache<int, int> cache(2);

    cache.put(-1, -100);
    cache.put(-2, -200);

    assert(cache.get(-1).value() == -100);
    assert(cache.get(-2).value() == -200);
}

// 12. String keys and values
void testStringKeys() {
    LRUCache<std::string, std::string> cache(2);

    cache.put("name", "Vasu");
    cache.put("language", "C++");

    assert(cache.get("name").value() == "Vasu");
    assert(cache.get("language").value() == "C++");
}

// 13. Repeated eviction
void testRepeatedEviction() {
    LRUCache<int, int> cache(2);

    for (int i = 1; i <= 10; i++) {
        cache.put(i, i * 10);

        assert(cache.size() <= 2);
    }

    assert(!cache.contains(1));
    assert(!cache.contains(2));
    assert(cache.contains(9));
    assert(cache.contains(10));
}

// 14. Erase followed by insertion
void testEraseThenInsert() {
    LRUCache<int, int> cache(2);

    cache.put(1, 10);
    cache.put(2, 20);

    cache.erase(1);
    cache.put(3, 30);

    assert(!cache.contains(1));
    assert(cache.contains(2));
    assert(cache.contains(3));
    assert(cache.size() == 2);
}

int main() {
    testPutAndGet();
    testEviction();
    testGetChangesRecency();
    testUpdateExistingKey();
    testUpdateDoesNotIncreaseSize();
    testZeroCapacity();
    testCapacityOne();
    testMissingKey();
    testErase();
    testClear();
    testNegativeValues();
    testStringKeys();
    testRepeatedEviction();
    testEraseThenInsert();

    std::cout << "All LRU Cache tests passed!\n";

    return 0;
}
