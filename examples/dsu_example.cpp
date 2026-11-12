#include <iostream>
#include "advanced_ds/dsu.hpp"

int main() {
    advanced_ds::DSU dsu(7);

    std::cout << "Initial components: " << dsu.count() << '\n';

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    dsu.unite(5, 6);

    std::cout << std::boolalpha;
    std::cout << "Are 0 and 2 connected? "
              << dsu.connected(0, 2) << '\n';
    std::cout << "Are 0 and 4 connected? "
              << dsu.connected(0, 4) << '\n';
    std::cout << "Size of the set containing 1: "
              << dsu.size(1) << '\n';
    std::cout << "Remaining components: "
              << dsu.count() << '\n';

    return 0;
}
