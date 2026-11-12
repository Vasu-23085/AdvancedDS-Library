#include <iostream>
#include <vector>
#include "advanced_ds/segment_tree.hpp"

int main() {
    std::vector<long long> values = {2, 4, 1, 7, 3};

    advanced_ds::SegmentTree st(values);

    std::cout << "Initial total sum: "
              << st.rangeSum(0, 5) << '\n';

    std::cout << "Range sum [1, 4): "
              << st.rangeSum(1, 4) << '\n';

    // Assign 10 to the element at index 2.
    st.update(2, 10);

    std::cout << "Range sum [1, 4) after update: "
              << st.rangeSum(1, 4) << '\n';

    std::cout << "Updated total sum: "
              << st.rangeSum(0, 5) << '\n';

    return 0;
}
