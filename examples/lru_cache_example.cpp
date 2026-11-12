#include <iostream>
#include <string>
#include "advanced_ds/lru_cache.hpp"

int main() {
    advanced_ds::LRUCache<int, std::string> cache(2);

    cache.put(1, "Apple");
    cache.put(2, "Banana");

    auto first = cache.get(1);
    std::cout << "Get key 1: "
              << first.value_or("Not found") << '\n';

    // Key 2 is now least recently used.
    cache.put(3, "Cherry");

    std::cout << "Contains key 1: "
              << std::boolalpha << cache.contains(1) << '\n';
    std::cout << "Contains key 2: "
              << cache.contains(2) << '\n';
    std::cout << "Contains key 3: "
              << cache.contains(3) << '\n';

    auto third = cache.get(3);
    std::cout << "Get key 3: "
              << third.value_or("Not found") << '\n';

    std::cout << "Cache size: " << cache.size() << '\n';

    return 0;
}
