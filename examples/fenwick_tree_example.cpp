#include <iostream>
#include "advanced_ds/fenwick_tree.hpp"

int main() {
    advanced_ds::FenwickTree ft(5);

    // Original array: [2, 4, 1, 7, 3]
    ft.update(0, 2);
    ft.update(1, 4);
    ft.update(2, 1);
    ft.update(3, 7);
    ft.update(4, 3);

    std::cout << "Prefix sum [0..2]: "
              << ft.prefixSum(2) << '\n';

    // Half-open range [1, 4) means indices 1, 2, 3.
    std::cout << "Range sum [1, 4): "
              << ft.rangeSum(1, 4) << '\n';

    // Add 5 to the element at index 2.
    ft.update(2, 5);

    std::cout << "Prefix sum [0..2] after update: "
              << ft.prefixSum(2) << '\n';

    std::cout << "Total sum: "
              << ft.rangeSum(0, 5) << '\n';

    return 0;
}
