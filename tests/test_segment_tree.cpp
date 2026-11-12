
#include <cassert>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

#include "advanced_ds/segment_tree.hpp"

using advanced_ds::SegmentTree;

// 1. Initial construction and queries
void testInitialQueries() {
    SegmentTree st({2, 4, 1, 7, 3});

    assert(st.size() == 5);
    assert(st.rangeSum(0, 5) == 17);
    assert(st.rangeSum(1, 4) == 12);
    assert(st.rangeSum(2, 2) == 0);
    assert(st.rangeSum(0, 1) == 2);
    assert(st.rangeSum(4, 5) == 3);
}

// 2. Point updates
void testUpdates() {
    SegmentTree st({2, 4, 1, 7, 3});

    st.update(2, 10);

    assert(st.rangeSum(0, 5) == 26);
    assert(st.rangeSum(1, 4) == 21);
    assert(st.rangeSum(2, 3) == 10);

    st.update(0, -2);

    assert(st.rangeSum(0, 2) == 2);
}

// 3. Repeated updates on the same index
void testRepeatedUpdates() {
    SegmentTree st({5, 10, 15});

    st.update(1, 20);
    assert(st.rangeSum(0, 3) == 40);

    st.update(1, -5);
    assert(st.rangeSum(0, 3) == 15);

    st.update(1, 0);
    assert(st.rangeSum(0, 3) == 20);
}

// 4. Negative values
void testNegativeValues() {
    SegmentTree st({-5, 10, -3, 8});

    assert(st.rangeSum(0, 4) == 10);
    assert(st.rangeSum(0, 1) == -5);
    assert(st.rangeSum(1, 3) == 7);

    st.update(2, -10);

    assert(st.rangeSum(0, 4) == 3);
}

// 5. Single-element tree
void testSingleElement() {
    SegmentTree st({42});

    assert(st.size() == 1);
    assert(st.rangeSum(0, 1) == 42);

    st.update(0, 100);

    assert(st.rangeSum(0, 1) == 100);
}

// 6. Empty tree
void testEmptyTree() {
    SegmentTree st(std::vector<long long>{});

    assert(st.size() == 0);
    assert(st.rangeSum(0, 0) == 0);
}

// 7. Zero values
void testZeroValues() {
    SegmentTree st({0, 0, 0, 0});

    assert(st.rangeSum(0, 4) == 0);

    st.update(2, 10);

    assert(st.rangeSum(0, 4) == 10);
    assert(st.rangeSum(2, 3) == 10);
}

// 8. Invalid update index
void testInvalidUpdate() {
    SegmentTree st({1, 2, 3});

    bool thrown = false;

    try {
        st.update(3, 10);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);
}

// 9. Invalid query ranges
void testInvalidRanges() {
    SegmentTree st({1, 2, 3});

    bool firstThrown = false;
    bool secondThrown = false;

    try {
        st.rangeSum(2, 1);
    } catch (const std::out_of_range&) {
        firstThrown = true;
    }

    try {
        st.rangeSum(0, 4);
    } catch (const std::out_of_range&) {
        secondThrown = true;
    }

    assert(firstThrown);
    assert(secondThrown);
}

// 10. Invalid operations on an empty tree
void testEmptyTreeInvalidOperations() {
    SegmentTree st(std::vector<long long>{});

    bool updateThrown = false;
    bool queryThrown = false;

    try {
        st.update(0, 10);
    } catch (const std::out_of_range&) {
        updateThrown = true;
    }

    try {
        st.rangeSum(0, 1);
    } catch (const std::out_of_range&) {
        queryThrown = true;
    }

    assert(updateThrown);
    assert(queryThrown);
}

// 11. Compare against a normal vector
void testAgainstNormalArray() {
    std::vector<long long> arr(100);

    for (int i = 0; i < 100; i++) {
        arr[i] = i + 1;
    }

    SegmentTree st(arr);

    std::mt19937 rng(42);
    std::uniform_int_distribution<int> indexDist(0, 99);
    std::uniform_int_distribution<int> valueDist(-100, 100);

    for (int operation = 0; operation < 1000; operation++) {

        if (operation % 2 == 0) {
            // Perform an update.
            int index = indexDist(rng);
            long long value = valueDist(rng);

            arr[index] = value;
            st.update(index, value);
        } else {
            // Perform a random range query.
            int left = indexDist(rng);
            int right = indexDist(rng);

            if (left > right) {
                std::swap(left, right);
            }

            // Include the right endpoint.
            right++;

            long long expected = 0;

            for (int i = left; i < right; i++) {
                expected += arr[i];
            }

            assert(st.rangeSum(left, right) == expected);
        }
    }
}

int main() {
    testInitialQueries();
    testUpdates();
    testRepeatedUpdates();
    testNegativeValues();
    testSingleElement();
    testEmptyTree();
    testZeroValues();
    testInvalidUpdate();
    testInvalidRanges();
    testEmptyTreeInvalidOperations();
    testAgainstNormalArray();

    std::cout << "All Segment Tree tests passed!\n";

    return 0;
}
